import tensorflow as tf

__weights_dict = dict()

is_train = False

def load_weights(weight_file):
    import numpy as np

    if weight_file == None:
        return

    try:
        weights_dict = np.load(weight_file).item()
    except:
        weights_dict = np.load(weight_file, encoding='bytes').item()

    return weights_dict


def KitModel(weight_file = None):
    global __weights_dict
    __weights_dict = load_weights(weight_file)

    input_1         = tf.placeholder(tf.float32,  shape = (None, 118, 80, 1), name = 'input_1')
    conv2d_1        = convolution(input_1, group=1, strides=[1, 1], padding='SAME', name='conv2d_1')
    conv2d_1_activation = tf.nn.relu(conv2d_1, name = 'conv2d_1_activation')
    batch_normalization_1 = batch_normalization(conv2d_1_activation, variance_epsilon=0.0010000000474974513, name='batch_normalization_1')
    max_pooling2d_1 = tf.nn.max_pool(batch_normalization_1, [1, 2, 2, 1], [1, 2, 2, 1], padding='VALID', name='max_pooling2d_1')
    conv2d_2        = convolution(max_pooling2d_1, group=1, strides=[1, 1], padding='SAME', name='conv2d_2')
    conv2d_2_activation = tf.nn.relu(conv2d_2, name = 'conv2d_2_activation')
    batch_normalization_2 = batch_normalization(conv2d_2_activation, variance_epsilon=0.0010000000474974513, name='batch_normalization_2')
    max_pooling2d_2 = tf.nn.max_pool(batch_normalization_2, [1, 3, 3, 1], [1, 3, 3, 1], padding='VALID', name='max_pooling2d_2')
    conv2d_3        = convolution(max_pooling2d_2, group=1, strides=[1, 1], padding='SAME', name='conv2d_3')
    conv2d_3_activation = tf.nn.relu(conv2d_3, name = 'conv2d_3_activation')
    batch_normalization_3 = batch_normalization(conv2d_3_activation, variance_epsilon=0.0010000000474974513, name='batch_normalization_3')
    max_pooling2d_3 = tf.nn.max_pool(batch_normalization_3, [1, 3, 3, 1], [1, 3, 3, 1], padding='VALID', name='max_pooling2d_3')
    flatten_1       = tf.contrib.layers.flatten(max_pooling2d_3)
    dense_1         = tf.layers.dense(flatten_1, 64, kernel_initializer = tf.constant_initializer(__weights_dict['dense_1']['weights']), bias_initializer = tf.constant_initializer(__weights_dict['dense_1']['bias']), use_bias = True)
    dense_1_activation = tf.nn.relu(dense_1, name = 'dense_1_activation')
    dense_2         = tf.layers.dense(dense_1_activation, 32, kernel_initializer = tf.constant_initializer(__weights_dict['dense_2']['weights']), bias_initializer = tf.constant_initializer(__weights_dict['dense_2']['bias']), use_bias = True)
    dense_2_activation = tf.nn.relu(dense_2, name = 'dense_2_activation')
    dense_3         = tf.layers.dense(dense_2_activation, 2, kernel_initializer = tf.constant_initializer(__weights_dict['dense_3']['weights']), bias_initializer = tf.constant_initializer(__weights_dict['dense_3']['bias']), use_bias = True)
    dense_3_activation = tf.nn.softmax(dense_3, name = 'dense_3_activation')
    return input_1, dense_3_activation


def convolution(input, name, group, **kwargs):
    w = tf.Variable(__weights_dict[name]['weights'], trainable=is_train, name=name + "_weight")
    if group == 1:
        layer = tf.nn.convolution(input, w, name=name, **kwargs)
    else:
        weight_groups = tf.split(w, num_or_size_splits=group, axis=-1)
        xs = tf.split(input, num_or_size_splits=group, axis=-1)
        convolved = [tf.nn.convolution(x, weight, name=name, **kwargs) for
                    (x, weight) in zip(xs, weight_groups)]
        layer = tf.concat(convolved, axis=-1)

    if 'bias' in __weights_dict[name]:
        b = tf.Variable(__weights_dict[name]['bias'], trainable=is_train, name=name + "_bias")
        layer = layer + b
    return layer

def batch_normalization(input, name, **kwargs):
    mean = tf.Variable(__weights_dict[name]['mean'], name = name + "_mean", trainable = is_train)
    variance = tf.Variable(__weights_dict[name]['var'], name = name + "_var", trainable = is_train)
    offset = tf.Variable(__weights_dict[name]['bias'], name = name + "_bias", trainable = is_train) if 'bias' in __weights_dict[name] else None
    scale = tf.Variable(__weights_dict[name]['scale'], name = name + "_scale", trainable = is_train) if 'scale' in __weights_dict[name] else None
    return tf.nn.batch_normalization(input, mean, variance, offset, scale, name = name, **kwargs)


