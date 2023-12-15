import argparse
import argcomplete
from nntool.api import NNGraph
from nntool.graph.types import ConstantInputNode, InputNode
import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt
import os
from PIL import Image


def create_parser():
    # create the top-level parser
    parser = argparse.ArgumentParser(prog='train')

    parser.add_argument('--mode', default="generate_at_model", choices=["accuracy", "performance", "generate_at_model"], help="Script mode")
    parser.add_argument('--trained_model', help='Output - Trained model in tflite format')
    # parser.add_argument('--activation_bits', default=8, choices=[8, 16],
    #                     help="If NE16 enabled you can select the number of bits for activations (8 and 16 supported)")
    # parser.add_argument('--weight_bits', default=8, choices=[2, 3, 4, 5, 6, 7, 8],
    #                     help="If NE16 enabled you can select the number of bits for weights (2-8 supported)")
    parser.add_argument('--ne16', default=False, action="store_true", help="Use NE16 HW accelerator in GAP9")
    parser.add_argument('--fp16', default=True, action="store_true", help="Use FP16 kernels for more numerical precision")
    parser.add_argument('--fp32', default=False, action="store_true", help="Use FP32 kernels for more numerical precision")
    parser.add_argument('--tensors_dir', default='tensors', help="Where nntool stores the weights/bias tensors dir (only used in generate and performance mode)")
    parser.add_argument('--at_model_path', default="QvarModel.c", help="Path to the C autotiler model file to generate (only used in generate mode)")
    parser.add_argument('--ram_type', default="AT_MEM_L3_DEFAULTRAM", choices=['AT_MEM_L3_HRAM', 'AT_MEM_L3_QSPIRAM', 'AT_MEM_L3_OSPIRAM', 'AT_MEM_L3_DEFAULTRAM'], help="Ram type to use during inference on platform (only used in generate and performance mode)")
    parser.add_argument('--flash_type', default="AT_MEM_L3_DEFAULTFLASH", choices=['AT_MEM_L3_HFLASH', 'AT_MEM_L3_QSPIFLASH', 'AT_MEM_L3_OSPIFLASH', 'AT_MEM_L3_MRAMFLASH', 'AT_MEM_L3_DEFAULTFLASH'], help="Flash type to use during inference (only used in generate and performance mode)")
    return parser


def nntool_build_model(model_path, quant_opts, already_quantized=False):
    G = NNGraph.load_graph(model_path, load_quantization=already_quantized)
    G.adjust_order()
    G.fusions("scaled_match_group")
    stats = None
    G.quantize(
        stats,
        read_existing_options=not quant_opts["scheme"] == "FLOAT",
        graph_options=quant_opts
    )
    print(quant_opts)
    print(G.qshow())
    return G


def test_accuracy(G, test_data, test_labels, quant_execution):
    correct = 0
    for x, y in tqdm(zip(test_data, test_labels), total=len(test_labels), desc="Testing:"):
        out = G.execute([x], dequantize=quant_execution)
        # out = G.execute_on_target([x])
        correct += int(np.argmax(out[-1][0]) == y)
    print(f"NNTool accuracy:\t\t{100*correct / len(test_data):.2f}%")


def main():
    parser = create_parser()
    argcomplete.autocomplete(parser)
    args = parser.parse_args()

    if args.ne16:
        quant_opts = {
            "scheme": "SQ8",
            "use_ne16": True,
            "force_input_size": args.activation_bits,
            "force_output_size": args.activation_bits,
            "force_external_size": args.activation_bits,
            "weight_bits": args.weight_bits,
            "allow_asymmetric_out": True,
        }
    elif args.fp16:
        quant_opts={
            "scheme": "FLOAT",
            "float_type": "bfloat16",
            "use_ne16": True,
        }
    elif args.fp32:
        quant_opts={
            "scheme": "FLOAT",
            "float_type": "float32",
        }
    else:
        quant_opts={
            "scheme": "SQ8",
            "allow_asymmetric_out": True,
        }

    G = nntool_build_model(args.trained_model, quant_opts, already_quantized=False)
    G.name = "Qvar"
    at_settings = {
        "tensor_directory": args.tensors_dir,
        "model_directory": os.path.split(args.at_model_path)[0] if args.at_model_path else "",
        "model_file": os.path.split(args.at_model_path)[1] if args.at_model_path else "ATmodel.c",
        "l3_ram_device": args.ram_type,
        "l3_flash_device": args.flash_type, #"AT_MEM_L3_DEFAULTFLASH",
        "l2_size": 1350000,
        "l1_size": 128000,
        "cluster_stack_size": 1024,
        "cluster_slave_stack_size": 512,
        # "graph_l1_promotion": 1, #2,
        #"graph_group_weights": True,
        #"graph_async_fork": True,
        "graph_monitor_cycles": True,
        "graph_produce_node_names": True,
        "graph_produce_operinfos": True,
    }

    if args.mode == "accuracy":
        data = np.load(os.path.join('/home/kangpx/onlineTiny2023/datasets/incu_datasets/qvar', f'fold_{3}_incu_dataset.npz'))                                                                                                                                                                                             
        x_incu, y_incu, x_test, y_test = data['x_incu'], data['y_incu'], data['x_test'], data['y_test']                                                                                                                                                                 
        #print(x_test.shape, x_test.dtype)
        test_accuracy(G, x_test[:3], y_incu[:3], True)
    elif args.mode == "performance":
        in_data = np.array(Image.open("test_images/5223_5.pgm")).astype(np.float32) / 128 - 1.0
        in_data = in_data.reshape(G[0].in_dims[0].shape).astype(np.float32)
        qout = G.execute([in_data], quantize=True, dequantize=False)
        res = G.execute_on_target(
            pmsis_os="freertos",
            platform="gvsoc", # platform could also be board if you want to run it on the chip
            directory="gap_test_inference",
            input_tensors=qout[0],
            output_tensors=4,
            write_out_to_file=True,
            tolerance=0.1 if args.fp16 else 0.0,
            at_log=True,
            dont_run=False,
            do_clean=False,
            cmake=True,
            print_output=True,
            memory=True,
            check_on_target=True,
            settings=at_settings,
        )
        qsnrs = G.qsnrs(qout, res.output_tensors)
        for n in G.nodes(sort=True):
            if isinstance(n, (ConstantInputNode, InputNode)):
                continue
            print(f"QSNR Layer {n.step_idx:3} ({n.name[:30]:30}): {qsnrs[n.step_idx]}")
        plots = res.plot_memory_boxes()
        plt.show()
    elif args.mode == "generate_at_model":
        G.generate(
            write_constants=True,
            settings=at_settings
        )


if __name__ == '__main__':
    main()

