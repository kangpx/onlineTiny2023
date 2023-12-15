import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.nn.modules import Identity


class ResidualBlock3(nn.Module):
    def __init__(self, in_channels, mid_channels, out_channels):
        super().__init__()
        self.layer1 = nn.Sequential(
            nn.Conv1d(in_channels=in_channels, out_channels=mid_channels, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm1d(num_features=mid_channels),
            nn.ReLU(inplace=True),
            nn.Dropout(0.1)
        )
        self.layer2 = nn.Sequential(
            nn.Conv1d(in_channels=mid_channels, out_channels=mid_channels, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm1d(num_features=mid_channels),
            nn.ReLU(inplace=True),
            nn.Dropout(0.1)
        )

        self.conv = nn.Conv1d(in_channels=mid_channels, out_channels=out_channels, kernel_size=3, stride=1, padding=1)
        self.bn = nn.BatchNorm1d(num_features=out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.dropout = nn.Dropout(0.1)

        self.channel_adapt = nn.Conv1d(in_channels=mid_channels, out_channels=out_channels, kernel_size=1, stride=1, padding=0) if mid_channels != out_channels else nn.Identity()

    def forward(self, x):
        identity = x
        out = self.layer1(x)
        out = self.layer2(out)
        out = self.conv(out)
        out = self.bn(out)
        #if not isinstance(self.channel_adapt, nn.Identity):
        #for i in range(0, 40):
        #    print(i, out.view(out.size(0), -1)[0, i].item())
        #    #print(i, self.channel_adapt(identity).view(out.size(0),-1)[0,i].item())
        out += self.channel_adapt(identity)
        out = self.relu(out)
        out = self.dropout(out)
        return out


class ResidualBlock2(nn.Module):
    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.layer1 = nn.Sequential(
            nn.Conv1d(in_channels=in_channels, out_channels=out_channels, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm1d(num_features=out_channels),
            nn.ReLU(inplace=True),
            nn.Dropout(0.1)
        )
        self.conv = nn.Conv1d(in_channels=out_channels, out_channels=out_channels, kernel_size=3, stride=1, padding=1)
        self.bn = nn.BatchNorm1d(num_features=out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.dropout = nn.Dropout(0.1)

    def forward(self, x):
        identity = x
        out = self.layer1(x)
        out = self.conv(out)
        out = self.bn(out)
        out += identity
        out = self.relu(out)
        out = self.dropout(out)
        return out


class BottleNeckResidualBlock3(nn.Module):
    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.layer1 = nn.Sequential(
            nn.Conv1d(in_channels=in_channels, out_channels=out_channels, kernel_size=1, stride=1),
            nn.BatchNorm1d(num_features=out_channels),
            nn.ReLU(inplace=True),
            nn.Dropout(0.1)
        )
        self.layer2 = nn.Sequential(
            nn.Conv1d(in_channels=out_channels, out_channels=out_channels, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm1d(num_features=out_channels),
            nn.ReLU(inplace=True),
            nn.Dropout(0.1)
        )

        self.conv = nn.Conv1d(in_channels=out_channels, out_channels=out_channels, kernel_size=1, stride=1)
        self.bn = nn.BatchNorm1d(num_features=out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.dropout = nn.Dropout(0.1)

    def forward(self, x):
        identity = x
        out = self.layer1(x)
        out = self.layer2(out)
        out = self.conv(out)
        out = self.bn(out)
        out += identity
        out = self.relu(out)
        out = self.dropout(out)
        return out


class ResNetBackBone(nn.Module):
    def __init__(self, in_channels, mid_channels, out_channels):
        super().__init__()
        self.conv = nn.Conv1d(in_channels=in_channels, out_channels=mid_channels, kernel_size=3, stride=1, padding=1)
        self.bn = nn.BatchNorm1d(num_features=mid_channels)
        self.relu = nn.ReLU(inplace=True)
        self.dropout = nn.Dropout(0.1)

        self.identity1 = ResidualBlock3(in_channels=mid_channels, mid_channels=mid_channels, out_channels=mid_channels)
        self.identity2 = ResidualBlock3(in_channels=mid_channels, mid_channels=mid_channels, out_channels=mid_channels)
        self.identity3 = ResidualBlock3(in_channels=mid_channels, mid_channels=mid_channels, out_channels=out_channels)

        self.flatten = nn.Flatten()

        # self.identity1 = ResidualBlock2(in_channels=out_channels, out_channels=out_channels)
        # self.identity2 = ResidualBlock2(in_channels=out_channels, out_channels=out_channels)
        # self.identity3 = ResidualBlock2(in_channels=out_channels, out_channels=out_channels)

        # self.identity1 = BottleNeckResidualBlock3(in_channels=out_channels, out_channels=out_channels)
        # self.identity2 = BottleNeckResidualBlock3(in_channels=out_channels, out_channels=out_channels)
        # self.identity3 = BottleNeckResidualBlock3(in_channels=out_channels, out_channels=out_channels)
        # self.flatten = nn.Flatten()
        
    def forward(self, x):
        out = self.conv(x)
        out = self.bn(out)
        out = self.relu(out)
        #print(out[:, 0, :40])
        out = self.dropout(out)
        #for i in range(0, 40):
        #    print(i, out.view(out.size(0), -1)[0,i].item())
        out = self.identity1(out)
        out = self.identity2(out)
        out = self.identity3(out)
        #out = out.view(out.size(0), -1)
        out = self.flatten(out)
        return out


class Classifier(nn.Module):
    def __init__(self, in_features, out_features):
        super().__init__()
        self.fc = nn.Linear(in_features, out_features)

    def forward(self, x):
        out = self.fc(x)
        return out


class ResNet(nn.Module):
    def __init__(self, backbone, classifier):
        super().__init__()
        self.backbone = backbone
        self.classifier = classifier
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        out = self.backbone(x)
        out = self.classifier(out)
        out = self.softmax(out)
        return out
