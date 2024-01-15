import os
import pickle
import numpy as np
import torch
from matplotlib import pyplot as plt
from sklearn.manifold import TSNE
from model_definitions import ResNetBackBone, Classifier
from dataman_gym import Xy_TrainTest


user_markers = ['o', '^', 'x', 'p', '*', 'h', 'H']
# class_colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k', 'w']
class_colors = ['C0', 'C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8', 'C9', 'C10', 'C11']

device = torch.device("cuda") 


def get_embedding(x, fold):
    backbone_path = f'../saved_models/gym/pt/fold_{fold}_pre_backbone_fullvalid_b32_s20.pt'
    backbone = ResNetBackBone(in_channels=7, mid_channels=32, out_channels=32).to(device)
    backbone.load_state_dict(torch.load(backbone_path))
    backbone.eval()
    x_embedding = backbone(x)
    return x_embedding


if __name__ == '__main__':
    root = '../datasets/Gym_Data.csv'
    for fold in range(1, 11):
        x_train, y_train, x_test, y_test = Xy_TrainTest(root, fold)

        x_train = x_train.detach().cpu().numpy()
        y_train = y_train.detach().cpu().numpy()
        x_test = x_test.detach().cpu().numpy()
        y_test = y_test.detach().cpu().numpy()
        
        cls_cnt_train = [np.count_nonzero(y_train == i) for i in range(12)]
        cls_cnt_test = [np.count_nonzero(y_test == i) for i in range(12)]
        min_cnt_train = np.min(cls_cnt_train)
        min_cnt_test = np.min(cls_cnt_test)

        x_train_truncated = np.empty((0, 7 ,40))
        y_train_truncated = np.empty((0))
        x_test_truncated = np.empty((0, 7, 40))
        y_test_truncated = np.empty((0))

        for i_cls in range(12):
            x_train_truncated = np.concatenate((x_train_truncated, x_train[y_train == i_cls][:min_cnt_train]), 0)
            y_train_truncated = np.concatenate((y_train_truncated, y_train[y_train == i_cls][:min_cnt_train]), 0)
            x_test_truncated = np.concatenate((x_test_truncated, x_test[y_test == i_cls][:min_cnt_test]), 0)
            y_test_truncated = np.concatenate((y_test_truncated, y_test[y_test == i_cls][:min_cnt_test]), 0)

        x = np.concatenate((x_train_truncated, x_test_truncated), 0)
        y = np.concatenate((y_test_truncated, y_test_truncated), 0)
        u = np.concatenate((np.zeros(x_train.shape[0]), np.ones(x_test.shape[0])), 0)

        x_embedding = get_embedding(torch.from_numpy(x).float().to(device), fold).detach().cpu().numpy()

        tsne = TSNE(n_components=2, init='pca', random_state=100)
        result = tsne.fit_transform(x.reshape(x.shape[0], -1))
        x_min, x_max = result.min(0), result.max(0)
        result = (result - x_min) / (x_max - x_min)

        tsne_embedding = TSNE(n_components=2, init='pca', random_state=100)
        result_embedding = tsne_embedding.fit_transform(x_embedding)
        x_min, x_max = result_embedding.min(0), result_embedding.max(0)
        result_embedding = (result_embedding - x_min) / (x_max - x_min)

        fig = plt.figure(figsize=(10,20))
        plt.subplot(2, 1, 1)
        for i in range(x.shape[0]):
            plt.scatter(result[i, 0], result[i, 1], color=class_colors[int(y[i])], marker=user_markers[int(u[i])], s=10, alpha=0.3 if u[i] == 0 else None)
        plt.subplot(2, 1, 2)
        for i in range(x_embedding.shape[0]):
            plt.scatter(result_embedding[i, 0], result_embedding[i, 1], color=class_colors[int(y[i])], marker=user_markers[int(u[i])], s=10, alpha=0.3 if u[i] == 0 else None)

        plt.savefig(f'../figures/gym_tsne_fold{fold}.pdf')

