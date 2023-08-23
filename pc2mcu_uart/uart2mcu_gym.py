import os
import json
import serial
import struct
import random
import argparse
import numpy as np
from tqdm import tqdm
from sklearn.metrics import accuracy_score, confusion_matrix


with open('../dataset_config.json', 'r') as json_file:
    dataset_config = json.load(json_file)


def trial(ser, x, y, inc_flag):
    y_preds = []
    for _x, _y in tqdm(zip(x, y)):
        _x = _x.reshape(7, 40)
        _x = np.transpose(_x)
        _x = _x.reshape(-1)
        _x = _x.tolist()
        _y = int(_y.reshape(-1)[0])
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

        label = ser.read(4)
        if label:
            y_preds.append(struct.unpack('I', label))
    return y_preds


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--fold', type=int, default=1)
    args = parser.parse_args()

    #--------------------------------------------------------------------#
    #                     instantiate serial object                      #
    #--------------------------------------------------------------------#
    ser = serial.Serial('/dev/tty.usbmodem1203', 115200, timeout=0.5)
    
    #--------------------------------------------------------------------#
    #                             load file                              #
    #--------------------------------------------------------------------#
    fold = args.fold
    print(f'fold: {fold}')

    dataset_path = os.path.join(dataset_config["gym_incu_dataset_root"], f'fold_{fold}_incu_dataset.npz')

    data = np.load(dataset_path)

    x_incu, y_incu, x_test, y_test = data['x_incu'], data['y_incu'], data['x_test'], data['y_test']


    #--------------------------------------------------------------------#
    #                               trial                                #
    #--------------------------------------------------------------------#
    y_pred_test_pre = trial(ser, x_test, y_test, False)
    print(f'pre accuracy: {accuracy_score(y_test, y_pred_test_pre)}')
    for epoch in range(1):
        _ = trial(ser, x_incu, y_incu, True) 
    y_pred_test_incu = trial(ser, x_test, y_test, False)
    print(f'inc accuracy: {accuracy_score(y_test, y_pred_test_incu)}')

    #--------------------------------------------------------------------#
    #                        close serial object                         #
    #--------------------------------------------------------------------#
    ser.close()

    #--------------------------------------------------------------------#
    #                         print trial result                         #
    #--------------------------------------------------------------------#
    # print(f'pre accuracy: {accuracy_score(y_test, y_pred_test_pre)}')
    # print(f'inc accuracy: {accuracy_score(y_test, y_pred_test_incu)}')


if __name__ == '__main__':
    main()
