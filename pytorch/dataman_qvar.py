import os
import json
import multiprocessing as mp
import scipy.signal as signal
import numpy as np
import torch
import pandas as pd
from matplotlib import pyplot as plt
from numpy.lib.stride_tricks import sliding_window_view
from tqdm import tqdm



CLASSES = ['1_wave_left', '2_wave_right', '3_make_fist', '4_stretch_fingers', '5_point_index_finger', '6_flick_fingers', '7_circle_left', '8_circle_right', '9_tap_index_thumb', '10_tap_little_thumb']
# SENSING_DIMENSIONS = ['acc_x','acc_y', 'acc_z', 'gyro_x', 'gyro_y', 'gyro_z', 'qvar_ch0', 'qvar_ch1', 'qvar_ch2', 'qvar_ch3', 'qvar_ch4', 'qvar_ch5']
SENSING_DIMENSIONS = ['acc_x','acc_y', 'acc_z', 'qvar_ch0', 'qvar_ch1', 'qvar_ch2', 'qvar_ch3', 'qvar_ch4', 'qvar_ch5']

with open('../dataset_config.json', 'r') as json_file:
    dataset_config = json.load(json_file)


def Xy_TrainTest_Kfold(fold_n):
    print('loading QVAR dataset...')
    with open(dataset_config["qvar_dataset_start_indices_path"], 'r') as file:
        start_indices_dict = json.load(file)
    x_whole = np.empty((0, 9, 240))
    y_whole = np.empty(0)

    sos = signal.cheby2(4, 30, 45, 'lowpass', fs=240, output='sos')

    for i_user in range(1, 21):
        for path, start_index in start_indices_dict[f'user_{i_user:0>2}'].items():
            if start_index < 0:
                continue
            with open(path, 'r') as file:
                data = json.load(file)
            x_sensing = np.array([data[sensing] for sensing in SENSING_DIMENSIONS])
            #
            x_sensing_filtered = signal.sosfilt(sos, x_sensing)
            x_slice = x_sensing_filtered[:, start_index: start_index + 240]

            # x_slice = x_sensing[:, start_index: start_index + 240]

            x_whole = np.concatenate((x_whole, x_slice[np.newaxis, :, :]), 0)
            y_whole = np.concatenate((y_whole, np.array([CLASSES.index(data['gesture'])])))

    shuffled_indices = np.arange(x_whole.shape[0])
    np.random.seed(136)
    np.random.shuffle(shuffled_indices)
    np.random.seed()
    n_sample_per_segment = x_whole.shape[0] // 10
    test_indices = shuffled_indices[(fold_n - 1) * n_sample_per_segment: fold_n * n_sample_per_segment]
    train_indices = [k for k in shuffled_indices if k not in test_indices]
    x_train = x_whole[train_indices]
    y_train = y_whole[train_indices]
    x_test = x_whole[test_indices]
    y_test = y_whole[test_indices]

    x_train = torch.from_numpy(x_train.copy()).float()
    y_train = torch.from_numpy(y_train.copy()).long()
    x_test = torch.from_numpy(x_test.copy()).float()
    y_test = torch.from_numpy(y_test.copy()).long()
    return x_train, y_train, x_test, y_test
    

def Xy_load(i_user):
    with open(dataset_config["qvar_dataset_start_indices_path"], 'r') as file:
        start_indices_dict = json.load(file)
    x_user = np.empty((0, 9, 240))
    y_user = np.empty(0)
    sos = signal.cheby2(4, 30, 45, 'lowpass', fs=240, output='sos')
    for path, start_index in start_indices_dict[f'user_{i_user:0>2}'].items():
        if start_index < 0:
            continue
        with open(path, 'r') as file:
            data = json.load(file)
        x_sensing = np.array([data[sensing] for sensing in SENSING_DIMENSIONS])

        # x_sensing_filtered = signal.sosfilt(sos, x_sensing)
        # x_slice = x_sensing_filtered[:, start_index: start_index + 240]

        x_slice = x_sensing[:, start_index: start_index + 240]

        x_user = np.concatenate((x_user, x_slice[np.newaxis, :, :]), 0)
        y_user = np.concatenate((y_user, np.array([CLASSES.index(data['gesture'])])))
    return x_user, y_user
    

