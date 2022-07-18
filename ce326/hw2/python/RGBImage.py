from RGBPixel import RGBPixel
import numpy as np

MAX_COLORDEPTH = 255

class RGBImage:

    def __init__(self, width, height, colordepth):#default constructor
        self.width = width;
        self.height = height;
        self.colordepth = colordepth;
        self.array = np.empty(shape = (self.width, self.height), dtype = RGBPixel);
        
        for i in range(self.height):
            for j in range (self.width):
                self.array[i][j] = RGBPixel(0, 0, 0, 0);
    

    def RGBImage_copy(self, copyImg): #image copy of copyImg
        self.colordepth = copyImg.colordepth;
        self.height = copyImg.height;
        self.width = copyImg.width;
        self.array.resize((copyImg.width, copyImg.height), refcheck = False);
        self.array = copyImg.array;

    def RGBImage_yuv(self, YUVImg):
        self.colordepth = 255;
        self.height = YUVImg.height;
        self.width = YUVImg.width;
     
        self.array = RGBPixel[self.height][self.width]();
        for i in range(self.height):
            for j in range (self.width):
                self.array[i][j] = RGBPixel(YUVImg.array[i][j]);

    def getWidth(self):
        return (self.width);

    def getHeight(self):
        return (self.height);

    def getColorDepth(self):
        return (self.colordepth);

    def getPixel(self,row, col):
        return self.array[row][col];

    def setPixel(self, row, col, pixel):
        self.array[row][col] = pixel;
        self.array[row][col].Red = pixel.Red;
        self.array[row][col].Green = pixel.Green;
        self.array[row][col].Blue = pixel.Blue;

    def printRGB(self):
        for i in range(self.height):
            for j in range (self.width):
                print(str(self.array[i][j].Red) + ", " + str(self.array[i][j].Green) + ", " + str(self.array[i][j].Blue));
                

    def grayscale(self): # in every pixel -> red*0.3, green*0.59, blue*0.11
        gray = 0; #all 3 colours have the same value
        for i in range(self.height):
            for j in range (self.width):
                 gray = (0.11 * self.array[i][j].Blue) + (0.3 * self.array[i][j].Red) + (0.59 * self.array[i][j].Green);
                 self.array[i][j].Blue = gray;
                 self.array[i][j].Red = gray;
                 self.array[i][j].Green = gray;
 

    def doublesize(self): #brightness of each pixel is copied in different positions
        arrayhelp = np.empty(shape = (2 * self.height, 2 * self.width), dtype = RGBPixel)
       
        for i in range(self.height * 2):
            for j in range (self.width * 2):
                arrayhelp[i][j] = RGBPixel(1, 2, 3, 15);
 
        for i in range(self.height):
            for j in range (self.width):
                 arrayhelp[2 * i][2 * j] = self.array[i][j];
                 arrayhelp[2 * i + 1][2 * j] = self.array[i][j];
                 arrayhelp[2 * i][2 * j + 1] = self.array[i][j];
                 arrayhelp[2 * i + 1][2 * j + 1] = self.array[i][j];
        
        
        self.array = arrayhelp;
        self.height = 2 * self.height;
        self.width = 2 * self.width;
        

    def foursize(self): #brightness of each pixel is copied in different positions
        arrayhelp = np.empty(shape = (4 * self.width, 4 * self.height), dtype = RGBPixel)
 
        for i in range(self.height * 4):
            for j in range (self.width * 4):
                arrayhelp[i][j] = RGBPixel(1, 2, 3, 15);

        for i in range(self.height):
            for j in range (self.width):
               arrayhelp[4 * i][4 * j] = self.array[i][j];
               arrayhelp[4 * i + 2][4 * j] = self.array[i][j];
               arrayhelp[4 * i][4 * j + 2] = self.array[i][j];
               arrayhelp[4 * i + 2][4 * j + 2] = self.array[i][j];
      
        self.array = arrayhelp;
        self.height = 4 * self.height;
        self.width = 4 * self.width;
    

    def halfsize(self): # brightness of a pixel = average brightness of other pixels
        mesosOrosBlue = 0;
        mesosOrosRed = 0;
        mesosOrosGreen = 0;

        arrayhelp = np.empty(shape = (int(self.height / 2), int(self.width / 2)), dtype = RGBPixel)

        for i in range(int(self.height / 2)):
            for j in range (int(self.width / 2)):
                arrayhelp[i][j] = RGBPixel(1, 2, 3, 15);

        for i in range(int(self.height / 2)):
            for j in range (int(self.width / 2)):
               mesosOrosBlue += self.array[2 * i][2 * j].Blue;
               mesosOrosBlue += self.array[2 * i + 1][2 * j].Blue;
               mesosOrosBlue += self.array[2 * i][2 * j + 1].Blue;
               mesosOrosBlue += self.array[2 * i + 1][2 * j + 1].Blue;
   
               arrayhelp[i][j].Blue = int(mesosOrosBlue / 4);
   
               mesosOrosRed += self.array[2 * i][2 * j].Red;
               mesosOrosRed += self.array[2 * i + 1][2 * j].Red;
               mesosOrosRed += self.array[2 * i][2 * j + 1].Red;
               mesosOrosRed += self.array[2 * i + 1][2 * j + 1].Red;
   
               arrayhelp[i][j].Red = int(mesosOrosRed / 4);
   
               mesosOrosGreen += self.array[2 * i][2 * j].Green;
               mesosOrosGreen += self.array[2 * i + 1][2 * j].Green;
               mesosOrosGreen += self.array[2 * i][2 * j + 1].Green;
               mesosOrosGreen += self.array[2 * i + 1][2 * j + 1].Green;
   
               arrayhelp[i][j].Green = int(mesosOrosGreen / 4);
   
               mesosOrosBlue = 0;
               mesosOrosRed = 0;
               mesosOrosGreen = 0;


        self.array = arrayhelp;
        self.height = int(self.height / 2);
        self.width = int(self.width / 2);


    def rotateClockwise(self): #rotate a photo 90 degrees clockwise
        arrayHelp = np.empty(shape = (self.width, self.height), dtype = RGBPixel)
        newColumn = 0;
        newRow = 0;

        for i in range(self.height):
            for j in range (self.width):
                arrayHelp[j][self.height - i - 1] = self.array[i][j];
 

        self.array = arrayHelp;
        newHeight = self.width;
        self.width = self.height;
        self.height = newHeight;
        
                 
                 
