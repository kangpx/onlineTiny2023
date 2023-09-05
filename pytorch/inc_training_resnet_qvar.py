import os
import datetime
import pickle as pkl
import json
import random
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.optim.lr_scheduler import CosineAnnealingLR, CosineAnnealingWarmRestarts
from torch.utils.data import DataLoader, TensorDataset, WeightedRandomSampler
import torch.onnx
import onnxruntime
from onnxruntime.quantization import QuantFormat, QuantType, StaticQuantConfig, quantize, CalibrationMethod
from onnxruntime.quantization import CalibrationDataReader
from onnxruntime.quantization.shape_inference import quant_pre_process
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, confusion_matrix, f1_score, precision_score, recall_score
from dataman_qvar import CLASSES, SENSING_DIMENSIONS, Xy_TrainTest, Xy_TrainTest_Kfold, preprocess
from model_definitions import ResNetBackBone, Classifier, ResNet
from early_stopping import EarlyStopping
from tqdm import tqdm


device = torch.device('cuda')
print(f'device: {device}')

with open('../dataset_config.json', 'r') as json_file:
    dataset_config = json.load(json_file)


def get_dataloader_kfold(fold):
    x_train, y_train, x_test, y_test = Xy_TrainTest_Kfold(fold_n=fold)
    x_train = preprocess(x_train, dataset_config["qvar_dataset_mean_std_kfold_nofilter_path"], fold)
    x_test = preprocess(x_test, dataset_config["qvar_dataset_mean_std_kfold_nofilter_path"], fold)
    x_train, x_valid, y_train, y_valid = train_test_split(x_train, y_train, train_size=0.8, random_state=6507+fold)

    train_dataset = TensorDataset(x_train, y_train)
    valid_dataset = TensorDataset(x_valid, y_valid)
    test_dataset = TensorDataset(x_test, y_test)

    train_class_weights = torch.tensor([1.0 for _ in range(len(CLASSES))])

    train_loader = DataLoader(train_dataset, shuffle=True, batch_size=64, drop_last=False)
    valid_loader = DataLoader(valid_dataset, shuffle=False, batch_size=64, drop_last=False)
    test_loader = DataLoader(test_dataset, shuffle=False, batch_size=64, drop_last=False)

    dataset_summary = pd.DataFrame(index=CLASSES+['total'],
                                    data={'# train':[(y_train == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(train_dataset)], 
                                          '# valid':[(y_valid == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(valid_dataset)],
                                          '# test':[(y_test == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(test_dataset)],})
    print(dataset_summary)
    print('class_weights:')
    for i_cls, cls in enumerate(CLASSES):
        print(f'{cls}: {train_class_weights[i_cls]}')

    return train_loader, valid_loader, test_loader, None, None, train_class_weights


def get_dataloader(fold, include_incnu=True):
    x_train, y_train, x_test, y_test = Xy_TrainTest(fold_n=fold)
    x_train = preprocess(x_train, dataset_config["qvar_dataset_mean_std_nofilter_path"], fold)
    x_test = preprocess(x_test, dataset_config["qvar_dataset_mean_std_nofilter_path"], fold)
    x_test, x_incu, y_test, y_incu = train_test_split(x_test, y_test, train_size=0.6, random_state=136+fold)

    incu_indices = list(range(y_incu.shape[0]))
    random.Random(10).shuffle(incu_indices)
    x_incu = x_incu[incu_indices]
    y_incu = y_incu[incu_indices]
    np.savez(os.path.join(dataset_config["qvar_incu_dataset_root"], f'fold_{fold}_incu_dataset'), x_incu=x_incu.detach().numpy(), y_incu=y_incu.detach().numpy(), x_test=x_test.detach().numpy(), y_test=y_test.detach().numpy())

    x_train, x_valid, y_train, y_valid = train_test_split(x_train, y_train, train_size=0.8, random_state=6507+fold)
    if include_incnu:
        x_valid, x_incnu, y_valid, y_incnu = train_test_split(x_valid, y_valid, test_size=x_incu.shape[0], random_state=6133+fold)
        incnu_indices = list(range(y_incnu.shape[0]))
        random.Random(20).shuffle(incnu_indices)
        x_incnu = x_incnu[incnu_indices]
        y_incnu = y_incnu[incnu_indices]

    train_dataset = TensorDataset(x_train, y_train)
    valid_dataset = TensorDataset(x_valid, y_valid)
    test_dataset = TensorDataset(x_test, y_test)
    incu_dataset = TensorDataset(x_incu, y_incu)
    if include_incnu:
        incnu_dataset = TensorDataset(x_incnu, y_incnu)
    else:
        incnu_dataset = None

    train_class_weights = torch.tensor([1.0 for _ in range(len(CLASSES))])

    train_loader = DataLoader(train_dataset, shuffle=True, batch_size=64, drop_last=False)
    valid_loader = DataLoader(valid_dataset, shuffle=False, batch_size=64, drop_last=False)
    test_loader = DataLoader(test_dataset, shuffle=False, batch_size=64, drop_last=False)
    incu_loader = DataLoader(incu_dataset, shuffle=False, batch_size=1, drop_last=False)
    if include_incnu:
        incnu_loader = DataLoader(incnu_dataset, shuffle=False, batch_size=1, drop_last=False)
    else:
        incnu_loader = None

    if include_incnu:
        dataset_summary = pd.DataFrame(index=CLASSES+['total'],
                                        data={'# train':[(y_train == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(train_dataset)],
                                                '# valid':[(y_valid == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(valid_dataset)],
                                                '# test':[(y_test == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(test_dataset)],
                                                '# incu':[(y_incu == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(incu_dataset)],
                                                '# incnu':[(y_incnu == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(incnu_dataset)],})
    else:
        dataset_summary = pd.DataFrame(index=CLASSES+['total'],
                                        data={'# train':[(y_train == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(train_dataset)],
                                                '# valid':[(y_valid == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(valid_dataset)],
                                                '# test':[(y_test == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(test_dataset)],
                                                '# incu':[(y_incu == i_cls).sum().item() for i_cls in range(len(CLASSES))] + [len(incu_dataset)],
                                                '# incnu':[0 for i_cls in range(len(CLASSES))] + [0],})

    print(dataset_summary)
    print('class_weights:')
    for i_cls, cls in enumerate(CLASSES):
        print(f'{cls}: {train_class_weights[i_cls]}')

    return train_loader, valid_loader, test_loader, incu_loader, incnu_loader, train_class_weights


def pre_train(train_loader, valid_loader, backbone_path, classifier_path, history_path, class_weights):
    #--------------------------------------------------------------------#
    #                     pre-training configuration                     #
    #--------------------------------------------------------------------#
    backbone = ResNetBackBone(in_channels=len(SENSING_DIMENSIONS), out_channels=64).to(device)
    classifier = Classifier(in_features=64*40, out_features=len(CLASSES)).to(device)
    print(backbone)
    print(classifier)
    total_params_backbone = sum(p.numel() for p in backbone.parameters())
    total_params_classifier = sum(p.numel() for p in classifier.parameters())
    total_params = total_params_backbone + total_params_classifier
    print(f"Number of parameters (backbone + classifier): {total_params}")

    optimizer_backbone = optim.Adam(backbone.parameters(), lr=0.001, betas=(0.9, 0.999), eps=1e-08)
    optimizer_classifier = optim.Adam(classifier.parameters(), lr=0.001, betas=(0.9, 0.999), eps=1e-08)
    
    loss_fn = nn.CrossEntropyLoss(weight=class_weights).to(device)
    
    n_epochs = 1000

    early_stopping = EarlyStopping(patience=100, verbose=True, path=[backbone_path, classifier_path])

    log_period = 100

    verbose = True

    # history = pd.DataFrame(columns=['epoch', 'train_loss', 'train_accuracy', 'valid_loss', 'valid_accuracy'])
    history = {'epoch':[], 'train_loss':[], 'train_accuracy':[], 'valid_loss':[], 'valid_accuracy':[]}

    #--------------------------------------------------------------------#
    #                         start pre-training                         #
    #--------------------------------------------------------------------#
    print('pre-training started.')
    nowtime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print('==========' * 8 + f'{nowtime}')

    for epoch in range(n_epochs):
        #--------------------------------------------------------------------#
        #                              training                              #
        #--------------------------------------------------------------------#
        train_loss_sum = 0.0
        train_correct_sum = 0.0
        train_total_sum = 0.0
        backbone.train()
        classifier.train()
        for i_batch, (x_batch, y_batch) in enumerate(train_loader):
            x_batch = x_batch.to(device)
            y_batch = y_batch.to(device)

            optimizer_backbone.zero_grad()
            optimizer_classifier.zero_grad()

            x_embedding = backbone(x_batch)
            y_pred = classifier(x_embedding)
            loss = loss_fn(y_pred, y_batch)
            loss.backward()

            optimizer_backbone.step()
            optimizer_classifier.step()

            y_pred_cls = torch.argmax(nn.Softmax(dim=1)(y_pred), dim=1).detach()
            train_loss_sum += loss.item()
            train_correct_sum += (y_pred_cls == y_batch).sum().item()
            train_total_sum += y_pred_cls.shape[0]

            if verbose and (i_batch % log_period == 0):
                print(f'[epoch-batch=[{epoch}-{i_batch}] loss: {train_loss_sum / (i_batch + 1)}, accuracy: {train_correct_sum / train_total_sum}')

        #--------------------------------------------------------------------#
        #                             validation                             #
        #--------------------------------------------------------------------#
        valid_loss_sum = 0.0
        valid_correct_sum = 0.0
        valid_total_sum = 0.0
        backbone.eval()
        classifier.eval()
        for i_batch, (x_batch, y_batch) in enumerate(valid_loader):
            x_batch = x_batch.to(device)
            y_batch = y_batch.to(device)

            with torch.no_grad():
                x_embedding = backbone(x_batch)
                y_pred = classifier(x_embedding)
                loss = loss_fn(y_pred, y_batch)
                y_pred_cls = torch.argmax(nn.Softmax(dim=1)(y_pred), dim=1).detach()

            valid_loss_sum += loss.item()
            valid_correct_sum += (y_pred_cls == y_batch).sum().item()
            valid_total_sum += y_pred_cls.shape[0]

        #--------------------------------------------------------------------#
        #                           epoch summary                            #
        #--------------------------------------------------------------------#
        print(f'-------------------------- epoch-{epoch} --------------------------')
        print(f'train_loss: {train_loss_sum / len(train_loader):.3}, train_acc: {train_correct_sum / train_total_sum:.3}')
        print(f'valid_loss: {valid_loss_sum / len(valid_loader):.3}, valid_acc: {valid_correct_sum / valid_total_sum:.3}')

        history['epoch'].append(epoch)
        history['train_loss'].append(train_loss_sum / len(train_loader))
        history['train_accuracy'].append(train_correct_sum / train_total_sum)
        history['valid_loss'].append(valid_loss_sum / len(valid_loader))
        history['valid_accuracy'].append(valid_correct_sum / valid_total_sum)

        nowtime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        print('==========' * 8 + f'{nowtime}')

        #--------------------------------------------------------------------#
        #                        check early stopping                        #
        #--------------------------------------------------------------------#
        early_stopping(valid_loss_sum / len(valid_loader), [backbone, classifier])
        if early_stopping.early_stop:
            print('early stopping.')
            break

    #--------------------------------------------------------------------#
    #                            save history                            #
    #--------------------------------------------------------------------#
    print(f'saving history to {history_path}...')
    with open(history_path, 'wb') as file:
        pkl.dump(history, file)

    print('pre-training finished.')

    backbone.load_state_dict(torch.load(backbone_path))
    classifier.load_state_dict(torch.load(classifier_path))

    return (backbone, classifier), history


def inc_training(backbone, classifier, inc_loader, test_loader, classifier_path, history_path, class_weights):
    #--------------------------------------------------------------------#
    #                     inc-training configuration                     #
    #--------------------------------------------------------------------#
    backbone.eval()
    classifier.train()

    loss_fn = nn.CrossEntropyLoss(weight=class_weights).to(device)

    optimizer_classifier = optim.SGD(classifier.parameters(), lr=0.002, momentum=0.5)

    n_epochs = 5 

    log_period = 100

    verbose = True

    history = {'conf_mat':[], 'accuracy':[], 'precision':[], 'recall':[], 'f1':[]}

    #--------------------------------------------------------------------#
    #                            inc-training                            #
    #--------------------------------------------------------------------#
    if inc_loader is None:
        print(f'saving classifier to {classifier_path}...')
        torch.save(classifier.state_dict(), classifier_path)
        print(f'saving history to {history_path}...')
        with open(history_path, 'wb') as file:
            pkl.dump(history, file)
        return classifier, history

    print('inc-training started.')
    nowtime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print('==========' * 8 + f'{nowtime}')

    for epoch in range(n_epochs):
        #--------------------------------------------------------------------#
        #                              training                              #
        #--------------------------------------------------------------------#
        for i_batch, (x_batch, y_batch) in enumerate(inc_loader):
            backbone.eval()
            classifier.train()

            x_batch = x_batch.to(device)
            y_batch = y_batch.to(device)

            optimizer_classifier.zero_grad()

            x_embedding = backbone(x_batch).detach()
            y_pred = classifier(x_embedding)

            loss = loss_fn(y_pred, y_batch)
            loss.backward()

            optimizer_classifier.step()

            #--------------------------------------------------------------------#
            #                              testing                               #
            #--------------------------------------------------------------------#
            if verbose and (i_batch % log_period == 0):
                conf_mat, accuracy, precision, recall, f1 = testing(backbone, classifier, test_loader, class_weights)
                history['conf_mat'].append(conf_mat)
                history['accuracy'].append(accuracy)
                history['precision'].append(precision)
                history['recall'].append(recall) 
                history['f1'].append(f1)
                print(f'step: [{i_batch} / {len(inc_loader)}], accuracy:{accuracy}, macro_precision: {precision[1]}, weighted_precision: {precision[2]}, macro_recall: {recall[1]}, weighted_recall: {recall[2]}')

    #--------------------------------------------------------------------#
    #                          save classifier                           #
    #--------------------------------------------------------------------#
    print(f'saving classifier to {classifier_path}...')
    torch.save(classifier.state_dict(), classifier_path)

    #--------------------------------------------------------------------#
    #                            save history                            #
    #--------------------------------------------------------------------#
    print(f'saving history to {history_path}...')
    with open(history_path, 'wb') as file:
        pkl.dump(history, file)

    print('inc-training finished.')

    return classifier, history
        

@torch.no_grad()
def testing(backbone, classifier, test_loader, class_weights):
    loss_fn = nn.CrossEntropyLoss(weight=class_weights).to(device)

    backbone.eval()
    classifier.eval()

    test_loss_sum = 0.0
    test_correct_sum = 0.0
    test_total_sum = 0.0

    y_pred_all = torch.tensor([]).to(device)
    y_real_all = torch.tensor([]).to(device)

    if test_loader is None:
        return None, 0.0, (0,0, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0, 0.0, 0.0)

    for _, (x_batch, y_batch) in enumerate(test_loader):
        x_batch = x_batch.to(device)
        y_batch = y_batch.to(device)

        with torch.no_grad():
            x_embedding = backbone(x_batch)
            y_pred = classifier(x_embedding)
            loss = loss_fn(y_pred, y_batch)
            y_pred_cls = torch.argmax(nn.Softmax(dim=1)(y_pred), dim=1).detach()

        test_loss_sum += loss.item()
        test_correct_sum += (y_pred_cls == y_batch).sum().item()
        test_total_sum += y_pred_cls.shape[0]
        y_pred_all = torch.cat((y_pred_all, y_pred_cls))
        y_real_all = torch.cat((y_real_all, y_batch))


    y_pred_all = y_pred_all.cpu().numpy()
    y_real_all = y_real_all.cpu().numpy()

    conf_mat = confusion_matrix(y_real_all, y_pred_all)

    f1s         = f1_score(y_real_all, y_pred_all, average=None)
    macro_f1    = f1_score(y_real_all, y_pred_all, average='macro')
    weighted_f1 = f1_score(y_real_all, y_pred_all, average='weighted')

    precisions         = precision_score(y_real_all, y_pred_all, average=None)
    macro_precision    = precision_score(y_real_all, y_pred_all, average='macro')
    weighted_precision = precision_score(y_real_all, y_pred_all, average='weighted')

    recalls         = recall_score(y_real_all, y_pred_all, average=None)
    macro_recall    = recall_score(y_real_all, y_pred_all, average='macro')
    weighted_recall = recall_score(y_real_all, y_pred_all, average='weighted')

    accuracy = accuracy_score(y_real_all, y_pred_all)

    return conf_mat, accuracy, (precisions, macro_precision, weighted_precision), (recalls, macro_recall, weighted_recall), (f1s, macro_f1, weighted_f1)


def load_model(backbone_path, classifier_path):
    backbone = ResNetBackBone(in_channels=len(SENSING_DIMENSIONS), out_channels=64).to(device)
    classifier = Classifier(in_features=64*40, out_features=len(CLASSES)).to(device)

    backbone.load_state_dict(torch.load(backbone_path))
    classifier.load_state_dict(torch.load(classifier_path))

    return backbone, classifier


class QvarCaliDataReader(CalibrationDataReader):
    def __init__(self, qvar_dataset, onnx_model_path):
        self.enum_data = None
        # Use inference session to get input shape.
        session = onnxruntime.InferenceSession(onnx_model_path, None)
        self.input_name = session.get_inputs()[0].name
        self.ncw_data_list = np.concatenate([qvar_dataset[i][0].detach().numpy()[np.newaxis, np.newaxis, :, :] for i in range(len(qvar_dataset))], 0)
        self.datasize = len(self.ncw_data_list)
        
    def get_next(self):
        if self.enum_data is None:
            self.enum_data = iter(
                [{self.input_name: ncw_data} for ncw_data in self.ncw_data_list]
            )
        return next(self.enum_data, None)

    def rewind(self):
        self.enum_data = None


def main():
    foldlog_pre = pd.DataFrame(data={'accuracy':[], 'macro_precisoin':[], 'weighted_precision':[], 'macro_recall':[], 'weighted_recall':[], 'macro_f1':[], 'weighted_f1':[]})
    foldlog_incu = pd.DataFrame(data={'accuracy':[], 'macro_precisoin':[], 'weighted_precision':[], 'macro_recall':[], 'weighted_recall':[], 'macro_f1':[], 'weighted_f1':[]})
    foldlog_incnu = pd.DataFrame(data={'accuracy':[], 'macro_precisoin':[], 'weighted_precision':[], 'macro_recall':[], 'weighted_recall':[], 'macro_f1':[], 'weighted_f1':[]})

    foldlog_classwise_pre = []
    foldlog_classwise_incu = []
    foldlog_classwise_incnu = []

    include_incnu = True
    
    for fold in tqdm(range(1, 21)):
        bb_pre_path       = f'../saved_models/qvar/pt/fold_{fold}_pre_backbone_{"fullvalid" if not include_incnu else "partvalid"}.pt'
        clf_pre_path      = f'../saved_models/qvar/pt/fold_{fold}_pre_classifier_{"fullvalid" if not include_incnu else "partvalid"}.pt'
        cmb_pre_onnx_path = f'../saved_models/qvar/onnx/fold_{fold}_pre_combination_{"fullvalid" if not include_incnu else "partvalid"}.onnx' 
        clf_incu_path     = f'../saved_models/qvar/pt/fold_{fold}_incu_classifier_{"fullvalid" if not include_incnu else "partvalid"}.pt'
        clf_incnu_path    = f'../saved_models/qvar/pt/fold_{fold}_incnu_classifier_{"fullvalid" if not include_incnu else "partvalid"}.pt'
        his_pre_path      = f'../histories/qvar/fold_{fold}_pre_{"fullvalid" if not include_incnu else "partvalid"}.pkl'
        his_incu_path     = f'../histories/qvar/fold_{fold}_incu_{"fullvalid" if not include_incnu else "partvalid"}.pkl'
        his_incnu_path    = f'../histories/qvar/fold_{fold}_incnu_{"fullvalid" if not include_incnu else "partvalid"}.pkl'

        #--------------------------------------------------------------------#
        #                          data preparation                          #
        #--------------------------------------------------------------------#
        train_loader, valid_loader, test_loader, incu_loader, incnu_loader, class_weights = get_dataloader(fold, include_incnu)

        #--------------------------------------------------------------------#
        #                            pre-training                            #
        #--------------------------------------------------------------------#
        (backbone, classifier), _ = pre_train(train_loader, valid_loader, bb_pre_path, clf_pre_path, his_pre_path, class_weights)

        #--------------------------------------------------------------------#
        #                      testing of pre-training                       #
        #--------------------------------------------------------------------#
        backbone, classifier = load_model(bb_pre_path, clf_pre_path)
        conf_mat_pre, accuracy_pre, precision_pre, recall_pre, f1_pre = testing(backbone, classifier, test_loader, class_weights)
        
        #--------------------------------------------------------------------#
        #               converting pre-training models to onnx               #
        #--------------------------------------------------------------------#
        backbone, classifier = load_model(bb_pre_path, clf_pre_path)
        backbone.eval()
        classifier.eval()
        combination = ResNet(backbone=backbone, classifier=classifier).to(device)
        dummy_input_backbone = torch.randn(1, len(SENSING_DIMENSIONS), 40).to(device)


        torch.onnx.export(combination,
                          dummy_input_backbone,
                          cmb_pre_onnx_path,
                          export_params=True,
                          opset_version=13,
                          do_constant_folding=True,
                          input_names=['modelInput'],
                          output_names=['modelOutput'],
                          dynamic_axes={'modelInput': {0: 'batch_size'}, 'modelOutput': {0: 'batch_size'}}
                          )
        print(f'combination has been converted to onnx and stored in {cmb_pre_onnx_path}')

        #--------------------------------------------------------------------#
        #                           quantize onnx                            #
        #--------------------------------------------------------------------#
        # quant_pre_process(input_model_path=cmb_pre_onnx_path, output_model_path=cmb_pre_onnx_preprocess_path)
        # print(f'combination has been preprocessed and stored in {cmb_pre_onnx_preprocess_path}')
        #
        # dr = QvarCaliDataReader(train_loader.dataset, cmb_pre_onnx_preprocess_path) 
        #  
        # conf = StaticQuantConfig(calibration_data_reader=dr, 
        #                          quant_format=QuantFormat.QDQ, 
        #                          calibrate_method=CalibrationMethod.MinMax,
        #                          optimize_model=False,
        #                          activation_type=QuantType.QInt8,
        #                          weight_type=QuantType.QInt8,
        #                          per_channel=True)
        #     
        # quantize(cmb_pre_onnx_preprocess_path, cmb_pre_onnx_quantize_path, conf)
        # print(f'combination has been quantized and stored in {cmb_pre_onnx_quantize_path}')

        #--------------------------------------------------------------------#
        #                         inc-training-user                          #
        #--------------------------------------------------------------------#
        backbone, classifier = load_model(bb_pre_path, clf_pre_path)
        classifier, history = inc_training(backbone, classifier, incu_loader, test_loader, clf_incu_path, his_incu_path, class_weights)

        #--------------------------------------------------------------------#
        #                    testing of inc-training-user                    #
        #--------------------------------------------------------------------#
        backbone, classifier = load_model(bb_pre_path, clf_incu_path)
        conf_mat_incu, accuracy_incu, precision_incu, recall_incu, f1_incu = testing(backbone, classifier, test_loader, class_weights)

        #--------------------------------------------------------------------#
        #                        inc-training-nonuser                        #
        #--------------------------------------------------------------------#
        backbone, classifier = load_model(bb_pre_path, clf_pre_path)
        classifier, history = inc_training(backbone, classifier, incnu_loader, test_loader, clf_incnu_path, his_incnu_path, class_weights)

        #--------------------------------------------------------------------#
        #                  testing of inc-training-nonuser                   #
        #--------------------------------------------------------------------#
        backbone, classifier = load_model(bb_pre_path, clf_incnu_path)
        conf_mat_incnu, accuracy_incnu, precision_incnu, recall_incnu, f1_incnu = testing(backbone, classifier, test_loader, class_weights)

        #--------------------------------------------------------------------#
        #                testing comparison between pre & inc                #
        #--------------------------------------------------------------------#
        print(conf_mat_pre)
        print(conf_mat_incu)
        print(conf_mat_incnu)

        df_classwise = pd.DataFrame(index=CLASSES, data={'precision_pre':precision_pre[0],
                                                         'precision_pre+incu':precision_incu[0],
                                                         'precision_pre+incnu':precision_incnu[0],
                                                         'recall_pre':recall_pre[0],
                                                         'recall_pre+incu':recall_incu[0],
                                                         'recall_pre+incnu':recall_incnu[0],
                                                         'f1_pre':f1_pre[0],
                                                         'f1_pre+incu':f1_incu[0],
                                                         'f1_pre+incnu':f1_incnu[0]})
        print(df_classwise.round(4))
        foldlog_classwise_pre.append((precision_pre[0], recall_pre[0], f1_pre[0]))
        foldlog_classwise_incu.append((precision_incu[0], recall_incu[0], f1_incu[0]))
        foldlog_classwise_incnu.append((precision_incnu[0], recall_incnu[0], f1_incnu[0]))

        df_overall = pd.DataFrame(index=['accuracy','macro_precision', 'weighted_precision', 'macro_recall', 'weighted_recall', 'macro_f1', 'weighted_f1'],
                                  data={'pre':[accuracy_pre, precision_pre[1], precision_pre[2], recall_pre[1], recall_pre[2], f1_pre[1], f1_pre[2]],
                                        'pre+incu':[accuracy_incu, precision_incu[1], precision_incu[2], recall_incu[1], recall_incu[2], f1_incu[1], f1_incu[2]],
                                        'pre+incnu':[accuracy_incnu, precision_incnu[1], precision_incnu[2], recall_incnu[1], recall_incnu[2], f1_incnu[1], f1_incnu[2]]}) 
        print(df_overall.round(4))

        foldlog_pre.loc[len(foldlog_pre.index)] = [accuracy_pre, precision_pre[1], precision_pre[2], recall_pre[1], recall_pre[2], f1_pre[1], f1_pre[2]] 
        foldlog_incu.loc[len(foldlog_incu.index)] = [accuracy_incu, precision_incu[1], precision_incu[2], recall_incu[1], recall_incu[2], f1_incu[1], f1_incu[2]] 
        foldlog_incnu.loc[len(foldlog_incnu.index)] = [accuracy_incnu, precision_incnu[1], precision_incnu[2], recall_incnu[1], recall_incnu[2], f1_incnu[1], f1_incnu[2]] 
        

    print('mean performances of all folds:')
    df_allfolds = pd.DataFrame(index=['accuracy','macro_precision', 'weighted_precision', 'macro_recall', 'weighted_recall', 'macro_f1', 'weighted_f1'],
                                data={'pre': foldlog_pre.mean().values.tolist(),
                                      'pre+onl(user)':foldlog_incu.mean().values.tolist(),
                                      'pre+onl(nonuser)':foldlog_incnu.mean().values.tolist()}) 
    print(df_allfolds.round(4))


    # # foldwise statistics
    # fold_labels = [f'fold_{i}' for i in range(1, 21)]
    # fold_metrics = {
    #     'accuracy_pre': [foldlog_pre.loc[i, 'accuracy'].round(4) for i in range(20)],
    #     'accuracy_onl_user': [foldlog_incu.loc[i, 'accuracy'].round(4) for i in range(20)],
    #     'accuray_onl_nonuser': [foldlog_incnu.loc[i, 'accuracy'].round(4) for i in range(20)],
    #     'macro_f1_pre': [foldlog_pre.loc[i, 'macro_f1'].round(4) for i in range(20)],
    #     'macro_f1_onl_user': [foldlog_incu.loc[i, 'macro_f1'].round(4) for i in range(20)],
    #     'macro_f1_onl_nonuser': [foldlog_incnu.loc[i, 'macro_f1'].round(4) for i in range(20)],
    # } 
    #
    # y = np.array([2*i for i in range(20)])
    # width = 0.3
    # multiplier = 0
    #
    # fig, ax = plt.subplots(layout='constrained', figsize=(10, 50))
    #
    # for attribute, measurement in fold_metrics.items():
    #     offset = width * multiplier
    #     rects = ax.barh(y + offset, measurement, width, label=attribute)
    #     ax.bar_label(rects, padding=2)
    #     multiplier += 1
    #
    # ax.set_yticks(y + 2 * width, fold_labels, fontsize=15)
    # ax.tick_params(axis='x', labelsize=15)
    # ax.legend(loc='upper right', ncol=2, fontsize=15)
    # ax.set_xlim(0, 1)
    #
    # plt.savefig(f'../figures/foldwise_qvar_{"fullvalid" if not include_incnu else "partvalid"}.jpg')
    #
    # # classwise statistics
    # class_labels = CLASSES
    # class_metrics = {
    #     'precision_pre': [np.round(np.mean([foldlog_classwise_pre[i_fold][0][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'precision_onl_user': [np.round(np.mean([foldlog_classwise_incu[i_fold][0][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'precision_onl_nonuser': [np.round(np.mean([foldlog_classwise_incnu[i_fold][0][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'recall_pre': [np.round(np.mean([foldlog_classwise_pre[i_fold][1][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'recall_onl_user': [np.round(np.mean([foldlog_classwise_incu[i_fold][1][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'recall_onl_nonuser': [np.round(np.mean([foldlog_classwise_incnu[i_fold][1][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'f1_pre': [np.round(np.mean([foldlog_classwise_pre[i_fold][2][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'f1_onl_user': [np.round(np.mean([foldlog_classwise_incu[i_fold][2][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
    #     'f1_onl_nonuser': [np.round(np.mean([foldlog_classwise_incnu[i_fold][2][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)]
    # } 
    #
    # y = np.array([3*i for i in range(10)])
    # width = 0.3
    # multiplier = 0
    #
    # fig, ax = plt.subplots(layout='constrained', figsize=(10, 50))
    #
    # for attribute, measurement in class_metrics.items():
    #     offset = width * multiplier
    #     rects = ax.barh(y + offset, measurement, width, label=attribute)
    #     ax.bar_label(rects, padding=2)
    #     multiplier += 1
    #
    # ax.set_yticks(y + 4 * width, class_labels, fontsize=15)
    # ax.tick_params(axis='x', labelsize=15)
    # ax.legend(loc='upper right', ncol=1, fontsize=15)
    # ax.set_xlim(0, 1)
    #
    # plt.savefig(f'../figures/classwise_qvar_{"fullvalid" if not include_incnu else "partvalid"}.jpg')

    # foldwise statistics
    fold_labels = [f'fold_{i}' for i in range(1, 21)]
    fold_metrics = {
        'accuracy_pre': [foldlog_pre.loc[i, 'accuracy'].round(4) for i in range(20)],
        'accuracy_onl_user': [foldlog_incu.loc[i, 'accuracy'].round(4) for i in range(20)],
        'accuray_onl_nonuser': [foldlog_incnu.loc[i, 'accuracy'].round(4) for i in range(20)],
        'macro_f1_pre': [foldlog_pre.loc[i, 'macro_f1'].round(4) for i in range(20)],
        'macro_f1_onl_user': [foldlog_incu.loc[i, 'macro_f1'].round(4) for i in range(20)],
        'macro_f1_onl_nonuser': [foldlog_incnu.loc[i, 'macro_f1'].round(4) for i in range(20)],
    } 

    x = np.array([2*i for i in range(20)])
    width = 0.3
    multiplier = 0

    fig, ax = plt.subplots(layout='constrained', figsize=(50, 10))

    for attribute, measurement in fold_metrics.items():
        offset = width * multiplier
        rects = ax.bar(x + offset, measurement, width, label=attribute)
        ax.bar_label(rects, padding=2)
        multiplier += 1

    ax.set_xticks(x + 2 * width, fold_labels, fontsize=15)
    ax.tick_params(axis='y', labelsize=15)
    ax.legend(loc='upper left', ncol=2, fontsize=15)
    ax.set_ylim(0, 1)

    plt.savefig(f'../figures/foldwise_qvar_{"fullvalid" if not include_incnu else "partvalid"}.jpg')

    # classwise statistics
    class_labels = CLASSES
    class_metrics = {
        'precision_pre': [np.round(np.mean([foldlog_classwise_pre[i_fold][0][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'precision_onl_user': [np.round(np.mean([foldlog_classwise_incu[i_fold][0][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'precision_onl_nonuser': [np.round(np.mean([foldlog_classwise_incnu[i_fold][0][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'recall_pre': [np.round(np.mean([foldlog_classwise_pre[i_fold][1][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'recall_onl_user': [np.round(np.mean([foldlog_classwise_incu[i_fold][1][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'recall_onl_nonuser': [np.round(np.mean([foldlog_classwise_incnu[i_fold][1][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'f1_pre': [np.round(np.mean([foldlog_classwise_pre[i_fold][2][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'f1_onl_user': [np.round(np.mean([foldlog_classwise_incu[i_fold][2][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)],
        'f1_onl_nonuser': [np.round(np.mean([foldlog_classwise_incnu[i_fold][2][i_cls] for i_fold in range(20)]), 4) for i_cls in range(10)]
    } 

    x = np.array([3*i for i in range(10)])
    width = 0.3
    multiplier = 0

    fig, ax = plt.subplots(layout='constrained', figsize=(50, 10))

    for attribute, measurement in class_metrics.items():
        offset = width * multiplier
        rects = ax.bar(x + offset, measurement, width, label=attribute)
        ax.bar_label(rects, padding=2)
        multiplier += 1

    ax.set_xticks(x + 4 * width, class_labels, fontsize=15)
    ax.tick_params(axis='y', labelsize=15)
    ax.legend(loc='upper left', ncol=1, fontsize=15)
    ax.set_ylim(0, 1)

    plt.savefig(f'../figures/classwise_qvar_{"fullvalid" if not include_incnu else "partvalid"}.jpg')


if __name__ == '__main__':
    main()

