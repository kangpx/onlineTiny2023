import torch
import numpy as np
from model_definitions import Classifier


def main():
    classifier_path = '../saved_models/ultra/pt/fold_0_pre_classifier_fullvalid.pt'
    classifier = Classifier(in_features=64*19, out_features=8)
    classifier.load_state_dict(torch.load(classifier_path, map_location=torch.device('cpu')))
    print(classifier.state_dict())


if __name__ == '__main__':
    main()
