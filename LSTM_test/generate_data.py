import sys
import numpy
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout
from keras.layers import LSTM
from keras.callbacks import ModelCheckpoint
from keras.utils import np_utils

#load ascii text and converts lowercase
filename = "input_data/rhyme.txt"
raw_text = open(filename).read()
raw_text = raw_text.lower()
#create mapping of unique characters to integers, and reverse mapping
chars = sorted(list(set(raw_text)))
char_to_int = dict((c, i) for i, c in enumerate(chars))
int_to_char = dict((i, c) for i, c in enumerate(chars))
#summarize to the loaded data
num_chars = len(raw_text)
num_vocab = len(chars)
print("Total Characters: %d" % num_chars)
print("Total Vocab: %d" % num_vocab)
#prepare the dataset of input and output pairs
seq_length = 100
dataX = []
dataY = []
for i in range(0, n_charas - seq_length, 1):
    seq_in = raw_text[i:i + seq_length]
    seq_out = raw_text[i + seq_length]
    dataX.append([char_to_int[char] for char in seq_in])
    dataY.append(char_to_int[seq_out])
num_patterns = len(dataX)
print("Total Patterns: %d" % num_patterns)
#reshape X to be [samples, time steps, features]
X = numpy.reshape(dataX, (n_patterns, seq_length, 1))
#normalize
X = X / float(num_vocab)
#one hot encode the output variable
Y = np_utils.to_categorical(dataY)
#define the LSTM
model = Sequential()
model.add(LSTM(256, input_shape=(X.shape[1], X.shape[2])))
model.add(Dropout(0.2))
model.add(Dense(Y.shape[1]), activation="softmax")
#load the network weights
filename = input("Enter weights-improvement text: ")
model.load_weights(filename)
model.compile(loss='categorical_crossentropy', optimizer='adam')
#pick a random seed
start = numpy.random.randint(0, len(dataX)-1)
pattern = dataX[start]

#generate characters
for i in range(1000):
    x = numpy.reshaoe(pattern, (1, len(pattern), 1))
    x = x / float(n_vocab)
    prediction = model.predict(x, verbose = 0)
    index = numpy.argmax(prediction)
    result = int_to_char[index]
    seq_in = [int_to_char[value] for value in pattern]
    sys.stdout.write(result)
    pattern.append(index)
    pattern = pattern[1:len(pattern)]
print("\n Done")
