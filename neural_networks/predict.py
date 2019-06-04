import sys
import os
import keras
from tensorflow.keras.models import load_model
import numpy as np
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import time

batch_size = 1
labels = ['yes', 'no', 'up', 'down', 'left', 'right', 'on', 'off', 'stop', 'go', 'silence', 'unknown']
num_labels = len(labels)

input_data_folder = "input_data/"

def predict(model = "speech_CNN.h5", input_shape = [1,118,80,1], input_data = "input_data\go\MFCC\00b01445_nohash_0.dat"):
    # Load input data
    X = np.empty(input_shape)
    X = np.reshape(np.loadtxt(input_data)[1:], input_shape)

    # Predict
    prediction_start = time.perf_counter()
    y = model.predict(X)
    prediction_stop = time.perf_counter()
    top_result = np.argmax(y)
    result_value = y[0][top_result]
    diff = prediction_stop - prediction_start
    return(top_result, result_value, diff)

def plot_precision_recall(y_ver, y_pred, y_pred_values, threshold_start, threshold_stop, num_steps):
    pred_step = (threshold_stop - threshold_start) / num_steps;
    total_preds = len(y_pred)
    precisions = []
    recalls = []

    for step in range(num_steps + 1):
        i = 0
        true_pred = 0
        false_pred = 0
        for prediction_value in y_pred_values:
            if(prediction_value >= (threshold_stop - pred_step * step)):
                if(y_pred[i] == y_ver[i]):
                    true_pred += 1
                else:
                    false_pred += 1
            i+=1
        print("Threshold: ", threshold_stop - pred_step * step)
        #precisions.append((true_pred, false_pred))
        precision = true_pred / (true_pred + false_pred)
        recall = (true_pred + false_pred) / total_preds
        precisions.append(precision)
        recalls.append(recall)
        print(true_pred, false_pred, total_preds)
    print(precisions)
    print(recalls)

    fig, ax = plt.subplots()
    ax.plot(recalls, precisions, marker='o')

    plt.title("Recall and precision curve for overall prediction accuracy", fontsize=20)
    plt.xlabel("Recall", fontsize=18)
    plt.ylabel("Precision", fontsize=18)
    #plt.grid()

    plt.show()

def plot_confusion_matrix(y_ver, y_pred, labels, title=None, cmap=plt.cm.Blues):
    if not title:
        title = "Confusion matrix"
    cm = confusion_matrix(y_ver, y_pred)
    print("Confusion matrix")
    print(cm)
    fig, ax = plt.subplots()
    im = ax.imshow(cm, interpolation='nearest', cmap = cmap)
    ax.figure.colorbar(im, ax=ax)
    # We want to show all ticks...
    ax.set(xticks=np.arange(cm.shape[1]),
           yticks=np.arange(cm.shape[0]),
           # ... and label them with the respective list entries
           xticklabels=labels, yticklabels=labels,
           title=title,
           ylabel='True label',
           xlabel='Predicted label')

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.
    fmt = 'd'
    thresh = cm.max() / 2.
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, format(cm[i, j], fmt),
                    ha="center", va="center",
                    color="white" if cm[i, j] > thresh else "black")
    fig.tight_layout()
    return ax


def main():
    #print("Getting input arguments")
    try:
        input_model = "models/speech_CNN.h5"#sys.argv[1] #"speech_CNN.h5"
        verification_register_file = "models/verification_data-201955023_CNN.txt"#sys.argv[2] #
        num_iterations = 120 #sys.argv[3] #120
    except:
        print("Script requires three input arguments: Model, file register (.txt) and num_iterations")
        return(0)

    #print("Loading model")
    model = load_model(input_model)
    # Get input shape
    for layer in model.layers:
        input_shape = layer.input_shape
        break
    input_shape = (batch_size, input_shape[1], input_shape[2], input_shape[3])

    # Load verification sample register and split into sample name and label
    verification_file_register = open(verification_register_file, "r")
    
    # Calculate the number of tests per category
    num_files_per_category = int(num_iterations / num_labels)

    y_ver = []
    y_pred = []
    y_pred_val = []
    pred_time = []

    loop_count = 0
    prev_label = 1
    for line in verification_file_register:
        line_arguments = line.split(',')
        input_data_file = input_data_folder + line_arguments[0]
        input_label = int(str(line_arguments[1]).strip("\n"), 10)
        if(input_label == prev_label):
            loop_count += 1
        else:
            loop_count = 0
        if(loop_count < num_files_per_category):
            # Predict returns three values: the index of the word with the highest value,
            # the value of the most likely word and the time spent estimating the value
            prediction, prediction_value, prediction_time = predict(model, input_shape, input_data_file)
            y_ver.append(input_label)
            y_pred.append(prediction)
            y_pred_val.append(prediction_value)
            pred_time.append(prediction_time)
            if(prediction_value < 0.90):
                print("Low pred value:", prediction_value)
            
        prev_label = input_label
    # Save prediction times to file
    input_split = input_model.split(".")
    prediction_time_filename = input_split[0] + "_prediction_times.txt" 
    pred_file = open(prediction_time_filename, "w")
    for time in pred_time:
        pred_file.write(str(time) + "\n")
    # Calculate average, median, min and max prediction times
    pred_time.sort()
    min = pred_time[0]
    max = pred_time[len(pred_time) - 1]
    median = pred_time[(len(pred_time) - 1) // 2]
    avg = sum(pred_time)/len(pred_time)
    print("Prediction times:")
    print("Avg:", avg, "Min:", min, "Max:", max, "Median:", median)
    # Finished predicting, can now display confusion matrix
    #plot_confusion_matrix(y_ver, y_pred, labels)
    #plt.show()
    plot_precision_recall(y_ver, y_pred, y_pred_val, 0, 1, 10)

    # Close text files
    verification_file_register.close()
    pred_file.close()
if __name__ == "__main__":
    main()
