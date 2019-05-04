import sys
import keras
from tensorflow.keras.models import load_model
import numpy as np

batch_size = 1
labels = ['yes', 'no', 'up', 'down', 'left', 'right', 'on', 'off', 'stop', 'go', 'silence', 'unknown']
def main():
    #print("Getting input arguments")
    input_model = sys.argv[1]
    input_data_file = sys.argv[2]

    #print("Loading model")
    model = load_model(input_model)
    # Get input shape
    for layer in model.layers:
        input_shape = layer.input_shape
        break
    input_shape = (batch_size, input_shape[1], input_shape[2], input_shape[3])
    #print("Getting input data")
    X = np.empty(input_shape)
    X = np.reshape(np.loadtxt(input_data_file)[1:], input_shape)

    # Predict
    print("Predicting")
    y = model.predict(X)
    #for prediction in y:
    top_result = np.argmax(y)
    print("Predicted word: ", labels[top_result])

    


if __name__ == "__main__":
    main()