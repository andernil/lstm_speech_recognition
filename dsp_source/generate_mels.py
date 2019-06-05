import os
import sys
import subprocess

current_dir = os.getcwd()
print(current_dir)
input_directory = sys.argv[1]
print(input_directory)
target_dir = current_dir + '/' + input_directory + '/'
print(target_dir)
Mel_dir = target_dir + "mels"
try:
	os.mkdir(Mel_dir)
except:
	print("mels-directory already exists")

count = 0
files = [f for f in os.listdir(target_dir) if os.path.isfile(os.path.join(target_dir, f))]
for f in files:
    if(f.endswith(".wav")):
        subprocess.run(["./generate_log_mel_filterbank_energies", input_directory, f])

