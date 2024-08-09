'''
╔═══════════════════════════════════════════════╗
║    SCC0251 - Image Processing and Analysis    ║
║    Year: 2024                  2º Semester    ║
╟───────────────────────────────────────────────╢
║      Student:  Fernando Gonçalves Campos      ║
║      Nº USP:   12542352                       ║
╟───────────────────────────────────────────────╢
║ Assignment 1: enhancement and superresolution ║
╚═══════════════════════════════════════════════╝
'''

import numpy as np
import numpy.typing as npt
import imageio.v3 as imageio
import os

def histogram_equalization(*args: npt.ArrayLike) -> npt.ArrayLike:
    """
    Performs histogram equalization on a single-channel grayscale image or a batch of grayscale images.

    Args:
        *args (numpy.ndarray): Either a single grayscale image or a sequence of grayscale images. Each image must be a numpy ndarray of shape (height, width).

    Returns:
        numpy.ndarray: The equalized image(s).
        - If a single image was provided, a single equalized image is returned.
        - If a batch of images was provided, a numpy array containing the equalized images is returned.
    """

    imgs = np.array(args) if len(args) != 1 else args[0]
    hist, _ = np.histogram(imgs, bins = 256, range = (0, 256), density = True)
    transfer_table = np.cumsum(hist) * 255

    return transfer_table[imgs]

def gamma_correction(image: np.ndarray, gamma: float) -> np.ndarray:
    return np.array(255 * ((image / 255) ** (1/gamma)), dtype=int)

def superresolution(img0: np.ndarray, img1: np.ndarray, img2: np.ndarray, img3: np.ndarray):
    n, m = img0.shape

    result = np.zeros((n*2, m*2), dtype=int)
    result[0::2, 0::2] = img0
    result[1::2, 0::2] = img1
    result[0::2, 1::2] = img2
    result[1::2, 1::2] = img3

    return result

def rmse(values_a: np.ndarray, values_b: np.ndarray) -> float:
    n, m = values_a.shape

    diff_values = values_a - values_b
    square_error = np.sum(diff_values ** 2)
    return np.sqrt(square_error / (n*m))

def main() -> None:
    low_file_prefix = input().rstrip("\r")
    high_filename = input().rstrip("\r")
    mode = int(input())
    gamma = float(input())

    img0 = imageio.imread(low_file_prefix + "0.png")
    img1 = imageio.imread(low_file_prefix + "1.png")
    img2 = imageio.imread(low_file_prefix + "2.png")
    img3 = imageio.imread(low_file_prefix + "3.png")

    match mode:
        case 1:
            img0 = histogram_equalization(img0)
            img1 = histogram_equalization(img1)
            img2 = histogram_equalization(img2)
            img3 = histogram_equalization(img3)

        case 2:
            img0, img1, img2, img3 = histogram_equalization(img0, img1, img2, img3)

        case 3:
            img0 = gamma_correction(img0, gamma)
            img1 = gamma_correction(img1, gamma)
            img2 = gamma_correction(img2, gamma)
            img3 = gamma_correction(img3, gamma)

    result_image = superresolution(img0, img1, img2, img3)
    high_res_image = imageio.imread(high_filename)

    error = rmse(result_image, high_res_image)
    print(f"{error:.4f}")

if __name__ == "__main__":
    main()