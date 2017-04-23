import sys
from text import to_text
from os.path import exists
from skimage import io
from numpy import array

def G2RGB(data):
    output = []
    for line in data:
        output.append([[color, color, color] for color in line])
    return array(output)

[from_file, to_file] = sys.argv[1:3]

if exists(to_file):
    raise Exception("%s Exists!" % to_file)

print("[I] Parsing %s" % from_file)

source_data = io.imread(from_file)

if(len(source_data.shape) < 2):
    raise Exception("File is smaller then rectangle!")
if(len(source_data.shape) > 3):
    raise Exception("File is bigger then cude!")
if(len(source_data.shape) == 2):
    print("[I] Converting Grayscale to RGB")
    source_data = G2RGB(source_data)
else:
    if(source_data.shape[2] > 4):
        raise Exception("Third dimention is bigger then RGBA")
    elif(source_data.shape[2] == 4):
        print("[W] Dismissing last channel (alpha)")
        source_data = source_data[:,:,0:3]
    elif(source_data.shape[2] == 1):
        print("[I] Converting Grayscale to RGB")
        source_data = G2RGB(source_data.reshape(list(source_data.shape)[0:2]))
    elif(source_data.shape[2] != 3):
        raise Error("Wrong third dimention %d" % source_data.shape[2])
    
print("[I] Writing %s" % to_file)
with open(to_file, "w") as output_file:
    output_file.write(to_text(source_data))

print("[I] Convertion done")
