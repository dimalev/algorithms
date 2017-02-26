import sys
import numpy as np

def daynight(rgbimagedata, threshold):
    imagedata = 0.333 * rgbimagedata[...,0] + 0.333 * rgbimagedata[...,1] + 0.333 * rgbimagedata[...,2]
    mid = np.mean(imagedata)
    # print(mid)
    return mid > threshold

data = sys.stdin.read()
rgbimage = []
for line in data.split("\n"):
    if len(line) != 0:
        rgbline = []
        for pixel in line.split(" "):
            rgbline.append([channel for channel in pixel.split(",")])
        rgbimage.append(rgbline)

if daynight(np.array(rgbimage, dtype = np.float64), 80):
    print("day")
else:
    print("night")
