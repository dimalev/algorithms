from numpy import array

def parse(text):
    mat = []
    for line in text.split("\n"):
        if(len(line) == 0):
            continue
        mat_line = []
        for pixel in line.split(" "):
            mat_line.append([int(color) for color in pixel.split(",")])
        mat.append(mat_line)
    return mat

def test_parse():
    output = parse("1,2,3 4,5,6\n7,8,9 10,11,12")
    print(output[1][1][1], " == 11")
