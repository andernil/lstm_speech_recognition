from keras.models import load_model

import json
import sys
import os

# Get model from input argument 1
input_model = sys.argv[1]
model = load_model(input_model)

# Print model summary
model.summary()

# Remove .h5 from input model name
input_model_name = os.path.splitext(input_model)[0]

# Save model to .json
with open(input_model_name + "_architecture.json", 'w') as f:
    f.write(model.to_json())
print("Saved architecture to", input_model_name, "_architecture.json")

# Save weights to .h5
model.save_weights(input_model_name + '_weights.h5')
print("Saved weights to", input_model_name, "_weights.h5")