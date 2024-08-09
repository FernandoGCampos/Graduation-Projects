import numpy as np
import numpy.typing as npt
import scipy.ndimage as sci

x = np.arange(16)
print(x[np.where(x % 2 == 0)])
