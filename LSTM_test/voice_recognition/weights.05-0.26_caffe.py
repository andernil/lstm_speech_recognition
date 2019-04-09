from __future__ import print_function
import numpy as np
import sys, argparse
import caffe
from caffe import layers as L
from caffe import params as P
from caffe import to_proto
from six import text_type as _text_type


__weights_dict = dict()

def load_weights(weight_file):
    if weight_file == None:
        return

    try:
        weights_dict = np.load(weight_file).item()
    except:
        weights_dict = np.load(weight_file, encoding='bytes').item()

    return weights_dict


def KitModel(weight_file = None):
    n = caffe.NetSpec()

    n.input_1         = L.Input(shape=[dict(dim=[1, 1, 118, 80])], ntop=1)
    n.conv2d_1        = L.Convolution(n.input_1, kernel_h=2, kernel_w=2, stride=1, num_output=40, pad_h=1, pad_w=1, group=1,             bias_term=True, ntop=1)
    n.conv2d_1_crop   = L.Crop(n.conv2d_1, L.DummyData(shape=[dict(dim=[1, 40, 118, 80])],                 ntop=1), ntop=1, offset=[1, 1])
    n.conv2d_1_activation = L.ReLU(n.conv2d_1_crop, in_place=True, ntop=1)
    n.batch_normalization_1 = L.BatchNorm(n.conv2d_1_activation, eps=0.0010000000474974513, use_global_stats=True, ntop=1)
    n.batch_normalization_1_scale = L.Scale(n.batch_normalization_1, bias_term=True, in_place=True, ntop=1)
    n.max_pooling2d_1 = L.Pooling(n.batch_normalization_1_scale, pool=0, kernel_size=3, pad_h=0, pad_w=0, stride=3, ntop=1)
    n.max_pooling2d_1_crop = L.Crop(n.max_pooling2d_1, L.DummyData(shape=[dict(dim=[1, 40, 39, 26])],                 ntop=1), ntop=1, offset=[0, 0])
    n.dropout_1       = L.Dropout(n.max_pooling2d_1_crop, dropout_ratio=0.9700000006705523 , in_place=True, ntop=1)
    n.conv2d_2        = L.Convolution(n.dropout_1, kernel_h=3, kernel_w=3, stride=1, num_output=40, pad_h=1, pad_w=1, group=1,             bias_term=True, ntop=1)
    n.conv2d_2_activation = L.ReLU(n.conv2d_2, in_place=True, ntop=1)
    n.batch_normalization_2 = L.BatchNorm(n.conv2d_2_activation, eps=0.0010000000474974513, use_global_stats=True, ntop=1)
    n.batch_normalization_2_scale = L.Scale(n.batch_normalization_2, bias_term=True, in_place=True, ntop=1)
    n.max_pooling2d_2 = L.Pooling(n.batch_normalization_2_scale, pool=0, kernel_size=3, pad_h=0, pad_w=0, stride=3, ntop=1)
    n.max_pooling2d_2_crop = L.Crop(n.max_pooling2d_2, L.DummyData(shape=[dict(dim=[1, 40, 13, 8])],                 ntop=1), ntop=1, offset=[0, 0])
    n.dropout_2       = L.Dropout(n.max_pooling2d_2_crop, dropout_ratio=0.9900000002235174 , in_place=True, ntop=1)
    n.conv2d_3        = L.Convolution(n.dropout_2, kernel_h=3, kernel_w=3, stride=1, num_output=40, pad_h=1, pad_w=1, group=1,             bias_term=True, ntop=1)
    n.conv2d_3_activation = L.ReLU(n.conv2d_3, in_place=True, ntop=1)
    n.batch_normalization_3 = L.BatchNorm(n.conv2d_3_activation, eps=0.0010000000474974513, use_global_stats=True, ntop=1)
    n.batch_normalization_3_scale = L.Scale(n.batch_normalization_3, bias_term=True, in_place=True, ntop=1)
    n.max_pooling2d_3 = L.Pooling(n.batch_normalization_3_scale, pool=0, kernel_size=3, pad_h=0, pad_w=0, stride=3, ntop=1)
    n.max_pooling2d_3_crop = L.Crop(n.max_pooling2d_3, L.DummyData(shape=[dict(dim=[1, 40, 4, 2])],                 ntop=1), ntop=1, offset=[0, 0])
    n.flatten_1       = L.Flatten(n.max_pooling2d_3_crop)
    n.dense_1         = L.InnerProduct(n.flatten_1, num_output=64, bias_term=True, ntop=1)
    n.dense_1_activation = L.ReLU(n.dense_1, in_place=True, ntop=1)
    n.dense_2         = L.InnerProduct(n.dense_1_activation, num_output=32, bias_term=True, ntop=1)
    n.dense_2_activation = L.ReLU(n.dense_2, in_place=True, ntop=1)
    n.dense_3         = L.InnerProduct(n.dense_2_activation, num_output=2, bias_term=True, ntop=1)
    n.dense_3_activation = L.Softmax(n.dense_3, ntop=1)

    return n

def make_net(prototxt):
    n = KitModel()
    with open(prototxt, 'w') as fpb:
        print(n.to_proto(), file=fpb)

def gen_weight(weight_file, model, prototxt):
    global __weights_dict
    __weights_dict = load_weights(weight_file)

    net = caffe.Net(prototxt, caffe.TRAIN)

    for key in __weights_dict:
        if 'weights' in __weights_dict[key]:
            net.params[key][0].data.flat = __weights_dict[key]['weights']
        elif 'mean' in __weights_dict[key]:
            net.params[key][0].data.flat = __weights_dict[key]['mean']
            net.params[key][1].data.flat = __weights_dict[key]['var']
            if 'scale' in __weights_dict[key]:
                net.params[key][2].data.flat = __weights_dict[key]['scale']
        elif 'scale' in __weights_dict[key]:
            net.params[key][0].data.flat = __weights_dict[key]['scale']
        if 'bias' in __weights_dict[key]:
            net.params[key][1].data.flat = __weights_dict[key]['bias']
        if 'gamma' in __weights_dict[key]: # used for prelu, not sure if other layers use this too
            net.params[key][0].data.flat = __weights_dict[key]['gamma']
    net.save(model)
    return net



if __name__=='__main__':
    parser = argparse.ArgumentParser(description='Generate caffe model and prototxt')
    parser.add_argument('--weight_file', '-w', type=_text_type, default='IR weight file')
    parser.add_argument('--prototxt', '-p', type=_text_type, default='caffe_converted.prototxt')
    parser.add_argument('--model', '-m', type=_text_type, default='caffe_converted.caffemodel')
    args = parser.parse_args()
    # For some reason argparser gives us unicode, so we need to conver to str first
    make_net(str(args.prototxt))
    gen_weight(str(args.weight_file), str(args.model), str(args.prototxt))


