#!/bin/sh
# Script for converting Keras-models to Caffe using MMdnn

# Get input model name

input_model_name="$1"
echo "$input_model_name"
original_filename="${input_model_name%.*}"
IR_filename="${original_filename}_IR"
echo "$IR_filename"

# Convert from Keras to intermediate representation (IR)
echo "Converting to IR"
echo "mmtoir -f keras -d $IR_filename -w $input_model_name"
mmtoir -f keras -d $IR_filename -w $input_model_name
# This generates an IR_filename.json and IR_filename.npy for architecture and weights, respectively

Caffe_filename="${original_filename}_caffe"
echo "Converting to Caffe-code"
# Convert from IR to Caffe-code
echo "mmtocode -f caffe -n ${IR_filename}.pb -w ${IR_filename}.npy -o ${Caffe_filename}.py -ow ${Caffe_filename}.npy"
mmtocode -f caffe -n ${IR_filename}.pb -w ${IR_filename}.npy -o ${Caffe_filename}.py -ow ${Caffe_filename}.npy

echo "Converting to Caffemodel"
# Convert from Caffe-code to Caffe model
echo "mmtomodel -f caffe -in "${Caffe_filename}.py" -iw "${Caffe_filename}.npy" -o $original_filename"
mmtomodel -f caffe -in "${Caffe_filename}.py" -iw "${Caffe_filename}.npy" -o $original_filename

