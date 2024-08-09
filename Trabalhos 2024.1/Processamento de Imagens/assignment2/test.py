import numpy as np

x = np.arange(16).reshape(4,4)
print(np.fft.fftshift(x))