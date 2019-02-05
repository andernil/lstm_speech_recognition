from numpy import array
from pickle import dump
from keras.utils import to_categorical
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Dropout

#load doc into memory
def load_doc(filename):
    #open as read only
    file = open(filename, 'r')
    # read text
    text = file.read()
    # close file
    file.close()
    return(text)

#load
#in_filename = 'input_data/shakespeare.txt'
in_filename = 'input_data/rhyme.txt'
raw_text = load_doc(in_filename)
#clean text
lines = raw_text.split('\n')
raw_text = ' '.join(lines)

#create sequences
length = 2
sequences = list()
for i in range(length, len(raw_text)):
    #select sequence of tokens
    seq = raw_text[i-length:i+1]
    #store
    sequences.append(seq)
print('Total Sequences: %d' % len(sequences))

raw_text = '\n'.join(sequences)
lines = raw_text.split('\n')

#integer encoded characters
chars = sorted(list(set(raw_text)))
mapping = dict((c, i) for i, c in enumerate(chars))
sequences = list()
for line in lines:
    #integer encode line
    encoded_seq = [mapping[char] for char in line]
    #store
    sequences.append(encoded_seq)

#vocabulary size
vocab_size = len(mapping)
print('Vocabulary Size: %d' % vocab_size)

#separate into input and output
sequences = array(sequences)
X, Y = sequences[:,:-1], sequences[:,-1]
sequences = [to_categorical(x, num_classes=vocab_size) for x in X]
X = array(sequences)
Y = to_categorical(Y, num_classes=vocab_size)

#define model
model = Sequential()
model.add(LSTM(75, input_shape=(X.shape[1], X.shape[2]), return_sequences=True))
model.add(LSTM(75))
#model.add(Dropout(0.5))
model.add(Dense(vocab_size, activation='softmax'))
print(model.summary())

#compile
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

#fit model
model.fit(X, Y, epochs=200, verbose=2)

#save model
model.save('model.h5')

#save the mapping
dump(mapping, open('mapping.pkl', 'wb'))
