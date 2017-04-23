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
    return array(mat)

def to_text(data):
    # size_txt = " ".join(map(str, [data.shape[0], data.shape[1]]))
    body_txt = "\n".join([" ".join([",".join(map(str, colors)) for colors in line]) for line in data])
    return body_txt + "\n"

def test_parse():
    output = parse("1,2,3 4,5,6\n7,8,9 10,11,12")
    print(output[1][1][1], " == 11")

def test_text():
    output = to_text(array([[[1,2,3], [4,5,6], [1,2,3]], [[3,2,1], [7,8,9], [10, 11, 12]]]))
    print(output)
    print(output == "1,2,3 4,5,6 1,2,3\n3,2,1 7,8,9 10,11,12\n")

# test_parse()
# test_text()
