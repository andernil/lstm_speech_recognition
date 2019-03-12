import string
import os

import numpy as np

import matplotlib.pyplot as plt
import tensorflow as tf
import plotly.offline as py
import plotly.graph_objs as go

# Include the network model functions
import NetworkModels
#import network_models_original

import tensorflow.keras as keras
from tensorflow.keras import Input, layers
from tensorflow.keras import backend as K
from keras.utils import to_categorical
from keras.callbacks import EarlyStopping, ModelCheckpoint, LearningRateScheduler

import random
import copy

import math

# Original
#num_frames_per_sample = 63
#num_MFCC_per_sample = 7;

# Modified
num_frames_per_sample = 124
num_MFCC_per_sample = 39

split_ratio = 0.6

train_audio_path = 'input_data'
subfolder = '/MFCC/'

def split_dataset(data, all_labels, label_counts, ratio=split_ratio) :
    X_train = []
    X_test = []
    y_train = []
    y_test = []
    element_count = 0
    for label_info in label_counts:
        label = label_info[0]
        num_elements = int(label_info[1])
        split_point = int(num_elements * ratio) + element_count
        X_train.extend(data[element_count:split_point])
        X_test.extend(data[split_point:num_elements])
        y_train.extend(all_labels[element_count:split_point])
        y_test.extend(all_labels[split_point:num_elements])
        element_count = num_elements + element_count
    return(np.array(X_train), np.array(X_test), np.array(y_train), np.array(y_test))

def step_decay(epoch):
    initial_lrate = 0.001
    drop = 0.4
    epochs_drop = 10.0
    lrate = initial_lrate * math.pow(drop, math.floor((1 + epoch)/epochs_drop))

    if(lrate < 4e-5):
        lrate = 4e-5
    print('Changing learning rate to {}'.format(lrate))
    return lrate

def main():
    dirs = [f for f in os.listdir(train_audio_path) if os.path.isdir(os.path.join(train_audio_path, f))]
    dirs.sort()
    print('Number of labels: ' + str(len(dirs[1:])))
    print(dirs)

    all_MFCC = []
    unknown_MFCC = []
    label_all = []
    label_value = {}
    label_counts = []
    target_list = ['bed', 'bird']
    unknown_list = [word for word in dirs if word not in target_list and word != 'background_noise_']
    i = 0
    for direct in dirs[1:5]:
        label_count = 0
        MFCCs = [file for file in os.listdir(os.path.join(train_audio_path, direct + subfolder)) if file.endswith('.dat')]
        label_value[direct] = i
        i = i + 1
        print(str(i)+":" + str(direct) + " ", end="")
        for MFCC in MFCCs:
            if(label_count < 70):
                MFCC_values = np.loadtxt(os.path.join(train_audio_path, direct + subfolder + MFCC), delimiter='\n')
                if(MFCC_values[0] != num_MFCC_per_sample):
                    print("Incorrect number of MFCC values per sample for file " + MFCC + " for word " + direct)
                else:
                    MFCC_values = MFCC_values[1:]
                    if(direct in unknown_list):
                        unknown_MFCC.append(MFCC_values)
                    else:
                        label_all.append(direct)
                        all_MFCC.append([MFCC_values, direct])
                        label_count = label_count + 1
        if(direct in target_list):
            label_counts.append([direct, label_count])
    MFCC_all = np.reshape(np.delete(all_MFCC,1,1),len(all_MFCC))
    label_all = [i for i in np.delete(all_MFCC,0,1).tolist()]
    MFCC_vals = np.array([x for x in MFCC_all])
    label_vals = [x for x in label_all]

    X_train, X_test, y_train, y_test = split_dataset(MFCC_vals, label_vals, label_counts, 0.6)

    X_train = X_train.reshape(X_train.shape[0], num_MFCC_per_sample, num_frames_per_sample, 1)
    X_test = X_test.reshape(X_test.shape[0], num_MFCC_per_sample, num_frames_per_sample, 1)
    y_train_enum =[label_value[label[0]] for label in y_train]
    y_test_enum = [label_value[label[0]] for label in y_test]

    y_train_hot = to_categorical(y_train_enum)
    y_test_hot = to_categorical(y_test_enum)

    #model_orig = network_models_original.ConvSpeechModel(nCategories = 2, samplingrate = 16000, inputLength = 16000)
    #model = NetworkModels.ConvSpeechModel(nCategories = len(target_list), data_in_dims = X_train.shape[1:])
    print(X_train.shape)
    model = NetworkModels.RNNSpeechModel(nCategories = len(target_list), data_in_dims = X_train.shape[1:])
    model.compile(optimizer='adam', loss=['sparse_categorical_crossentropy'], metrics=['sparse_categorical_accuracy'])
    model.summary()

    lrate = LearningRateScheduler(step_decay)
    earlystopper = EarlyStopping(monitor='sparse_categorical_accuracy', patience=10, verbose=1)
    checkpointer = ModelCheckpoint('model-RNN.h5', monitor='sparse_categorical_accuracy', verbose=1, save_best_only=True)
    results = model.fit(x=X_train, y=y_train_enum, batch_size=None, epochs=40, verbose=1, callbacks=[earlystopper, checkpointer, lrate], shuffle=True, steps_per_epoch = 10)

# Run the program
main()
