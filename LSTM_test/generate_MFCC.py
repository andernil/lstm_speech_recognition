import os
import sys
import subprocess

current_dir = os.getcwd()
print(current_dir)
input_directory = sys.argv[1]
print(input_directory)
target_dir = current_dir + '/' + input_directory + '/'
print(target_dir)
count = 0
files = [f for f in os.listdir(target_dir) if os.path.isfile(os.path.join(target_dir, f))]
for f in files:
    if(f.endswith(".wav")):
        subprocess.run(["./HLS_FFT", input_directory, f])

