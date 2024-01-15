import os
import pickle
import numpy as np
import torch
from matplotlib import pyplot as plt
from sklearn.manifold import TSNE
from model_definitions import ResNetBackBone, Classifier
from dataman_qvar import Xy_TrainTest


user_markers = ['o', '^', 'x', 'p', '*', 'h', 'H']
# class_colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k', 'w']
class_colors = ['C0', 'C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8', 'C9']

device = torch.device("cuda") 


def get_embedding(x, fold):
    backbone_path = f'../saved_models/qvar/pt/fold_{fold}_pre_backbone_fullvalid_b32.pt'
    backbone = ResNetBackBone(in_channels=9, mid_channels=32, out_channels=32).to(device)
    backbone.load_state_dict(torch.load(backbone_path))
    backbone.eval()
    x_embedding = backbone(x)
    return x_embedding


if __name__ == '__main__':
    for fold in range(1, 21):
        x_train, y_train, x_test, y_test = Xy_TrainTest(fold)

        x_train = x_train.detach().cpu().numpy()
        y_train = y_train.detach().cpu().numpy()
        x_test = x_test.detach().cpu().numpy()
        y_test = y_test.detach().cpu().numpy()

        x = np.concatenate((x_train, x_test), 0)
        y = np.concatenate((y_train, y_test), 0)
        u = np.concatenate((np.zeros(x_train.shape[0]), np.ones(x_test.shape[0])), 0)

        y_mask = y < 5
        x = x[y_mask]
        y = y[y_mask]
        u = u[y_mask]

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

        plt.savefig(f'../figures/qvar_tsne_fold{fold}.pdf')

