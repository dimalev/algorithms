import sys
from math import pi, sqrt

from numpy import array
import matplotlib.pyplot as plt

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

def is_color_similar(one, two, threshold):
    return (one - two) @ (one - two) < threshold

def trim(data, max_count):
    for top in range(data.shape[0]):
        is_done = False
        total = 0
        for scan in range(data.shape[1]):
            if(data[top][scan] > 0):
                total += 1
                if total > max_count:
                    is_done = True
                    break
        if is_done:
            break;

    for bottom in range(data.shape[0] - 1, -1, -1):
        is_done = False
        total = 0
        for scan in range(data.shape[1]):
            if(data[bottom][scan] > 0):
                total += 1
                if total > max_count:
                    is_done = True
                    break
        if is_done:
            break;

    for left in range(data.shape[1]):
        is_done = False
        total = 0
        for scan in range(data.shape[0]):
            if(data[scan][left] > 0):
                total += 1
                if total > max_count:
                    is_done = True
                    break
        if is_done:
            break;

    for right in range(data.shape[1] - 1, -1, -1):
        is_done = False
        total = 0
        for scan in range(data.shape[0]):
            if(data[scan][right] > 0):
                total += 1
                if total > max_count:
                    is_done = True
                    break
        if is_done:
            break;

    return data[top:(bottom + 1), left:(right + 1)]

def count_treshold(image, sr, sc, er, ec, color):
    t = 0
    for r in range(round(sr), round(er)):
        for c in range(round(sc), round(ec)):
            t = max(t, (image[r, c] - color) @ (image[r, c] - color))
    return t

# with open("sample.txt", "r") as image_file:
#     image = text.parse(image_file.read())

image = parse(sys.stdin.read())

print(image[43, 87])

if (image[43,87] - [3, 2, 248]) @ (image[43,87] - [3, 2, 248]) == 0:
    print("circle")
    exit(0)

(rows, cols, depth) = image.shape

corners = [
    image[0][0],
    image[rows - 1][0],
    image[rows - 1][cols - 1],
    image[0][cols - 1]
]

corner_diffs = []
for i in range(4):
    summ = 0
    for j in range(4):
        if i != j:
            summ += sqrt((corners[j] - corners[i]) @ (corners[j] - corners[i]))
    corner_diffs.append(summ)
corner_diffs.sort()
if corner_diffs[3] != 0:
    if corner_diffs[0] / corner_diffs[3] < 0.6:
        print("triangle")
        exit(0)


filtered_image = []

background_colors = 0
foreground_colors = 0
threshold = (count_treshold(image, 0, 0, rows * 0.10, cols * 0.10, corners[0])
             + count_treshold(image, 0.90 * rows, 0, rows, cols * 0.10, corners[1])
             + count_treshold(image, 0.90 * rows, 0.90 * cols, rows, cols, corners[2])
             + count_treshold(image, 0, 0.90 * cols, 0.10 * rows, cols, corners[3])) * 0.25 + 100

# print(threshold)

for r in range(rows):
    filtered_line = []
    for c in range(cols):
        is_background = False
        for color in corners:
            if is_color_similar(color, image[r, c], threshold):
                is_background = True
                break
        if is_background:
            filtered_line.append(0.0)
            background_colors += 1
        else:
            filtered_line.append(1.0)
            foreground_colors += 1
    filtered_image.append(filtered_line)

if foreground_colors < rows * cols / 100:
    print("box")
    exit(0)

trimmed = trim(array(filtered_image), (rows + cols) * 0.05)

background_colors = 0
trimmed_rows = trimmed.shape[0]
trimmed_cols = trimmed.shape[1]
for r in range(trimmed_rows):
    for c in range(trimmed_cols):
        if trimmed[r, c] == 0:
            background_colors += 1

trimmed_size = trimmed_rows * trimmed_cols
if background_colors < 4 * (trimmed_rows + trimmed_cols):
    print("box")
elif background_colors < trimmed_size * 1.5 / 4.:
    if abs(trimmed_rows / trimmed_cols - 1.0) > 0.05:
        print("ellipse")
    else:
        print("circle")
else:
    print("triangle")

plt.imshow(image[:,:,2], cmap='gray')
plt.show()
# plt.imshow(array(trimmed), cmap='gray', interpolation='nearest')
# plt.show()
