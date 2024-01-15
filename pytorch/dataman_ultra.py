import os
import pickle
import random
import numpy as np
import torch


CLASSES = ['leftwards', 'rightwards', 'backwards', 'forward', 'outwards', 'inward', 'beckoning', 'sliding']


def Xy_TrainTest(dataset_root, fold_n):
    x_train = np.empty((0, 45, 19))
    y_train = np.empty((0))
    x_test = np.empty((0, 45, 19)) 
    y_test = np.empty((0))

    print(f'loading dataset {dataset_root}...')
    for i_sub in [k for k in range(7) if k != fold_n]:
        for i_cls in range(8):
            for file_name in os.listdir(_dir := os.path.join(dataset_root, f'subject_{i_sub}', f'class_{i_cls}')):
                if not file_name.endswith('.pkl'):
                    continue
                with open(os.path.join(_dir, file_name), 'rb') as file:
                    data = pickle.load(file)
                x_train = np.concatenate((x_train, data['X'][0:855].reshape(1, 45, 19)), 0)
                y_train = np.concatenate((y_train, np.array([i_cls])), 0)

    for i_cls in range(8):
        for file_name in os.listdir(_dir := os.path.join(dataset_root, f'subject_{fold_n}', f'class_{i_cls}')):
            if not file_name.endswith('.pkl'):
                continue
            with open(os.path.join(_dir, file_name), 'rb') as file:
                data = pickle.load(file)
            x_test = np.concatenate((x_test, data['X'][0:855].reshape(1, 45, 19)), 0)
            y_test = np.concatenate((y_test, np.array([i_cls])), 0)

    x_train = torch.from_numpy(x_train.copy()).float()
    y_train = torch.from_numpy(y_train.copy()).long()
    x_test = torch.from_numpy(x_test.copy()).float()
    y_test = torch.from_numpy(y_test.copy()).long()

    print('loading complete.')
    return x_train, y_train, x_test, y_test


def Xy_TrainTest_Kfold(dataset_root, fold_n):
    x_whole = np.empty((0, 45, 19))
    y_whole = np.empty((0))

    for i_sub in range(7):
        for i_cls in range(8):
            for file_name in os.listdir(_dir := os.path.join(dataset_root, f'subject_{i_sub}', f'class_{i_cls}')):
                if not file_name.endswith('.pkl'):
                    continue
                with open(os.path.join(_dir, file_name), 'rb') as file:
                    data = pickle.load(file)
                x_whole = np.concatenate((x_whole, data['X'][0:855].reshape(1, 45, 19)), 0)
                y_whole = np.concatenate((y_whole, np.array([i_cls])), 0)

    shuffled_indices = np.arange(x_whole.shape[0])
    random.Random(136).shuffle(shuffled_indices)
    n_sample_per_segment = x_whole.shape[0] // 7
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

    print('loading complete.')
    return x_train, y_train, x_test, y_test


if __name__ == '__main__':
    pass
