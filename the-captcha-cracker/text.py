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

def cut_data():
    letters = []
    for i in range(2, 25):
        if i == 21:
            continue
        with open("sampleCaptchas/input/input%02d.txt" % i, "r") as inf:
        # with open("sample.txt", "r") as inf:
            inf.readline()
            input_text = inf.read()
            input_data = parse(input_text)
            input_array = array(input_data)
            gray_array = input_array[:, :, 1]
            for j in range(5):
                start_x = 5 + j * 9
                end_x = 13 + j * 9
                letters.append("[" + ",".join([str(i) for i in gray_array[11:21, start_x:end_x].reshape(80).tolist()]) + "]")
    print("lessons = [", ",".join(letters), "]")

def cut_answers():
    letters = []
    for i in range(2, 25):
        if i == 21:
            continue
        with open("sampleCaptchas/output/output%02d.txt" % i, "r") as inf:
        # with open("sample.txt", "r") as inf:
            line = inf.readline().strip()
            letters += list(line)
    print("results = [", ",".join(['"' + l + '"' for l in letters]), "]")
    

cut_data()
cut_answers()

