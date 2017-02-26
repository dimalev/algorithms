#!/usr/bin/python3

from skimage import io
import sys

if len(sys.argv) < 2:
    print("Usage:")
    print()
    print("./converty.py FILENAME")

def printImageData(rgbimagedata):
    return "\n".join([" ".join([",".join([str(channel) for channel in pixel ]) for pixel in row]) for row in rgbimagedata])

print(printImageData(io.imread(sys.argv[1])))
