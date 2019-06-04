import sys

import keras2caffe

from keras.models import load_model

model = load_model(sys.argv[1])

keras2caffe.convert(model, 'deploy.prototxt', 'weights.caffemodel')