def Xy_TrainTest(fold_n):
    print('loading QVAR dataset...')

    x_train = np.empty((0, 9, 240))
    y_train = np.empty(0)
    x_test = np.empty((0, 9, 240))
    y_test = np.empty(0)

    with mp.Pool() as pool:
        for x_user, y_user in pool.map(Xy_load, [k for k in range(1, 21) if k != fold_n]):
            x_train = np.concatenate((x_train, x_user), 0)
            y_train = np.concatenate((y_train, y_user), 0)

    x_test, y_test = Xy_load(fold_n)
    
    x_train = torch.from_numpy(x_train.copy()).float()
    y_train = torch.from_numpy(y_train.copy()).long()
    x_test = torch.from_numpy(x_test.copy()).float()
    y_test = torch.from_numpy(y_test.copy()).long()

    print('loading complete.')
    return x_train, y_train, x_test, y_test


def preprocess(x_before, mean_std_path, fold_n):
    # downsampling 
    x_after = x_before[:, :, ::6]

    # mean-std normalization
    # with open(mean_std_path, 'r') as file:
    #     mean_std = json.load(file)
    # ms = mean_std[f'fold_{fold_n:0>2}']
    # for i in range(x_after.shape[0]):
    #     x_after[i] = (x_after[i] - torch.tensor(ms['mean'])) / torch.tensor(ms['std'])

    # # channel-wise min-max
    # for i in range(x_after.shape[0]):
    #     x_after[i] = (x_after[i] - torch.min(x_after[i], dim=1)[0].view(-1, 1)) / (torch.max(x_after[i], dim=1)[0].view(-1, 1) - torch.min(x_after[i], dim=1)[0].view(-1, 1))

    # # global min-max
    # for i in range(x_after.shape[0]):
    #     x_after[i] = (x_after[i] - torch.min(x_after[i])) / (torch.max(x_after[i]) - torch.min(x_after[i]))
    return x_after


def plot_qvar(qvar_sample):
    plt.figure()
    for i_channel in range(3, 9):
        plt.plot(np.arange(qvar_sample.shape[-1]), qvar_sample[i_channel])
    plt.show()


def get_start_index(file_path):
    with open(file_path, 'r') as file:
        data = json.load(file)
    for i_channel in range(6):
        if len(data[f'qvar_ch{i_channel}']) != 600:
            return -1
    qvar_sample = np.array([data[f'qvar_ch{i_channel}'] for i_channel in range(6)])
    window_stride = 40
    window_length = 240
    reference_window_length = 80
    debiased_qvar_sample = np.zeros(qvar_sample.shape)
    for i_channel in range(6):
        bias = np.mean(qvar_sample[i_channel, 0:reference_window_length])
        debiased_qvar_sample[i_channel] = qvar_sample[i_channel] - bias
    weight_windows = sliding_window_view(np.abs(debiased_qvar_sample), (debiased_qvar_sample.shape[0], window_length))[0, ::window_stride]
    weights = np.sum(weight_windows, axis=(1,2))
    argmax_window_id = np.argmax(weights)
    start_index = argmax_window_id * window_stride
    # plt.figure()
    # for i_channel in range(6):
    #     plt.plot(np.arange(qvar_sample.shape[-1]), qvar_sample[i_channel])
    # plt.vlines(x=start_index, ymin=np.min(qvar_sample), ymax=np.max(qvar_sample))
    # plt.vlines(x=start_index+window_length, ymin=np.min(qvar_sample), ymax=np.max(qvar_sample))
    # plt.show()
    return start_index
        

def get_start_indices(file_paths):
    with mp.Pool() as pool:
        start_indices = pool.map(get_start_index, file_paths)
    return start_indices


