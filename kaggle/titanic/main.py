# 0           1        2      3                         4    5   6     7     8         9    10    11
# PassengerId,         Pclass,Name,                     Sex, Age,SibSp,Parch,Ticket,   Fare,Cabin,Embarked
# PassengerId,Survived,Pclass,Name,                     Sex, Age,SibSp,Parch,Ticket,   Fare,Cabin,Embarked
# 1,          0,       3,     "Braund, Mr. Owen Harris",male,22, 1,    0,    A/5 21171,7.25,,     S


import csv
from math import floor

def convert_data(line):
    g = 1 if line[3] == 'female' else 0
    c = 1.0 if line[10] == 'C' else 0.0
    q = 1.0 if line[10] == 'Q' else 0.0
    s = 1.0 if line[10] == 'S' else 0.0
    Mr = 1.0 if "Mr." in line[2] else 0.0
    Ms = 1.0 if "Ms." in line[2] else 0.0
    Mrs = 1.0 if "Mrs." in line[2] else 0.0
    Don = 1.0 if "Don." in line[2] or "Dona." in line[2] else 0.0
    Master = 1.0 if "Master." in line[2] else 0.0
    Miss = 1.0 if "Miss." in line[2] else 0.0
    Rev = 1.0 if "Rev." in line[2] else 0.0
    Dr = 1.0 if "Dr." in line[2] else 0.0
    Col = 1.0 if "Col." in line[2] else 0.0
    Mme = 1.0 if "Mme." in line[2] else 0.0
    Major = 1.0 if "Major." in line[2] else 0.0
    Sir = 1.0 if "Sir." in line[2] else 0.0
    Mlle = 1.0 if "Mlle." in line[2] else 0.0
    row = [line[1]]  + [g] + line[4:7] + line[8:9] + [c, q, s] + [Mr, Ms, Mrs, Don, Master, Miss, Rev, Dr, Col, Mme, Major, Sir, Mlle]
    crow = [(v if v != "" else "0.0") for v in row]
    irow = list(map(float, crow))
    return irow
    

def write_data(cdata, input_csvfile, output_csvfile):
    input_writer = csv.writer(input_csvfile, delimiter = " ")
    output_writer = csv.writer(output_csvfile, delimiter = " ")
    for line in cdata:
        input_writer.writerow(convert_data([line[0]] + line[2:]))
        output_writer.writerow([line[1]])

data = []
with open("train.csv") as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)

cdata = data[1:]

limit = floor(len(cdata) * 0.8)

with open("train-converted.csv", "w") as input_csvfile:
    with open("train-output.csv", "w") as output_csvfile:
        write_data(cdata[0:limit], input_csvfile, output_csvfile)

with open("validate-converted.csv", "w") as input_csvfile:
    with open("validate-output.csv", "w") as output_csvfile:
        write_data(cdata[limit:], input_csvfile, output_csvfile)

test = []
with open("test.csv") as csvfile:
    reader = csv.reader(csvfile)
    test = list(reader)

ctest = test[1:]
with open("test-converted.csv", "w") as csvfile:
    test_writer = csv.writer(csvfile, delimiter = " ")
    for line in ctest:
        test_writer.writerow(convert_data(line))
