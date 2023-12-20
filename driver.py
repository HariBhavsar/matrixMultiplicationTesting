import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt 
import subprocess

naiveData = np.zeros(1)
loopData = np.zeros(1)
parData = np.zeros(1)
simdData = np.zeros(1)
threadData = np.zeros(1)
xArray = np.zeros(1)

num = input("Enter largest dimension to check : ")
num = int(num)

for i in range(1,num):
    
    with open('num.txt','w') as file:
        l = str(i)
        file.write(l)

    subprocess.run(['bash','autotest.sh'], check=True)

    with open('output.txt','r') as file:
        content = file.read()
        number = float(content)
        loopData = np.append(loopData,number)

    with open('outputNAIVE.txt','r') as file:
        content = file.read()
        number = float(content)
        naiveData = np.append(naiveData,number)

    with open('outputSIMD.txt','r') as file:
        content = file.read()
        number = float(content)
        simdData = np.append(simdData,number)

    with open('outputPar.txt','r') as file:
        content = file.read()
        number = float(content)
        parData = np.append(parData,number)

    with open('outputThread.txt','r') as file:
        content = file.read()
        number = float(content)
        threadData = np.append(threadData,number)

    xArray = np.append(xArray,i)

    print("Iteration number ",i," done")

plt.plot(xArray, naiveData, label='naive', color='blue')
plt.plot(xArray, loopData, label='loop reorder', color='green')
plt.plot(xArray, simdData, label='just simd', color='red')
plt.plot(xArray, parData, label='parallel', color='pink')
plt.plot(xArray, threadData, label='all', color='black')

plt.title('Comparision of different matrix multiplication algos')
plt.xlabel('size of square matrix')
plt.ylabel('time taken in seconds')
plt.legend() 
plt.grid(False)

plt.show()