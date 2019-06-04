import string
import os

import numpy as np

import matplotlib.pyplot as plt
import plotly.offline as py
import plotly.graph_objs as go

# Include the network model functions
import NetworkModels

import keras
from keras import Input, layers
from keras import backend as K
from keras.utils import to_categorical
from keras.callbacks import EarlyStopping, ModelCheckpoint, LearningRateScheduler
from datetime import datetime

from data_classes import DataGenerator

import random
import copy

import math

num_frames_per_sample = 118
num_MFCC_per_sample = 80
NN_batch_size = 10
NN_num_epochs = 40
NN_num_training_samples = 0
NN_num_validation_samples = 0

train_val_split_ratio = 0.6
val_ver_split_ratio = 0.75

train_audio_path = 'input_data'
subfolder = '/Mels/'

# Split the data set into three bins: Training (60%), validation (30%) and testing (10%)
#
# Inputs:
# - data: all data .dat-files read from the input data subfolders
# - all_labels: labels for all the .dat files
# - label_values: enumerated labels
# - label_counts: the number of unique labels
# - ratio: the split-ratio between training and validation/testing
# - test_ratio: split-ratio between validation and testing
# Outputs:
# - output_data: dictionary of data labels divided into three categories
# - output_labels: corresponding labels for each sample

def split_dataset(data, all_labels, label_values, label_counts, ratio=0.6, verification_ratio=0.75) :
    X_train = []
    X_val = []
    X_ver = []
    #y_train = []
    #y_test = []
    element_count = 0
    for label_info in label_counts:
        num_elements = int(label_info[1])
        split_point = int(num_elements * ratio) + element_count
        test_val_split_point = int(split_point + (element_count + num_elements - split_point) * verification_ratio)

        X_train.extend(data[element_count:split_point])
        X_val.extend(data[split_point: test_val_split_point])
        X_ver.extend(data[test_val_split_point: element_count + num_elements])
        element_count = num_elements + element_count

    output_data = {
        "train": X_train,
        "validation": X_val,
        "verification": X_ver
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

    all_Mels = []
    unknown_Mels = []
    label_all = []
    label_value = {}
    label_counts = []
    target_list = ['yes', 'no', 'up', 'down', 'left', 'right', 'on', 'off', 'stop', 'go', 'silence', 'unknown']
    dirs_filtered = [dir for dir in dirs and target_list]
    print(dirs_filtered)
    # Look through folders and add file IDs 
    i = 0
    for direct in dirs_filtered:
        label_count = 0
        Melss = [file for file in os.listdir(os.path.join(train_audio_path, direct + subfolder)) if file.endswith('.dat')]
        label_value[direct] = i
        i = i + 1
        print(str(i)+":" + str(direct) + " ", end="")
        for Mel in Mels:
            if(label_count < 4000):
                Mel_values = os.path.join(direct + subfolder + Mel)
                if(direct in unknown_list):
                    unknown_Mels.append(Mel_values)
                else:
                    label_all.append(direct)
                    all_Mels.append([Mel_values, direct])
                    label_count = label_count + 1
        if(direct in target_list):
            label_counts.append([direct, label_count])
    
    Mels_all = np.reshape(np.delete(all_Mels,1,1), len(all_Mels))
    label_all = [i for i in np.delete(all_Mels,0,1).tolist()]
    Mels_vals = np.array([x for x in Mels_all])
    label_vals = [x for x in label_all]

    # Split dataset into training and validation sets
    partition, labels = split_dataset(MFCC_vals, label_vals, label_value, label_counts, train_val_split_ratio, val_ver_split_ratio)

    # Parameters
    params = {  'dim': (118,80),
                'batch_size': 64,
                'num_classes': len(target_list),
                'num_channels': 1,
                'shuffle': True}

    # Generators
    training_generator = DataGenerator(partition['train'], labels, **params)
    validation_generator = DataGenerator(partition['validation'], labels, **params)

    # Get timestamp for use in model names and verification data register
    date = datetime.now()
    postfix = str(date.year) + str(date.month) + str(date.day) + str(date.hour) + str(date.minute)

    # Save verification files. Format: Filename,label
    ver_text_filename = str("verification_data-" + postfix + ".txt")
    ver_text_file = open(ver_text_filename, "w")
    for element in partition['verification']:
        output_string = element
        label = labels[element]
        output_string = output_string + "," + str(label) + "\n"
        ver_text_file.write(output_string)
    ver_text_file.close()

    model = NetworkModels.AttRNNSpeechModel(nCategories = len(target_list), data_in_dims = (118,80,1))

    model.compile(optimizer='adam', 
                  loss=['sparse_categorical_crossentropy'], 
                  metrics=['sparse_categorical_accuracy']
                  )
    model.summary()
    model_filename = "speech_attLSTM"
    model_filename = model_filename + "-" + postfix + ".h5"

    lrate = LearningRateScheduler(step_decay)
    earlystopper = EarlyStopping(monitor='val_sparse_categorical_accuracy', patience=5, verbose=1)
    checkpointer = ModelCheckpoint(model_filename, monitor='val_sparse_categorical_accuracy', verbose=1, save_best_only=True)
    results = model.fit_generator(generator=training_generator,
                         validation_data=validation_generator,
                         epochs=40,
                         verbose=1,
                         callbacks=[earlystopper, checkpointer, lrate]
    )
    # Plot the accuracy history
    plt.plot(results.history['sparse_categorical_accuracy'])
    plt.plot(results.history['val_sparse_categorical_accuracy'])
    plt.title('Categorical accuracy')
    plt.ylabel('accuracy')  
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper left')
    plt.show()

    # Plot the loss history
    plt.plot(results.history['loss'])
    plt.plot(results.history['val_loss'])
    plt.title('Model loss')
    plt.ylabel('loss')  
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper left')
    plt.show()

# Run the program
if __name__ == "__main__":
    main()