def dump_json_start_indices(dataset_root, target_path):
    user_dict = {f'user_{i_user:0>2}':{} for i_user in range(1, 21)}
    for i_user in range(1, 21):
        _dir = os.path.join(dataset_root, f'user_{i_user:0>2}')
        user_file_paths = [os.path.join(_dir, name) for name in os.listdir(_dir)]
        user_start_indices = get_start_indices(user_file_paths)
        user_dict[f'user_{i_user:0>2}'] = {path:int(start_index) for path, start_index in zip(user_file_paths, user_start_indices)}
    with open(target_path, 'w') as file:
        json.dump(user_dict, file, indent=4)


def get_mean_std(fold):
    x_train, _, _, _ = Xy_TrainTest(dataset_config["qvar_dataset_start_indices_path"], fold)
    mean = np.mean(np.transpose(x_train.numpy(), (1, 0, 2)), axis=(1, 2)).reshape(x_train.shape[1], 1)
    std = np.std(np.transpose(x_train.numpy(), (1, 0, 2)), axis=(1, 2)).reshape(x_train.shape[1], 1)
    return mean.tolist(), std.tolist()


def dump_json_mean_std(dataset_root, target_path):
    mean_std_dict = {}
    with mp.Pool() as pool:
        for fold, (mean, std) in enumerate(pool.map(get_mean_std, range(1, 21)), 1):
            mean_std_dict[f'fold_{fold:0>2}'] = {'mean': mean, 'std': std} 
    print(mean_std_dict)
    with open(target_path, 'w') as file:
        json.dump(mean_std_dict, file, indent=4)


def get_mean_std_kfold(fold):
    x_train, _, _, _ = Xy_TrainTest_Kfold(dataset_config["qvar_dataset_start_indices_path"], fold)
    mean = np.mean(np.transpose(x_train.numpy(), (1, 0, 2)), axis=(1, 2)).reshape(x_train.shape[1], 1)
    std = np.std(np.transpose(x_train.numpy(), (1, 0, 2)), axis=(1, 2)).reshape(x_train.shape[1], 1)
    return mean.tolist(), std.tolist()


def dump_json_mean_std_kfold(dataset_root, target_path):
    mean_std_dict = {}
    with mp.Pool() as pool:
        for fold, (mean, std) in enumerate(pool.map(get_mean_std, range(1, 11)), 1):
            mean_std_dict[f'fold_{fold:0>2}'] = {'mean': mean, 'std': std} 
    print(mean_std_dict)
    with open(target_path, 'w') as file:
        json.dump(mean_std_dict, file, indent=4)


def dump_txt():
    txt_root = dataset_config["qvar_dataset_txt_root"]
    with open(dataset_config["qvar_dataset_start_indices_path"], 'r') as file:
        start_indices_dict = json.load(file)
    for i_user in range(1, 21):
        _dir = os.path.join(txt_root, f'user_{i_user:0>2}')
        if not os.path.exists(_dir):
            os.makedirs(_dir)
        for json_path, start_index in tqdm(start_indices_dict[f'user_{i_user:0>2}'].items(), desc=f'user_{i_user:0>2}'):
            if start_index < 0:
                continue
            with open(json_path, 'r') as json_file:
                json_data = json.load(json_file)
            y_true = CLASSES.index(json_data['gesture'])
            x_sensing = np.array([json_data[sensing] for sensing in SENSING_DIMENSIONS])  # (9, 600)
            x_slice = x_sensing[:, start_index: start_index + 240]  # (9, 240)
            x_slice = x_slice[:, ::6]  # (9, 40)
            x_slice = np.transpose(x_slice)  # (40, 9)
            
            txt_name, _ = os.path.splitext(json_path)
            txt_name = os.path.basename(txt_name) + '.txt'
            with open(os.path.join(_dir, txt_name), 'w') as txt_file:
                for i in range(x_slice.shape[0]):
                    for j in range(x_slice.shape[1]):
                        txt_file.write(str(x_slice[i, j]))
                        txt_file.write('\r\n')
                txt_file.write(str(y_true))
                


if __name__ == '__main__':
    dump_json_start_indices(dataset_config["qvar_dataset_root"], dataset_config["qvar_dataset_start_indices_path"])

