'''
╔═══════════════════════════════════════════════╗
║    SCC0251 - Image Processing and Analysis    ║
║    Year: 2024                  2º Semester    ║
╟───────────────────────────────────────────────╢
║      Student:  Fernando Gonçalves Campos      ║
║      Nº USP:   12542352                       ║
╟───────────────────────────────────────────────╢
║                 Assignment 2:                 ║
║              Fourier Transform &              ║
║         Filtering in Frequency Domain         ║
╚═══════════════════════════════════════════════╝
'''

import numpy as np
import imageio.v3 as imageio

def get_center_distances(shape) -> tuple[np.ndarray, np.ndarray]:
    '''
    Get the distances from the origin point of the fourier transform after the shift
    '''
    height, width = shape
    vertical_center = height / 2
    horizontal_center = width / 2

    vertical_distances, horizontal_distances = np.ogrid[0:height, 0:width]

    vertical_distances = vertical_distances - vertical_center
    horizontal_distances = horizontal_distances - horizontal_center

    return vertical_distances, horizontal_distances

def get_low_pass_filter(shape, r: float) -> np.ndarray:
    filter = np.zeros(shape)

    vertical_distances, horizontal_distances = get_center_distances(shape)
    square_radii = np.sqrt(np.square(vertical_distances) + np.square(horizontal_distances))

    square_r = r
    filter[square_radii <= square_r] = 1

    return filter

def get_high_pass_filter(shape, r: float) -> np.ndarray:
    filter = np.zeros(shape)

    vertical_distances, horizontal_distances = get_center_distances(shape)
    square_radii = np.sqrt(np.square(vertical_distances) + np.square(horizontal_distances))

    square_r = r
    filter[square_radii > square_r] = 1

    return filter

def get_band_stop_filter(shape, r0: float, r1: float) -> np.ndarray:
    filter = np.ones(shape)

    vertical_distances, horizontal_distances = get_center_distances(shape)
    square_radii = np.square(vertical_distances) + np.square(horizontal_distances)

    square_r0 = np.square(r0)
    square_r1 = np.square(r1)
    filter[np.logical_and(square_radii > square_r1, square_radii <= square_r0)] = 0

    return filter

def get_lamplacian_high_pass_filter(shape) -> np.ndarray:
    vertical_distances, horizontal_distances = get_center_distances(shape)

    filter: np.ndarray = (-4 * np.square(np.pi)) * (np.square(vertical_distances) + np.square(horizontal_distances))

    return filter

def get_gaussian_low_pass_filter(shape, s0: float, s1: float) -> np.ndarray:
    vertical_distances, horizontal_distances = get_center_distances(shape)

    square_s0 = np.square(s0) * 2
    square_s1 = np.square(s1) * 2

    x = (np.square(vertical_distances) / square_s0) + (np.square(horizontal_distances) / square_s1)

    return np.exp(-x)

def rmse(values_a: np.ndarray, values_b: np.ndarray) -> float:
    n, m = values_a.shape

    diff_values = values_a - values_b
    square_error = np.sum(diff_values ** 2)

    return np.sqrt(square_error / (n*m))


def main() -> None:
    image_filename = input().rstrip('\r')
    ref_image_filename = input().rstrip('\r')
    filter_index = int(input())

    image = imageio.imread(image_filename)
    image_fourier = np.fft.fft2(image)
    image_fourier = np.fft.fftshift(image_fourier)

    filter = np.ones(image_fourier.shape)

    match filter_index:
        case 0:
            radius = float(input())
            filter = get_low_pass_filter(filter.shape, radius)
        case 1:
            radius = float(input())
            filter = get_high_pass_filter(filter.shape, radius)
        case 2:
            radius0 = float(input())
            radius1 = float(input())
            filter = get_band_stop_filter(filter.shape, radius0, radius1)
        case 3:
            filter = get_lamplacian_high_pass_filter(filter.shape)
        case 4:
            sigma0 = float(input())
            sigma1 = float(input())
            filter = get_gaussian_low_pass_filter(filter.shape, sigma0, sigma1)

    # Applies the filter the image frequencies
    result_image_fourier = image_fourier * filter

    # Inverse fourier transform
    result_image_fourier = np.fft.ifftshift(result_image_fourier)
    result_image = np.fft.ifft2(result_image_fourier).real

    # Normalizes the pixels to be values in the range [0, 255]
    result_image = result_image - np.min(result_image)
    result_image = result_image / np.max(result_image)
    result_image = (result_image * 255).astype(np.uint8)

    reference_image = imageio.imread(ref_image_filename)

    error = rmse(result_image, reference_image)
    print(f"{error:.4f}")

if __name__ == "__main__":
    main()