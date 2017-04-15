
from numpy import array
from sklearn import svm
clf = svm.SVC(gamma=0.0000001, C = 10)

clf.fit(array(lessons), array(results))

mat = []
input()
for i in range(30):
    line = input().strip()
    if(len(line) == 0):
        continue
    mat_line = []
    for pixel in line.split(" "):
        mat_line.append([int(color) for color in pixel.split(",")])
    mat.append(mat_line)

letters = []
input_array = array(mat)
gray_array = input_array[:, :, 1]
for j in range(5):
    start_x = 5 + j * 9
    end_x = 13 + j * 9
    letters.append(gray_array[11:21, start_x:end_x].reshape(80).tolist())

print("".join(clf.predict(array(letters)).tolist()))
