import numpy as np
import torch
from model_definitions import ResNetBackBone, Classifier, ResNet
from dataman_gym import SENSING_DIMENSIONS, SLIDING_WINDOW_LENGTH, CLASSES

if __name__ == '__main__':
    device = torch.device('cuda')
    backbone_path = '../saved_models/gym/pt/fold_1_pre_backbone_fullvalid.pt'
    data = np.load('incu_datasets/gym/fold_1_incu_dataset.npz')
    x_incu, y_incu, x_test, y_test = data['x_incu'], data['y_incu'], data['x_test'], data['y_test']
    x_incu = torch.tensor(x_incu).to(device)
    y_incu = torch.tensor(y_incu).to(device)
    x_test = torch.tensor(x_test).to(device)
    y_test = torch.tensor(y_test).to(device)
    backbone = ResNetBackBone(in_channels=len(SENSING_DIMENSIONS), out_channels=64).to(device)
    classifier = Classifier(in_features=64*SLIDING_WINDOW_LENGTH, out_features=len(CLASSES)).to(device)
    backbone.load_state_dict(torch.load(backbone_path))
    print(backbone(x_test[:1]))
