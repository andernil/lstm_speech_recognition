import os
import subprocess

current_dir = os.getcwd()
target_list = ['yes', 'no', 'up', 'down', 'left', 'right', 'on', 'off', 'stop', 'go', 'marvin']
dirs = [dir for dir in os.listdir(current_dir) if os.path.isdir(dir) and dir in target_list]
count = 1
for dir in dirs:
    progress = " [" + str(count) + "/" + str(len(dirs)) + "]"
    print("Generating log-mel-filterbanks values for word: "  + dir + progress)
    subprocess.run(["python3.5", "generate_mels.py", dir], stdout=subprocess.DEVNULL)
    count = count + 1

