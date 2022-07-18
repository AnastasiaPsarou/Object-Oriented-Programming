from RGBImage import RGBImage
from RGBPixel import RGBPixel
from PPMImage import PPMImage
from YUVPixel import YUVPixel
from YUVImage import YUVImage
from Histogram import Histogram
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from PIL import Image
import numpy as np
import os

#create a PPMImage copy of an another one
image = Image.open("dark-room_200x133.ppm")
#image.show()

file = open("dark-room_200x133.ppm")
darmRoomCopy = PPMImage(file);

f = open("img.ppm", "a")
darmRoomCopy.toFile(f)
#print("The contents of the new file", darmRoomCopy.toString())

image = Image.open("img.ppm")
image.show()

#Then the doubleSize is going to be printed
darmRoomCopy.doublesize();
fileDouble = open("img.ppm", "a")
darmRoomCopy.toFile(f)

image = Image.open("img.ppm")
image.show()

#Then the halfsize is going to be printed
darmRoomCopy.halfsize();
darmRoomCopy.toFile(f)

image = Image.open("img.ppm")
image.show()

#Then the rotation Clockwise is going to be printed
darmRoomCopy.rotateClockwise();
darmRoomCopy.toFile(f)

image = Image.open("img.ppm")
image.show()

