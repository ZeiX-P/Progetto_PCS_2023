import matplotlib.pyplot as plt
from matplotlib.tri import Triangulation
import numpy as np 
import pandas as pd
import csv
import itertools
 

def write_file(filename, data):
  fh = open(filename, "w")
  try:
      fh.write(data)
  finally:
      fh.close()

def file0D():
    array = []
    with open('/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug/coordinate.csv', "r") as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=' ')
        

        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
                continue
            points = []
            for i in range(1,3):
                points.append(float(row[i]))
                

            array.append(points)
    csv_file.close()
    return array

def file2D():
    array = []
    with open('/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug/vertices.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=' ')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
                continue
            points = []
            for i in range(1,4):
                points.append(int(row[i]))
        
            array.append(points)
    csv_file.close
    return array

def normal_file0D():

    array2 = []
    with open('/Users/LENOVO/Desktop/Progetto_Raffinamento/Cell0Ds.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=' ')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
                continue
            vertices = []
            for i in range(2,4):
                vertices.append(float(row[i]))
                
            array2.append(vertices)
    csv_file.close
    return array2

def normal_file2D():

    array2 = []
    with open('/Users/LENOVO/Desktop/Progetto_Raffinamento/Cell2Ds.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=' ')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
                continue
            vertices = []
            for i in range(1,4):
                vertices.append(int(row[i]))
                
            array2.append(vertices)
    csv_file.close
    return array2
   
array1 = file0D()

array2 = file2D()


#array1.sort()
#array1= list(k for k,_ in itertools.groupby(array1))
print("Numero x: " + str(len(array1)))
print("Numero triangoli :" + str(len(array2)))
nodes = np.array(array1)
print(nodes)
vertices = np.array(array2)
print(vertices)
'''
nodes = np.array([[0.,         0.        ],
 [0.,        1.        ],
 [1.,         0.        ],
 [1.,         1.        ],
 [0.,         0.33333333],
 [0.,         0.66666667],
 [0.33333333, 0.        ],
 [0.66666667, 0.        ],
 [0.33333333, 1.        ],
 [0.66666667, 1.        ],
 [1.,         0.33333333],
 [1.,         0.66666667],
 [0.48987551, 0.53023763],
 [0.43898046, 0.76879765],
 [0.70260457, 0.70541771],
 [0.23823447, 0.57580349],
 [0.30488903, 0.35751012],
 [0.7335183,  0.42800646],
 [0.52102626, 0.34589035],
 [0.80431355, 0.19597677],
 [0.19985633, 0.8004077 ],
 [0.44618858, 0.18491763],
 [0.84231781, 0.84302109],
 [0.21688219, 0.17515222],
 [0.63434267, 0.23095824]])
'''

x, y = np.degrees(nodes[:, 0]), np.degrees(nodes[:, 1])
triang = Triangulation(x, y, vertices)
plt.figure()
plt.gca().set_aspect('equal')
plt.triplot(triang, 'go-')
plt.show()
