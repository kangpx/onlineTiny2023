import os
import json
import serial
import struct
import random
from tqdm import tqdm
from sklearn.metrics import accuracy_score, confusion_matrix


with open('../dataset_config.json', 'r') as json_file:
    dataset_config = json.load(json_file)


def trial(ser, x, y_real, inc_flag):
    y_preds = []
    for (_x, _y) in tqdm(zip(x, y_real)):
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
            ser.write(struct.pack('f', 1.0))
        else:
            ser.write(struct.pack('f', 0.0))

        #--------------------------------------------------------------------#
        #                         receive from stm32                         #
        #--------------------------------------------------------------------#
        # while (data := ser.readline()):
        #     print(data.decode('utf-8'))

        label = ser.read(4)
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
    txt_root = dataset_config["qvar_dataset_txt_root"]
    _dir = os.path.join(txt_root, 'user_20')
    _paths = [os.path.join(_dir, name) for name in os.listdir(_dir)]
    random.seed(10086)
    test_paths = random.sample(_paths, int(0.6 * len(_paths)))
    inc_paths = [path for path in _paths if path not in test_paths] * 5
    random.shuffle(inc_paths)
    random.seed()
    
    x_test = []
    y_real_test = []
    x_inc = []
    y_real_inc = []

    for path in test_paths:
        tmp = []
        with open(path, 'r') as txt_file:
            for i in range(40 * 9):
                tmp.append(float(txt_file.readline()))
            y_real = float(txt_file.readline())
        x_test.append(tmp)
        y_real_test.append(int(y_real))

    for path in inc_paths:
        tmp = []
        with open(path, 'r') as txt_file:
            for i in range(40 * 9):
                tmp.append(float(txt_file.readline()))
            y_real = float(txt_file.readline())
        x_inc.append(tmp)
        y_real_inc.append(int(y_real))

    #--------------------------------------------------------------------#
    #                               trial                                #
    #--------------------------------------------------------------------#
    _ = trial(ser, x_inc[:1], y_real_inc[:1], True)
    
    # y_pred_test_pre = trial(ser, x_test, y_real_test, False)
    # _ = trial(ser, x_inc, y_real_inc, True) 
    # y_pred_test_incu = trial(ser, x_test, y_real_test, False)

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
