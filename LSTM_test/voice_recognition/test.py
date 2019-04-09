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

import keras
from keras import Input, layers
from keras import backend as K
from keras.utils import to_categorical
from keras.callbacks import EarlyStopping, ModelCheckpoint, LearningRateScheduler

from data_classes import DataGenerator

import random
import copy

import math

# Original
#num_frames_per_sample = 63
#num_MFCC_per_sample = 7;

# Modified
num_frames_per_sample = 118
num_MFCC_per_sample = 80
NN_batch_size = 10
NN_num_epochs = 40
NN_num_training_samples = 0
NN_num_validation_samples = 0

split_ratio = 0.6

train_audio_path = 'input_data'
subfolder = '/MFCC/'

def split_dataset(data, all_labels, label_values, label_counts, ratio=split_ratio) :
    X_train = []
    X_test = []
    #y_train = []
    #y_test = []
    element_count = 0
    for label_info in label_counts:
        num_elements = int(label_info[1])
        split_point = int(num_elements * ratio) + element_count
        X_train.extend(data[element_count:split_point])
        X_test.extend(data[split_point:element_count + num_elements])
        #y_train.extend(all_labels[element_count:split_point])
        #y_test.extend(all_labels[split_point:num_elements])
        element_count = num_elements + element_count

    output_data = {
        "train": X_train,
        "validation": X_test
    }
    enum_labels = [label_values[label[0]] for label in all_labels]
    output_labels = dict(zip(data,enum_labels))
    return(output_data, output_labels)

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
    target_list = ['bed', 'bird', 'cat', 'dog', 'down', 'eight', 'five', 'four', 'go', 'happy', 'house']
    unknown_list = [word for word in dirs if word not in target_list and word != 'background_noise_']
     
    # Look through folders and add file IDs 
    i = 0
    for direct in dirs[1:15]:
        label_count = 0
        MFCCs = [file for file in os.listdir(os.path.join(train_audio_path, direct + subfolder)) if file.endswith('.dat')]
        label_value[direct] = i
        i = i + 1
        print(str(i)+":" + str(direct) + " ", end="")
        for MFCC in MFCCs:
            if(label_count < 100):
                #MFCC_values is the name of the file
                MFCC_values = os.path.join(direct + subfolder + MFCC)
                if(direct in unknown_list):
                    unknown_MFCC.append(MFCC_values)
                else:
                    label_all.append(direct)
                    all_MFCC.append([MFCC_values, direct])
                    label_count = label_count + 1
        if(direct in target_list):
            label_counts.append([direct, label_count])
    
    MFCC_all = np.reshape(np.delete(all_MFCC,1,1), len(all_MFCC))
    label_all = [i for i in np.delete(all_MFCC,0,1).tolist()]
    MFCC_vals = np.array([x for x in MFCC_all])
    label_vals = [x for x in label_all]

    # Split dataset into training and validation sets
    partition, labels = split_dataset(MFCC_vals, label_vals, label_value, label_counts)

    # Parameters
    params = {  'dim': (118,80),
                'batch_size': 64,
                'num_classes': len(target_list),
                'num_channels': 1,
                'shuffle': True}

    # Generators
    training_generator = DataGenerator(partition['train'], labels, **params)
    validation_generator = DataGenerator(partition['validation'], labels, **params)

    model = NetworkModels.ConvSpeechModel(nCategories = len(target_list), data_in_dims = (118,80,1))
    model.compile(optimizer='adam', loss=['sparse_categorical_crossentropy'], metrics=['sparse_categorical_accuracy'])
    model.summary()

    lrate = LearningRateScheduler(step_decay)
    earlystopper = EarlyStopping(monitor='val_sparse_categorical_accuracy', patience=10, verbose=1)
    checkpointer = ModelCheckpoint('model-CNN.h5', monitor='val_sparse_categorical_accuracy', verbose=1, save_best_only=True)
#   results = model.fit(x=X_train, y=y_train_enum, validation_data = [X_test, y_test_enum], batch_size = None, epochs=NN_num_epochs, steps_per_epoch=(NN_num_training_samples // NN_batch_size) // 2, validation_steps=1, verbose=1, callbacks=[earlystopper, checkpointer, lrate], shuffle=True)
    model.fit_generator(generator=training_generator,
                         validation_data=validation_generator,
                         #use_multiprocessing=True,
                         #workers=4,
                         epochs=40,
                         #verbose=1,
                         callbacks=[earlystopper, checkpointer, lrate])
# Run the program
main()
