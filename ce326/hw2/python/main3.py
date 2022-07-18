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

f = open("lena.yuv")

#image before the equalization
eikona = YUVImage(1, 2, f);

histogram = Histogram(eikona);
print(histogram.toString())

histogram.equalize();
