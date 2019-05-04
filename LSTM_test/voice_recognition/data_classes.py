import numpy as np
import keras

class DataGenerator(keras.utils.Sequence):
    def __init__(self, list_IDs, labels, batch_size=32, dim=(118,80,1), num_channels=1,
                num_classes=10, shuffle=True):
                'Initialization'
                self.dim = dim
                self.batch_size = batch_size
                self.labels = labels
                self.list_IDs = list_IDs
                self.num_channels = num_channels
                self.num_classes = num_classes
                self.shuffle = shuffle
                self.on_epoch_end()

    def on_epoch_end(self):
        'Updates indexes after each epoch'
        self.indexes = np.arange(len(self.list_IDs))
        if self.shuffle == True:
            np.random.shuffle(self.indexes)

    def __data_generation(self, list_IDs_temp):
        'Generates data containing batch_size samples' # X : (num_samples, *dim, num_channels)
        # Initialization
        # Channel last
        X = np.empty((self.batch_size, *self.dim, self.num_channels))
        # Channel first
        #X = np.empty((self.batch_size, self.num_channels, *self.dim))
        y = np.empty((self.batch_size), dtype=int)

        #Generate data
        for i, ID in enumerate(list_IDs_temp):
            # Store sample
            # Channel last
            X[i,] = np.reshape(np.loadtxt('input_data/' + ID)[1:], (*self.dim, self.num_channels))
            # Channel first
            #X[i,] = np.reshape(np.loadtxt('input_data/' + ID)[1:], (self.num_channels,*self.dim))
            # Store class
            y[i] = self.labels[ID]

        return X, y

    def __len__(self):
        'Denotes the number of batches per epoch'
        return int(np.floor(len(self.list_IDs) / self.batch_size))

    def __getitem__(self, index):
        'Generate one batch of data'
        # Generate indexes of batch
        indexes = self.indexes[index*self.batch_size:(index+1)*self.batch_size]

        # Find list of IDs
        list_IDs_temp = [self.list_IDs[k] for k in indexes]

        # Generate data
        X, y = self.__data_generation(list_IDs_temp)

        return X, y