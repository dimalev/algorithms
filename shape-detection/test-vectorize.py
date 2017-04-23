from numpy import array, vectorize

def G2RGB(data):
    output = []
    for line in data:
        output.append([[color, color, color] for color in line])
    return array(output)

sample = array([[1,2,3], [7,3,8]])

print(G2RGB(sample))
