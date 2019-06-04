from keras.models import Model, load_model

from keras.layers import Input, Activation, Concatenate, Permute, Reshape, Flatten, Lambda, Dot, Softmax
from keras.layers import Add, Dropout, BatchNormalization, Conv2D, Reshape, MaxPooling2D, Dense, CuDNNLSTM, Bidirectional, LSTM
from keras import backend as K
from keras.utils import to_categorical
from keras.callbacks import EarlyStopping, ModelCheckpoint, LearningRateScheduler
from keras import backend as K
from keras import optimizers

def ConvSpeechModel(nCategories, data_in_dims):
    """
    Base fully convolutional model for speech recognition
    """

    inputs = Input(data_in_dims)

    x = inputs
    #note that Melspectrogram puts the sequence in shape (batch_size, melDim, timeSteps, 1)
    #we would rather have it the other way around for LSTMs

    c1 = Conv2D(20, (3,3) , activation='relu', padding='same') (x)
    c1 = BatchNormalization() (c1)
    p1 = MaxPooling2D((2, 2)) (c1)
    p1 = Dropout(0.03) (p1)

    c2 = Conv2D(40, (3,3) , activation='relu', padding='same') (p1)
    c2 = BatchNormalization() (c2)
    p2 = MaxPooling2D((1, 2)) (c2)
    p2 = Dropout(0.01) (p2)

    c3 = Conv2D(40, (3,3) , activation='relu', padding='same') (p2)
    c3 = BatchNormalization() (c3)
    p3 = MaxPooling2D((1, 2)) (c3)

    p3 = Flatten()(p3)
    p3 = Dense(64, activation = 'relu')(p3)
    p3 = Dense(32, activation = 'relu')(p3)

    output = Dense(nCategories, activation = 'softmax')(p3)

    model = Model(inputs=[inputs], outputs=[output], name='ConvSpeechModel')
    
    return model



def RNNSpeechModel(nCategories, data_in_dims):
    #simple LSTM

    inputs = Input(data_in_dims)

    x = inputs

    x = Conv2D(10, (5,1) , activation='relu', padding='same') (x)
    x = BatchNormalization() (x)
    x = Conv2D(1, (5,1) , activation='relu', padding='same') (x)
    x = BatchNormalization() (x)

    x = Reshape((118, 80)) (x)

    x = (LSTM(64, return_sequences=True, activation = 'tanh', recurrent_activation = 'sigmoid')) (x)
    x = (LSTM(64, activation = 'tanh', recurrent_activation = 'sigmoid')) (x)

    x = Dense(64, activation = 'relu')(x)
    x = Dense(32, activation = 'relu')(x)

    output = Dense(nCategories, activation = 'softmax')(x)

    model = Model(inputs=[inputs], outputs=[output])
    
    return model


def AttRNNSpeechModel(nCategories, data_in_dims):
    #simple LSTM

    inputs = Input(data_in_dims)

    x = inputs
    #note that Melspectrogram puts the sequence in shape (batch_size, melDim, timeSteps, 1)
    #we would rather have it the other way around for LSTMs

    x = Conv2D(10, (5,1) , activation='relu', padding='same') (x)
    x = BatchNormalization() (x)
    x = Conv2D(1, (5,1) , activation='relu', padding='same') (x)
    x = BatchNormalization() (x)

    x = Reshape((118, 80)) (x)

    x = (LSTM(64, return_sequences=True, activation = 'tanh', recurrent_activation = 'sigmoid')) (x)
    x = (LSTM(64, return_sequences=True, activation = 'tanh', recurrent_activation = 'sigmoid')) (x)

    xFirst = Lambda(lambda q: q[:,64]) (x) #[b_s, vec_dim]
    query = Dense(128) (xFirst)

    #dot product attention
    attScores = Dot(axes=[1,2])([query, x]) 
    attScores = Softmax(name='attSoftmax')(attScores) #[b_s, seq_len]

    #rescale sequence
    attVector = Dot(axes=[1,1])([attScores, x]) #[b_s, vec_dim]

    x = Dense(64, activation = 'relu')(attVector)
    x = Dense(32)(x)

    output = Dense(nCategories, activation = 'softmax', name='output')(x)

    model = Model(inputs=[inputs], outputs=[output])
    
    return model
