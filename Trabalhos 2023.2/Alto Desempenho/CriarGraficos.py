import csv
import matplotlib.pyplot as plt
import numpy as np
from os.path import dirname, join

directory = dirname(__file__)

#Reads data
sequencialFile = open(join(directory, 'Sequencial.csv'))
paralelo2_4File = open(join(directory, 'paralelo2-4.csv'))
paralelo4_4File = open(join(directory, 'paralelo4-4.csv'))
paralelo8_4File = open(join(directory, 'paralelo8-4.csv'))
sequencialReader = csv.reader(sequencialFile)
paralelo2_4Reader = csv.reader(paralelo2_4File)
paralelo4_4Reader = csv.reader(paralelo4_4File)
paralelo8_4Reader = csv.reader(paralelo8_4File)
sequencialHeader = next(sequencialReader)
paralelo2_4Header = next(paralelo2_4Reader)
paralelo4_4Header = next(paralelo4_4Reader)
paralelo8_4Header = next(paralelo8_4Reader)

sequencialX = []
sequencialY = []
for pair in sequencialReader:
    sequencialX.append(float(pair[0]))
    sequencialY.append(float(pair[1]))
sequencialX = np.array(sequencialX)
sequencialY = np.array(sequencialY)
sequencialFile.close()

paralelo2_4X = []
paralelo2_4Y = []
for pair in paralelo2_4Reader:
    paralelo2_4X.append(float(pair[0]))
    paralelo2_4Y.append(float(pair[1]))
paralelo2_4X = np.array(paralelo2_4X)
paralelo2_4Y = np.array(paralelo2_4Y)
paralelo2_4File.close()

paralelo4_4X = []
paralelo4_4Y = []
for pair in paralelo4_4Reader:
    paralelo4_4X.append(float(pair[0]))
    paralelo4_4Y.append(float(pair[1]))
paralelo4_4X = np.array(paralelo4_4X)
paralelo4_4Y = np.array(paralelo4_4Y)
paralelo4_4File.close()

paralelo8_4X = []
paralelo8_4Y = []
for pair in paralelo8_4Reader:
    paralelo8_4X.append(float(pair[0]))
    paralelo8_4Y.append(float(pair[1]))
paralelo8_4X = np.array(paralelo8_4X)
paralelo8_4Y = np.array(paralelo8_4Y)
paralelo8_4File.close()

plt.plot(sequencialX ** 2, sequencialY, label = 'sequencial', linewidth = 2)
plt.plot(paralelo2_4X ** 2, paralelo2_4Y, label = 'paralelo (2 proc 4 thrd)', linewidth = 2)
plt.plot(paralelo4_4X ** 2, paralelo4_4Y, label = 'paralelo (4 proc 4 thrd)', linewidth = 2)
plt.plot(paralelo8_4X ** 2, paralelo8_4Y, label = 'paralelo (8 proc 4 thrd)', linewidth = 2)

#Decorates plot
plt.xlabel("Tamanho", fontsize='large')
plt.ylabel("Tempo (s)", fontsize='large')
plt.legend(fontsize='large')

#Saves the plot in a png
plt.title("Comparação com número de processos")
plt.savefig(join(directory, "GráficoPorProcessos.png"))
plt.clf()

#Reads data
sequencialFile = open(join(directory, 'Sequencial.csv'))
paralelo4_1File = open(join(directory, 'paralelo4-1.csv'))
paralelo4_2File = open(join(directory, 'paralelo4-2.csv'))
paralelo4_4File = open(join(directory, 'paralelo4-4.csv'))
sequencialReader = csv.reader(sequencialFile)
paralelo4_1Reader = csv.reader(paralelo4_1File)
paralelo4_2Reader = csv.reader(paralelo4_2File)
paralelo4_4Reader = csv.reader(paralelo4_4File)
sequencialHeader = next(sequencialReader)
paralelo4_1Header = next(paralelo4_1Reader)
paralelo4_2Header = next(paralelo4_2Reader)
paralelo4_4Header = next(paralelo4_4Reader)

sequencialX = []
sequencialY = []
for pair in sequencialReader:
    sequencialX.append(float(pair[0]))
    sequencialY.append(float(pair[1]))
sequencialX = np.array(sequencialX)
sequencialY = np.array(sequencialY)
sequencialFile.close()

paralelo4_1X = []
paralelo4_1Y = []
for pair in paralelo4_1Reader:
    paralelo4_1X.append(float(pair[0]))
    paralelo4_1Y.append(float(pair[1]))
paralelo4_1X = np.array(paralelo4_1X)
paralelo4_1Y = np.array(paralelo4_1Y)
paralelo4_1File.close()

paralelo4_2X = []
paralelo4_2Y = []
for pair in paralelo4_2Reader:
    paralelo4_2X.append(float(pair[0]))
    paralelo4_2Y.append(float(pair[1]))
paralelo4_2X = np.array(paralelo4_2X)
paralelo4_2Y = np.array(paralelo4_2Y)
paralelo4_2File.close()

paralelo4_4X = []
paralelo4_4Y = []
for pair in paralelo4_4Reader:
    paralelo4_4X.append(float(pair[0]))
    paralelo4_4Y.append(float(pair[1]))
paralelo4_4X = np.array(paralelo4_4X)
paralelo4_4Y = np.array(paralelo4_4Y)
paralelo4_4File.close()

