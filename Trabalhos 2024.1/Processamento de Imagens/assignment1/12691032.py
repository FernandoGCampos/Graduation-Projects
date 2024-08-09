################################################################################
#|                       USP - Universidade de Sao Paulo                      |#
#|            ICMC - Instituto de Ciencias Matematicas e de Computacao        |#
################################################################################
#|                    Bacharelado em Ciencias de Computacao                   |#
#|                                   2024/1                                   |#
#|                   Image Processing and Analysis (SCC0251)                  |#
#|                                                                            |#
#|                      Autor: Thiago Shimada (12691032)                      |#
################################################################################
#| > Assignment 0: Enhancement and superresolution                            |#
################################################################################
import imageio.v3 as imageio
import numpy as np
import matplotlib.pyplot as plt
import os

def gamma_curve_correction(imgs, gamma):
    #gets the size of the input matrix
    N, M = imgs[0].shape

    R = 255.00 # maximum graylevel

    #create an arange to computate z_gamma adjustment
    levels = np.arange(256)

    #calculate the adjustment using the given formula
    z_gamma = (R * np.power(levels / R, 1/gamma)).astype(np.uint8)

    # create the vector of images to store the equalised version
    imgs_eq = []
    for i in range(4):
        imgs_eq.append(np.zeros([N, M]).astype(np.uint8))

    for z in range(256):
        imgs_eq[0][np.where(imgs[0] == z)] = z_gamma[z]
        imgs_eq[1][np.where(imgs[1] == z)] = z_gamma[z]
        imgs_eq[2][np.where(imgs[2] == z)] = z_gamma[z]
        imgs_eq[3][np.where(imgs[3] == z)] = z_gamma[z]

    return imgs_eq

def histogram(img, no_levels):
    #gets the size of the input matrix
    N, M = img.shape
    #creates an empty histogram with size proportional to the number of graylevels
    hist = np.zeros(no_levels)

    # computes for all levels in the range
    for i in range(no_levels):
        # sum all positions in which img == i is true
        pixels_value_i = np.sum(img == i)
        # store it in the histogram array
        hist[i] = pixels_value_i

    return(hist)

def single_image_histogram_equalization(imgs, no_levels):
    # gets the size of the input image
    N, M = imgs[0].shape

    # create the vector of images to store the equalised version
    imgs_eq = []

    # computes the image histogram
    hist = []
    for i in range(4):
        hist.append(histogram(imgs[i],  no_levels))

    # create the vector of transformed histograms
    histograms_transform = []

    for img in range(4):
        # creates an empty cumulative histogram
        histC = np.zeros(no_levels).astype(int)
        # computes the cumulative histogram
        histC[0] = hist[img][0] # first value (intensity 0)
        # from intensity 1 to no_levels-1
        for i in range(1,  no_levels):
            histC[i] = hist[img][i] + histC[i-1]

        # the vector below is used to store the actual transformation function
        # it allows us to later visualize what was the function that computed
        # the equalisation
        hist_transform = np.zeros(no_levels).astype(np.uint8)

        # create the image to store the equalised version
        img_eq = np.zeros([N,M]).astype(np.uint8)

        # for each intensity value, transforms it into a new intensity
        # using the np.where() function
        for z in range(no_levels):
            # computes what would be the output level 's' for an input value 'z'
            s = ((no_levels-1)/float(M*N))*histC[z]

            # for every coordinate in which matrix A has the value 'z'
            # assigns the transformed/equalised value 's'
            img_eq[ np.where(imgs[img] == z) ] = s

            # store the tranformation function
            hist_transform[z] = s

        # append the equalised image in the vector
        imgs_eq.append(img_eq)
        # append the transformed histogram in the vector
        histograms_transform.append(hist_transform)

    return (imgs_eq, histograms_transform)

def joint_histogram_equalization(imgs, no_levels):
    #gets the size of the input matrix
    N, M = imgs[0].shape
    #creates an empty array of four histograms with size proportional to the number of graylevels
    hist = []
    for img in imgs:
        hist_tmp = histogram(img, 256)
        hist.append(hist_tmp)

    # creates an empty cumulative histogram
    histC = np.zeros(no_levels).astype(int)
    # computes the cumulative histogram
    histC[0] = hist[0][0] + hist[1][0] + hist[2][0] + hist[3][0]
    # from intensity 1 to no_levels-1
    for i in range(1,  no_levels):
        histC[i] = hist[0][i] + hist[1][i] + hist[2][i] + hist[3][i] + histC[i-1]
    histC = histC / 4

    # the vector of vectors below is used to store the actual transformation function
    # it allows us to later visualize what was the function that computed
    # the equalisation
    hist_transform = []
    for i in range(4):
        hist_transform.append(np.zeros(no_levels).astype(int))

    # create the images to store the equalised version
    imgs_eq = []
    for i in range(4):
        imgs_eq.append(np.zeros([N, M]).astype(np.uint8))

    # for each intensity value, transforms it into a new intensity
    # using the np.where() function
    for z in range(no_levels):
        # computes what would be the output level 's' for an input value 'z'
        s = ((no_levels-1)/float(M*N))*histC[z]

        # for every coordinate in which matrices imgs have the value 'z'
        # assigns the transformed/equalised value 's'
        imgs_eq[0][imgs[0] == z] = s
        imgs_eq[1][imgs[1] == z] = s
        imgs_eq[2][imgs[2] == z] = s
        imgs_eq[3][imgs[3] == z] = s

    return (imgs_eq, hist_transform)

def superresolution(imgs):
    N, M = imgs[0].shape

    enhanced_img = np.zeros([N+N,M+M]).astype(np.uint16)

    enhanced_img[::2, ::2] = imgs[0]
    enhanced_img[1::2, ::2] = imgs[1]
    enhanced_img[::2, 1::2] = imgs[2]
    enhanced_img[1::2, 1::2] = imgs[3]

    return enhanced_img

def image_comparison(img1, img2):
    N, M = img1.shape
    sum = np.sum(np.power((img2 - img1), 2))
    sum /= (N * M)
    print(f"{np.sqrt(sum):.4f}")

imglowbasename = os.path.join(os.path.dirname(__file__), input().rstrip("\r"))
imghighname = os.path.join(os.path.dirname(__file__), input().rstrip("\r"))
enhancement_method = int(input())
gamma_parameter = float(input())

imglow = []
for i in range(4):
    imglowname = f"{imglowbasename}{i}.png"
    imglow.append(imageio.imread(imglowname))

imghigh = imageio.imread(f"{imghighname}")

enhanced_img = imghigh
if enhancement_method == 0:
    enhanced_img = imglow
elif enhancement_method == 1:
    enhanced_img, _ = single_image_histogram_equalization(imglow, 256)
elif enhancement_method == 2:
    enhanced_img, _ = joint_histogram_equalization(imglow, 256)
else:
    enhanced_img = gamma_curve_correction(imglow, gamma_parameter)

superresolution_img = superresolution(enhanced_img)

image_comparison(superresolution_img, imghigh)