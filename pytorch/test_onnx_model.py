import os
import numpy as np
import torch
from model_definitions import ResNet, ResNet
import onnx
import onnxruntime


if __name__ == '__main__':
    combination_path = 'fold_1_pre_combination_bn_bs64.onnx'
    combination_model = onnx.load(combination_path)
    onnx.checker.check_model(combination_model)

    txt_root = '../datasets/qvar_dataset_txt'
    _dir = os.path.join(txt_root, 'user_03')
    _paths = [os.path.join(_dir, name) for name in os.listdir(_dir)]

    y_real = -1.0
    in_data = []

    with open(_paths[0], 'r') as txt_file:
        for i in range(40 * 9):
            in_data.append(float(txt_file.readline()))
        y_real = float(txt_file.readline())
    
    in_data = np.array(in_data).reshape(1, 40, 9)
    in_data = np.transpose(in_data, (0, 2, 1))

    ort_session = onnxruntime.InferenceSession(combination_path)
    ort_inputs = {ort_session.get_inputs()[0].name: in_data.astype(np.float32)}
    ort_outs = ort_session.run(None, ort_inputs)
    ort_out = ort_outs[0]
    print(ort_out)
    print(np.argmax(ort_out))
    print(y_real)
