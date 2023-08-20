import os
import sys
import json
import pickle
import serial
import struct
import random
import numpy as np
from tqdm import tqdm
from sklearn.metrics import accuracy_score
import torch
from torch.utils.data import DataLoader, TensorDataset 
from sklearn.model_selection import train_test_split
sys.path.insert(0, '../pytorch/')
from dataman_ultra import Xy_TrainTest


with open('../dataset_config.json', 'r') as json_file:
    dataset_config = json.load(json_file)


def trial(ser, data_loader, inc_flag):
    y_preds = []
    for _x, _y in tqdm(data_loader):
        _x = _x.numpy().reshape(45, 19)
        _x = np.transpose(_x)
        _x = _x.reshape(-1)
        _x = _x.tolist()
        _y = int(_y.numpy().reshape(-1)[0])
        #--------------------------------------------------------------------#
        #                         transmit to stm32                          #
        #--------------------------------------------------------------------#
        # transmit label
        ser.write(struct.pack('f', _y))

        # transmit data
        data_vector = bytearray()
        for __x in _x:
            data_vector.extend(struct.pack('f', __x))
        ser.write(data_vector)

        # transmit inc_flag
        if inc_flag is True:
            ser.write(struct.pack('f', 1))
        else:
            ser.write(struct.pack('f', 0))

        #--------------------------------------------------------------------#
        #                         receive from stm32                         #
        #--------------------------------------------------------------------#
        # while (data := ser.readline()):
        #     print(str(data.decode('utf-8')))

        label = ser.read(1)
        if label:
            y_preds.append(int(label.decode('utf-8')))
    return y_preds



def main():
    #--------------------------------------------------------------------#
    #                     instantiate serial object                      #
    #--------------------------------------------------------------------#
    ser = serial.Serial('/dev/tty.usbmodem1203', 115200, timeout=0.5)
    
    #--------------------------------------------------------------------#
    #                             load file                              #
    #--------------------------------------------------------------------#
    fold = 3

    dataset_root = dataset_config["ultra_dataset_root"]

    _, _, x_test, y_test = Xy_TrainTest(dataset_root, fold)

    x_test, x_incu, y_test, y_incu = train_test_split(x_test, y_test, train_size=0.6, random_state=136+fold)

    test_dataset = TensorDataset(x_test, y_test)
    incu_dataset = TensorDataset(x_incu, y_incu)
    

    torch.manual_seed(0)
    test_loader = DataLoader(test_dataset, shuffle=False, batch_size=1, drop_last=False)
    incu_loader = DataLoader(incu_dataset, shuffle=True, batch_size=1, drop_last=False)

    # _paths = []
    # __dir = os.path.join(dataset_root, f'subject_{fold}')
    # for i_cls in range(8):
    #     _dir = os.path.join(__dir, f'class_{i_cls}')
    #     _paths += [os.path.join(_dir, name) for name in os.listdir(_dir)]
    #
    # random.seed(10086)
    # test_paths = random.sample(_paths, int(0.6 * len(_paths)))
    # inc_paths = [path for path in _paths if path not in test_paths]
    # random.shuffle(inc_paths)
    # random.seed()
    # 
    # x_test = []
    # y_real_test = []
    # x_inc = []
    # y_real_inc = []
    #
    # for path in test_paths:
    #     with open(path, 'rb') as pkl_file:
    #         tmp = pickle.load(pkl_file)
    #         x_tmp = np.transpose(tmp['X'][0:855].reshape(45, 19), (1, 0)).reshape(-1).tolist()
    #         y_tmp = int(tmp['y'])
    #     x_test.append(x_tmp)
    #     y_real_test.append(y_tmp)
    #
    # for path in inc_paths:
    #     with open(path, 'rb') as pkl_file:
    #         tmp = pickle.load(pkl_file)
    #         x_tmp = np.transpose(tmp['X'][0:855].reshape(45, 19), (1, 0)).reshape(-1).tolist()
    #         y_tmp = int(tmp['y'])
    #     x_inc.append(x_tmp)
    #     y_real_inc.append(y_tmp)

    #--------------------------------------------------------------------#
    #                               trial                                #
    #--------------------------------------------------------------------#
    y_pred_test_pre = trial(ser, test_loader, False)
    print(f'pre accuracy: {accuracy_score(y_test.numpy().tolist(), y_pred_test_pre)}')
    _ = trial(ser, incu_loader, True) 
    y_pred_test_incu = trial(ser, test_loader, False)
    print(f'inc accuracy: {accuracy_score(y_test.numpy().tolist(), y_pred_test_incu)}')

    #--------------------------------------------------------------------#
    #                        close serial object                         #
    #--------------------------------------------------------------------#
    ser.close()

    #--------------------------------------------------------------------#
    #                         print trial result                         #
    #--------------------------------------------------------------------#
    # print(f'pre accuracy: {accuracy_score(y_real_test, y_pred_test_pre)}')
    # print(f'inc accuracy: {accuracy_score(y_real_test, y_pred_test_incu)}')


if __name__ == '__main__':
    main()

