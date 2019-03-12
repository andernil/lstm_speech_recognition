import os
import subprocess

current_dir = os.getcwd()
dirs = [dir for dir in os.listdir(current_dir) if os.path.isdir(dir) and dir != "CMakeFiles"]
count = 0
for dir in dirs:
    progress = " [" + str(count) + "/" + str(len(dirs)) + "]"
    print("Generating MFCC values for word: "  + dir + progress)
    subprocess.run(["python3.5", "generate_MFCC.py", dir], stdout=subprocess.DEVNULL)
    count = count + 1

