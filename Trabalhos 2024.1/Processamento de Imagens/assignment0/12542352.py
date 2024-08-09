'''
╔═══════════════════════════════════════════╗
║ SCC0251 - Image Processing and Analysis   ║
║ Year: 2024                  2º Semester   ║
╟───────────────────────────────────────────╢
║ Student:  Fernando Gonçalves Campos       ║
║ Nº USP:   12542352                        ║
╟───────────────────────────────────────────╢
║ Assignment 0: how to do assignments       ║
╚═══════════════════════════════════════════╝
'''

import imageio.v3 as imageio

# Reads the filename removing trailing empty spaces (Runcodes testcases leave an extra CR character at the end if the input)
filename = input().rstrip("\r")

img = imageio.imread(filename)
y_coord = int(input())
x_coord = int(input())

pixel = img[y_coord][x_coord]
print(pixel[0], pixel[1], pixel[2])