plt.plot(sequencialX ** 2, sequencialY, label = 'sequencial', linewidth = 2)
plt.plot(paralelo4_1X ** 2, paralelo4_1Y, label = 'paralelo (4 proc 1 thrd)', linewidth = 2)
plt.plot(paralelo4_2X ** 2, paralelo4_2Y, label = 'paralelo (4 proc 2 thrd)', linewidth = 2)
plt.plot(paralelo4_4X ** 2, paralelo4_4Y, label = 'paralelo (4 proc 4 thrd)', linewidth = 2)

#Decorates plot
plt.xlabel("Tamanho", fontsize='large')
plt.ylabel("Tempo (s)", fontsize='large')
plt.legend(fontsize='large')

#Saves the plot in a png
plt.title("Comparação com número de threads")
plt.savefig(join(directory, "GráficoPorThreads.png"))
plt.clf()

paralelo2_4X = np.delete(paralelo2_4X, 5)
paralelo4_4X = np.delete(paralelo4_4X, 5)
paralelo8_4X = np.delete(paralelo8_4X, 5)
paralelo2_4Y = np.delete(paralelo2_4Y, 5)
paralelo4_4Y = np.delete(paralelo4_4Y, 5)
paralelo8_4Y = np.delete(paralelo8_4Y, 5)
plt.plot(sequencialX ** 2, sequencialY / sequencialY, label = 'sequencial', linewidth = 2)
plt.plot(paralelo2_4X ** 2, sequencialY / paralelo2_4Y, label = 'paralelo (2 proc 4 thrd)', linewidth = 2)
plt.plot(paralelo4_4X ** 2, sequencialY / paralelo4_4Y, label = 'paralelo (4 proc 4 thrd)', linewidth = 2)
plt.plot(paralelo8_4X ** 2, sequencialY / paralelo8_4Y, label = 'paralelo (8 proc 4 thrd)', linewidth = 2)

#Decorates plot
plt.xlabel("Tamanho", fontsize='large')
plt.ylabel("Speedup", fontsize='large')
plt.legend(fontsize='large')

#Saves the plot in a png
plt.title("Comparação com número de processos")
plt.savefig(join(directory, "GráficoSpeedupPorProcessos.png"))
plt.clf()

paralelo4_1X = np.delete(paralelo4_1X, 5)
paralelo4_2X = np.delete(paralelo4_2X, 5)
paralelo4_1Y = np.delete(paralelo4_1Y, 5)
paralelo4_2Y = np.delete(paralelo4_2Y, 5)
plt.plot(sequencialX ** 2, sequencialY / sequencialY, label = 'sequencial', linewidth = 2)
plt.plot(paralelo4_1X ** 2, sequencialY / paralelo4_1Y, label = 'paralelo (4 proc 1 thrd)', linewidth = 2)
plt.plot(paralelo4_2X ** 2, sequencialY / paralelo4_2Y, label = 'paralelo (4 proc 2 thrd)', linewidth = 2)
plt.plot(paralelo4_4X ** 2, sequencialY / paralelo4_4Y, label = 'paralelo (4 proc 4 thrd)', linewidth = 2)

#Decorates plot
plt.xlabel("Tamanho", fontsize='large')
plt.ylabel("Speedup", fontsize='large')
plt.legend(fontsize='large')

#Saves the plot in a png
plt.title("Comparação com número de threads")
plt.savefig(join(directory, "GráficoSpeedupPorThreads.png"))
plt.clf()

plt.plot(sequencialX ** 2, sequencialY / sequencialY, label = 'sequencial', linewidth = 2)
plt.plot(paralelo2_4X ** 2, (sequencialY / paralelo2_4Y) / 8, label = 'paralelo (2 proc 4 thrd)', linewidth = 2)
plt.plot(paralelo4_4X ** 2, (sequencialY / paralelo4_4Y) / 16, label = 'paralelo (4 proc 4 thrd)', linewidth = 2)
plt.plot(paralelo8_4X ** 2, (sequencialY / paralelo8_4Y) / 32, label = 'paralelo (8 proc 4 thrd)', linewidth = 2)
#Decorates plot
plt.xlabel("Tamanho", fontsize='large')
plt.ylabel("Eficiência", fontsize='large')
plt.legend(fontsize='large')

#Saves the plot in a png
plt.title("Comparação com número de processos")
plt.savefig(join(directory, "GráficoEficiênciaPorProcessos.png"))
plt.clf()

plt.plot(sequencialX ** 2, sequencialY / sequencialY, label = 'sequencial', linewidth = 2)
plt.plot(paralelo4_1X ** 2, (sequencialY / paralelo4_1Y) / 4, label = 'paralelo (4 proc 1 thrd)', linewidth = 2)
plt.plot(paralelo4_2X ** 2, (sequencialY / paralelo4_2Y) / 8, label = 'paralelo (4 proc 2 thrd)', linewidth = 2)
plt.plot(paralelo4_4X ** 2, (sequencialY / paralelo4_4Y) / 16, label = 'paralelo (4 proc 4 thrd)', linewidth = 2)

#Decorates plot
plt.xlabel("Tamanho", fontsize='large')
plt.ylabel("Eficiência", fontsize='large')
plt.legend(fontsize='large')

#Saves the plot in a png
plt.title("Comparação com número de threads")
plt.savefig(join(directory, "GráficoEficiênciaPorThreads.png"))
plt.clf()