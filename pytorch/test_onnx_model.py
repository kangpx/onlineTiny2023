import os
import json
import numpy as np
import torch
from model_definitions import ResNet, ResNet
import onnx
import onnxruntime


with open('../dataset_config.json', 'r') as json_file:
    dataset_config = json.load(json_file)


if __name__ == '__main__':
    combination_path = '../saved_models/ultra/onnx/fold_0_pre_combination_fullvalid.onnx'
    combination_model = onnx.load(combination_path)
    onnx.checker.check_model(combination_model)

    dataset_path = os.path.join(dataset_config["ultra_incu_dataset_root"], f'fold_{0}_incu_dataset.npz')

    data = np.load(dataset_path)

    x_incu, y_incu, x_test, y_test = data['x_incu'], data['y_incu'], data['x_test'], data['y_test']

    in_data = x_test[0][np.newaxis, :, :]
    in_label = int(y_test[0])
    print(in_data.shape)
    with open('/Users/kangpx/test_in_data.txt', 'w') as file:
        file.write(','.join([str(item) for item in in_data.reshape(-1).tolist()]))

    ort_session = onnxruntime.InferenceSession(combination_path)
    ort_inputs = {ort_session.get_inputs()[0].name: in_data.astype(np.float32)}
    ort_outs = ort_session.run(None, ort_inputs)
    ort_out = ort_outs[0]
    print(ort_out)
    print(f'real: {in_label}, predicted: {np.argmax(ort_out)}')
