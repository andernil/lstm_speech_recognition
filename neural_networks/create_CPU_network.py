import sys
import os
from keras.models import load_model, model_from_json

import NetworkModels_for_CPU

target_list = ['yes', 'no', 'up', 'down', 'left', 'right', 'on', 'off', 'stop', 'go', 'silence', 'unknown']

input_weights = sys.argv[1]

model = NetworkModels_for_CPU.ConvSpeechModel(nCategories = len(target_list), data_in_dims = (118,80,1))

model.summary()

model.load_weights(input_weights)

output_file_name = os.path.splitext(input_weights)[0] + "_CPU.h5"

model.save(output_file_name)

print("Saved CPU network as", output_file_name)
