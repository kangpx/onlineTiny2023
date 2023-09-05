#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators_fp16.h"

#include "CNN_Copy_Generators.h"

void load_expressions_kernels() {
}





void UltraModel(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 4, "at_api.h", "Ultra.h", "CNN_BasicKernels_fp16.h", "Expression_Kernels.h");
    SetGeneratedFilesNames("UltraKernels.c", "UltraKernels.h");
    AT_SetGraphCtrl(AT_GRAPH_MONITOR_CYCLES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_NODE_NAMES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_OPERINFOS, AT_OPT_ON);

    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "Ultra_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "Ultra_L2_Memory", 0, 1,
        AT_MEM_L3_DEFAULTRAM, L3Memory, "Ultra_L3_Memory", 0, 0,
        AT_MEM_L3_DEFAULTFLASH, L3Flash, "Ultra_L3_Flash", "Ultra_L3_Flash_Const.dat", 0
    );

    LoadCNNLibrary_fp16();
    load_expressions_kernels();

    // generator for Conv_0_fusion
    CNN_ConvolutionPoolAct_fp16("S4_Conv_0_fusion", 0,
                                 45, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_2_fusion
    CNN_ConvolutionPoolAct_fp16("S9_Conv_2_fusion", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_4_fusion
    CNN_ConvolutionPoolAct_fp16("S12_Conv_4_fusion", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_6
    CNN_ConvolutionPoolAct_fp16("S15_Conv_6", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_NONE);
    
    
    // generator for Add_7_fusion
    CNN_MatAddAct_fp16("S17_Add_7_fusion", 0, 1, 1, 64, 19, KOP_MATADD, KOP_RELU);
    
    // generator for Conv_9_fusion
    CNN_ConvolutionPoolAct_fp16("S21_Conv_9_fusion", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_11_fusion
    CNN_ConvolutionPoolAct_fp16("S24_Conv_11_fusion", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_13
    CNN_ConvolutionPoolAct_fp16("S27_Conv_13", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_NONE);
    
    
    // generator for Add_14_fusion
    CNN_MatAddAct_fp16("S29_Add_14_fusion", 0, 1, 1, 64, 19, KOP_MATADD, KOP_RELU);
    
    // generator for Conv_16_fusion
    CNN_ConvolutionPoolAct_fp16("S33_Conv_16_fusion", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_18_fusion
    CNN_ConvolutionPoolAct_fp16("S36_Conv_18_fusion", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_RELU);
    
    // generator for Conv_20
    CNN_ConvolutionPoolAct_fp16("S39_Conv_20", 0,
                                 64, 64, 19, 1,
                                 KOP_CONV, 3, 1, 1, 1, 1, 1, 1,
                                 KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                                 KOP_NONE);
    
    
    // generator for Add_21_fusion
    CNN_MatAddAct_fp16("S41_Add_21_fusion", 0, 1, 1, 64, 19, KOP_MATADD, KOP_RELU);
    
    // generator for Gemm_30
    CNN_LinearAct_fp16("S44_Gemm_30", 0,
                      1216, 8,
                      KOP_LINEAR, KOP_NONE);
    
    // generator for Softmax_31
    CNN_SoftMax_fp16("S45_Softmax_31", 0, 8, KOP_SOFTMAX);
    

#define GRAPH
#ifdef GRAPH
    CreateGraph("UltraCNN",
        /* Arguments either passed or globals */
            CArgs(24,
                TCArgInfo("F16 * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("F16 * __restrict__", "Conv_0_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_0_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_120", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_120.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_2_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_2_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_123", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_123.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_4_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_4_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_126", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_126.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_6_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_6_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_129", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_129.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_9_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_9_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_132", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_132.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_11_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_11_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_135", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_135.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_13_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_13_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_138", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_138.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_16_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_16_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_141", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_141.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_18_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_18_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_144", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_144.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Conv_20_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Conv_20_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Constant_onnx__conv_147", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Constant_onnx__conv_147.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Gemm_30_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Gemm_30_weights.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Gemm_30_biases", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("tensors/Gemm_30_biases.tensor", 1, 1, 16, 0)),
                TCArgInfo("F16 * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(14,
            TCArgInfo("F16 * __restrict__", "S4_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S9_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S12_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S15_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S17_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S21_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S24_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S27_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S29_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S33_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S36_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S39_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S41_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("F16 * __restrict__", "S44_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );



    // Node S4_Conv_0_fusion
    AddNode("S4_Conv_0_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "Input_1", 0),
            GNodeArg(GNA_IN, "Conv_0_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_120", 0),
            GNodeArg(GNA_OUT, "S4_Output", 0)
        )
    );
    // Node S9_Conv_2_fusion
    AddNode("S9_Conv_2_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "S4_Output", 0),
            GNodeArg(GNA_IN, "Conv_2_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_123", 0),
            GNodeArg(GNA_OUT, "S9_Output", 0)
        )
    );
    // Node S12_Conv_4_fusion
    AddNode("S12_Conv_4_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "S9_Output", 0),
            GNodeArg(GNA_IN, "Conv_4_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_126", 0),
            GNodeArg(GNA_OUT, "S12_Output", 0)
        )
    );
    // Node S15_Conv_6
    AddNode("S15_Conv_6",
        Bindings(4,
            GNodeArg(GNA_IN, "S12_Output", 0),
            GNodeArg(GNA_IN, "Conv_6_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_129", 0),
            GNodeArg(GNA_OUT, "S15_Output", 0)
        )
    );
    // Node S17_Add_7_fusion in1q bf16 in2q bf16 outq bf16
    AddNode("S17_Add_7_fusion",
        Bindings(3,
            GNodeArg(GNA_IN, "S15_Output", 0),
            GNodeArg(GNA_IN, "S4_Output", 0),
            GNodeArg(GNA_OUT, "S17_Output", 0)
        )
    );
    // Node S21_Conv_9_fusion
    AddNode("S21_Conv_9_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "S17_Output", 0),
            GNodeArg(GNA_IN, "Conv_9_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_132", 0),
            GNodeArg(GNA_OUT, "S21_Output", 0)
        )
    );
    // Node S24_Conv_11_fusion
    AddNode("S24_Conv_11_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "S21_Output", 0),
            GNodeArg(GNA_IN, "Conv_11_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_135", 0),
            GNodeArg(GNA_OUT, "S24_Output", 0)
        )
    );
    // Node S27_Conv_13
    AddNode("S27_Conv_13",
        Bindings(4,
            GNodeArg(GNA_IN, "S24_Output", 0),
            GNodeArg(GNA_IN, "Conv_13_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_138", 0),
            GNodeArg(GNA_OUT, "S27_Output", 0)
        )
    );
    // Node S29_Add_14_fusion in1q bf16 in2q bf16 outq bf16
    AddNode("S29_Add_14_fusion",
        Bindings(3,
            GNodeArg(GNA_IN, "S27_Output", 0),
            GNodeArg(GNA_IN, "S17_Output", 0),
            GNodeArg(GNA_OUT, "S29_Output", 0)
        )
    );
    // Node S33_Conv_16_fusion
    AddNode("S33_Conv_16_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "S29_Output", 0),
            GNodeArg(GNA_IN, "Conv_16_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_141", 0),
            GNodeArg(GNA_OUT, "S33_Output", 0)
        )
    );
    // Node S36_Conv_18_fusion
    AddNode("S36_Conv_18_fusion",
        Bindings(4,
            GNodeArg(GNA_IN, "S33_Output", 0),
            GNodeArg(GNA_IN, "Conv_18_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_144", 0),
            GNodeArg(GNA_OUT, "S36_Output", 0)
        )
    );
    // Node S39_Conv_20
    AddNode("S39_Conv_20",
        Bindings(4,
            GNodeArg(GNA_IN, "S36_Output", 0),
            GNodeArg(GNA_IN, "Conv_20_weights", 0),
            GNodeArg(GNA_IN, "Constant_onnx__conv_147", 0),
            GNodeArg(GNA_OUT, "S39_Output", 0)
        )
    );
    // Node S41_Add_21_fusion in1q bf16 in2q bf16 outq bf16
    AddNode("S41_Add_21_fusion",
        Bindings(3,
            GNodeArg(GNA_IN, "S39_Output", 0),
            GNodeArg(GNA_IN, "S29_Output", 0),
            GNodeArg(GNA_OUT, "S41_Output", 0)
        )
    );
    // Node Gemm_30
    AddNode("S44_Gemm_30",
        Bindings(4,
            GNodeArg(GNA_IN, "S41_Output", 0),
            GNodeArg(GNA_IN, "Gemm_30_weights", 0),
            GNodeArg(GNA_IN, "Gemm_30_biases", 0),
            GNodeArg(GNA_OUT, "S44_Output", 0)
        )
    );
    // Node Softmax_31 inq bf16 outq bf16
    AddNode("S45_Softmax_31",
        Bindings(2,
            GNodeArg(GNA_IN, "S44_Output", 0),
            GNodeArg(GNA_OUT, "Output_1", 0)
        )
    );
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    UltraModel(128000, 1350000, 8000000, 64*1024*1024);
    GenerateTilingCode();
    return 0;
}
