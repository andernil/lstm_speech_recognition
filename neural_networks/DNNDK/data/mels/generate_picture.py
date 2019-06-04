import struct
import sys
import os
import numpy as np
from PIL import Image

size_h = 118
size_w = 80

data_float = []

def main():
    current_dir = os.getcwd()
    #print(os.listdir(current_dir))
    for target_file in os.listdir(current_dir):
        if target_file.endswith(".dat"):
            print(target_file)
            data = open(target_file,"r", newline='\n').read()
            split_data = data.splitlines()
            data_float = [float(line) for line in split_data]
            if(len(data_float) > 9440):
                data_float.pop(0)
            data_array = np.asarray(data_float)
            data_array = np.reshape(data_array, (118,80))
            #size = struct.pack("<I", len(data_array))
            #    img = Image.frombytes("RGB", (size_h, size_w), data, "raw", "RGB", 0, 1)
            img = Image.fromarray(data_array)
            rgb = img.convert("RGB")
            output_file = (os.path.splitext(os.path.basename(target_file))[0]) + ".png"
            rgb.save(output_file)


if __name__=="__main__":
    main()
