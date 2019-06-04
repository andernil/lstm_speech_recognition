import sys 
import os


os.environ["PATH"] += os.pathsep + 'C:/Program Files (x86)/Graphviz2.38/bin/'

from keras.utils import plot_model
from keras.models import load_model

input_model = sys.argv[1]
model = load_model(input_model)

output_filename = os.path.splitext(input_model)[0] + ".png"
plot_model(model, to_file = output_filename)
print("Graph saved as", output_filename)