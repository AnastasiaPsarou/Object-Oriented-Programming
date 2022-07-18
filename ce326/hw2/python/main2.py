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


f = open("landscape.yuv")

#image before the equalization
eikona = YUVImage(1, 2, f);
print(eikona.toString())

#image after the equalization
eikona.equalize();
print(eikona.toString())

file = open("eikona.yuv", "a")
eikona.toFile(file)
