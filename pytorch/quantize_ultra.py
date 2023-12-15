import os
import datetime
import pickle as pkl
import json
import random
import numpy as np
from sklearn.metrics.pairwise import normalize
import torch
import torch.nn as nn
import torch.optim as optim
from torch.optim.lr_scheduler import CosineAnnealingLR, CosineAnnealingWarmRestarts
from torch.utils.data import DataLoader, TensorDataset, WeightedRandomSampler
import pandas as pd
from dataman_ultra import CLASSES, Xy_TrainTest
from model_definitions import ResNetBackBone, Classifier, ResNet
from sklearn.metrics import accuracy_score, confusion_matrix, f1_score, precision_score, recall_score
from sklearn.model_selection import train_test_split
from early_stopping import EarlyStopping
import matplotlib.pyplot as plt 
import onnxruntime
from onnxruntime.quantization import QuantFormat, QuantType, StaticQuantConfig, quantize, CalibrationMethod
from onnxruntime.quantization import CalibrationDataReader


class CaliDataReader(CalibrationDataReader):
    def __init__(self, cali_dataset, onnx_path):
        self.enum_data = None

        # Use inference session to get input shape.
        session = onnxruntime.InferenceSession(onnx_path, None)
        (_, _, height, width) = session.get_inputs()[0].shape

        self.cali_dataset = cali_dataset
      
        self.input_name = session.get_inputs()[0].name
        self.datasize = len(self.cali_dataset)

    def get_next(self):
        if self.enum_data is None:
            self.enum_data = iter(
                [{self.input_name: x} for x in self.cali_dataset]
            )
        return next(self.enum_data, None)

    def rewind(self):
        self.enum_data = None


def get_quantize(onnx_path, quantized_onnx_path, cali_dr):
    conf = StaticQuantConfig(calibration_data_reader=cali_dr, 
                             quant_format=QuantFormat.QDQ, 
                             calibrate_method=CalibrationMethod.MinMax,
                             optimize_model=True,
                             activation_type=QuantType.QInt8,
                             weight_type=QuantType.QInt8,
                             per_channel=True)
        
    quantize(onnx_path, quantized_onnx_path, conf)
    print(f'combination has been quantized and stored in {quantized_onnx_path}')


def main():
    onnx_path = '../saved_models/ultra/onnx/fold_0_pre_combination_fullvalid_c32.onnx'
    quantized_onnx_path  = '../saved_models/ultra/onnx/fold_0_pre_combination_fullvalid_c32_QUANT.onnx'

    x_train, y_train, _, _ = Xy_TrainTest(fold_n=0)

    cali_dr = CaliDataReader(x_train, onnx_path)
    get_quantize(onnx_path, quantized_onnx_path, cali_dr)


if __name__ == '__main__':
    main()

