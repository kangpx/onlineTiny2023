import csv
import os
import numpy as np
from numpy.lib.stride_tricks import sliding_window_view
import pandas as pd
import torch


SLIDING_WINDOW_LENGTH = 40 

SLIDING_WINDOW_STEP = 20 

CLASSES = ['Adductor', 'ArmCurl', 'BenchPress', 'LegCurl', 'LegPress', 'Null', 'Riding', 'RopeSkipping', 'Running', 'Squat', 'StairClimber', 'Walking']
SENSING_DIMENSIONS = ['A_x','A_y','A_z','G_x','G_y','G_z','Body_Capacitance']

# POSITIONS = ['leg', 'pocket', 'wrist']
POSITIONS = ['wrist']

CLASS_WEIGHTS = [12.0, 12.0, 12.0, 12.0, 12.0, 1.0, 8.0, 36.0, 8.0, 8.0, 8.0, 8.0]


def most_common(lst):
    return CLASSES.index(max(set(lst), key=lst.count))


def fold(n, data):
    assert 1 <= n <= 10
    train = data.loc[[i for i in range(1, 11) if i != n], :]
    test = data.loc[[n], :]
    return train, test


def Xy_TrainTest(file, fold_n):

    X_train = np.array([])
    y_train = np.array([])
    X_test = np.array([])
    y_test = np.array([])

    # data_session = pd.read_csv(inputdir + file)
    print(f'loading {file}...')
    data_session = pd.read_csv(file)
    data_session = pd.DataFrame(data_session)
    # print(data_session.head(3)) 
    print(f'chooing data with position {POSITIONS}...')
    data_session = data_session[data_session['Sensor_Position'].isin(POSITIONS)].reset_index(drop=True)

    print(f"splitting dataset subject to fold-{fold_n}...")
    train = data_session[data_session['Object'].isin([i for i in range(1, 11) if i != fold_n])].reset_index(drop=True)
    test = data_session[data_session['Object'] == fold_n].reset_index(drop=True)
    # print(train.head(3))
    # print(test.head(3))

    # data_session = data_session.set_index("Object")
    # train, test = fold(fold_n, data_session)
    # train = train.reset_index()
    # test = test.reset_index()

    train = train.drop(["Object", "Day", "Sensor_Position"], axis=1)
    test = test.drop(["Object","Day", "Sensor_Position"], axis=1)
    # print(train.head(3))
    # print(test.head(3))

    # print(train.shape)
    # print(test.shape)
    # print(train.columns.to_list())
    # print(test.columns.to_list())
    # print(train.head(5))
    # print(test.head(5))

    X_train = train[SENSING_DIMENSIONS].to_numpy()
    X_test = test[SENSING_DIMENSIONS].to_numpy()
    Y_train = train['Workout'].to_numpy()
    Y_test = test['Workout'].to_numpy()

    # for i in range(0, train.shape[0], SLIDING_WINDOW_STEP):
    #     # X_train = np.append(X_train, train.iloc[i:i + SLIDING_WINDOW_LENGTH, 1:8].to_numpy().ravel())
    #     y_train = np.append(y_train, most_common(list(train.iloc[i:(i + SLIDING_WINDOW_LENGTH), 0].to_numpy().ravel())))
    #
    # for i in range(0, test.shape[0], SLIDING_WINDOW_STEP):
    #     # X_test = np.append(X_test, test.iloc[i:i + SLIDING_WINDOW_LENGTH, 1:8].to_numpy().ravel())
    #     y_test = np.append(y_test, most_common(list(test.iloc[i:(i + SLIDING_WINDOW_LENGTH), 0].to_numpy().ravel())))

    # print("X_train shape: ", X_train.shape)
    # print("y_train shape: ", y_train.shape)
    # print("X_test shape: ", X_test.shape)
    # print("y_test shape: ", y_test.shape)

    #pd.DataFrame(y_train).to_csv("y_train.csv")
    #pd.DataFrame(y_test).to_csv("y_test.csv")

    # X_train = X_train.reshape(-1, 80, 7)
    X_train = sliding_window_view(X_train, (SLIDING_WINDOW_LENGTH, X_train.shape[1]))[::SLIDING_WINDOW_STEP, 0]
    Y_train = sliding_window_view(Y_train, (SLIDING_WINDOW_LENGTH))[::SLIDING_WINDOW_STEP]
    for i in range(Y_train.shape[0]):
        y_train = np.append(y_train, most_common(list(Y_train[i])))
    # print(y_train.shape)
    # print(Y_train[40])
    # print(y_train[40])

    #np.save(str(fold_n) + "_X_Train.npy", X_train)
    # print("X_train shape: ", X_train.shape)
    #pd.DataFrame(X_train).to_csv(outputdir + "X_train.csv")

    y_train = y_train.reshape(-1)
    #np.save(str(fold_n) + "_y_Train.npy", y_train)
    # print("y_train shape: ", y_train.shape)
    #pd.DataFrame(y_train).to_csv(outputdir + "y_train.csv")

    # X_test = X_test.reshape(-1, 80, 7)
    X_test = sliding_window_view(X_test, (SLIDING_WINDOW_LENGTH, X_test.shape[1]))[::SLIDING_WINDOW_STEP, 0]
    Y_test = sliding_window_view(Y_test, (SLIDING_WINDOW_LENGTH))[::SLIDING_WINDOW_STEP]
    for i in range(Y_test.shape[0]):
        y_test = np.append(y_test, most_common(list(Y_test[i])))
    #np.save(str(fold_n) + "_X_Test.npy", X_test)
    # print("X_test shape: ", X_test.shape)
    #pd.DataFrame(X_test).to_csv(outputdir + "X_test.csv")

    y_test = y_test.reshape(-1)
    #np.save(str(fold_n) + "_y_Test.npy", y_test)
    # print("y_test shape: ", y_test.shape)
    #pd.DataFrame(y_test).to_csv(outputdir + "y_test.csv")
   
    # --> (-1, 7, 80)
    print('transposing data to channel-first...') 
    X_train = X_train.transpose(0, 2, 1)
    X_test = X_test.transpose(0, 2, 1)

    print('transforming data from numpy.array into torch.tensor...') 
    X_train = torch.from_numpy(X_train.copy()).float()
    y_train = torch.from_numpy(y_train.copy()).long()
    X_test = torch.from_numpy(X_test.copy()).float()
    y_test = torch.from_numpy(y_test.copy()).long()

    print('loading complete.')

    return X_train, y_train, X_test, y_test


if __name__ == '__main__':
    x_train, y_train, x_test, y_test = Xy_TrainTest('~/onlineTiny2023datasets/Gym_Data.csv', 1)
    print(x_train.shape, y_train.shape, x_test.shape, y_test.shape)


