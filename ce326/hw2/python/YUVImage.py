from RGBPixel import RGBPixel
from RGBImage import RGBImage
from YUVPixel import YUVPixel
from PPMImage import PPMImage
from Histogram import Histogram
from UnsupportedFileFormatException import UnsupportedFileFormatException
import os
import numpy as np
import os.path
import io
import imghdr
from pathlib import Path


class YUVImage:
    
    def __init__(self, width, height, imgorfile):
        self.width = width;
        self.height = height;
        self.array = np.empty(shape = (self.height, self.width), dtype = YUVPixel)
        
        #if the imgorfile variable is not an image nor a file 
        #in this case we just initiate with (16, 16, 16, 128)
        if((not isinstance(imgorfile, io.IOBase)) & (not(isinstance(imgorfile, YUVImage))) & (not(isinstance(imgorfile, RGBImage)))):
            for i in range(self.height):
                for j in range(self.width):
                    self.array[i][j] = YUVPixel(16, 16, 16, 128);
        #case that we want to copy the image from another YUVImage
        elif(isinstance(imgorfile, YUVImage)):
            self.width = imgorfile.width;
            self.height = imgorfile.height;
            
            for i in range(height):
                for j in range(width):
                    self.array[i][j] = YUVPixel(imgorfile.array[i][j].getY(), imgorfile.array[i][j].getU(), imgorfile.array[i][j].getV(), 0);
        
        #case that we want to copy the image from another RGBImage
        elif(isinstance(imgorfile, RGBImage)):
            self.width = imgorfile.width;
            self.height = imgorfile.height;
            
            for i in range(height):
                for j in range(width):
                    self.array[i][j] = YUVPixel(5, 0, 0, imgorfile);
            
        #case that we want to create the image from a file
        elif(isinstance(imgorfile, io.IOBase)):
            times = 0; #mas leei se poia metavliti anaferetai h kathe timi pou yparxei sto arxeio
            first = 1; #distinguish height, width, colordepth from red, blue, green
            heightHelp = 0;
            widthHelp = 0;
            var = 0;
            
            try:
                strPpm = os.path.basename(imgorfile.name)
                if((strPpm[len(strPpm) - 4 : len(strPpm)]) != '.yuv'):
                    raise UnsupportedFileFormatException()
                
                string = imgorfile.read().rstrip('\n')
      
                splits = string.split(); #traverse first object(YUV)
                
                #read the information from the .yuv file and save them to array, width, height
                for split in splits:
                    var = var + 1
                    if(var == 1):
                        continue
                    
                    times = times + 1;
                    if(first == 1):
                        if(times == 1):
                            self.width = int(split);
                        elif(times == 2):
                            self.height = int(split);

                            self.array = np.empty(shape = (self.height, self.width), dtype = YUVPixel)
                            for k in range(self.height): #initialisation rgb array
                                for j in range(self.width):
                                    self.array[k][j] = YUVPixel(0, 0, 0, 0);
                                    
                            first = 0;
                            times = 0;
                            
                    else:
                        if(times == 1):
                            self.array[heightHelp][widthHelp].setY(int(split));
                        
                        elif(times == 2):
                            self.array[heightHelp][widthHelp].setU(int(split));
                            
                        elif(times == 3):
                            self.array[heightHelp][widthHelp].setV(int(split));
                            times = 0;
                            if((heightHelp == self.height - 1) & (widthHelp == self.width - 1)):
                                break;
                            elif(widthHelp == (self.width - 1)): #reinitialisation
                                widthHelp = 0;
                                heightHelp = heightHelp + 1;
                            else:
                                widthHelp = widthHelp + 1;
                            
            except FileNotFoundError:
                print("File not Found!")
            except UnsupportedFileFormatException:
                print("UnsupportedFileFormatException")
            
    
    def toString(self):
        mystr = "YUV3";
        mystr += '\n'
        mystr += str(self.width);
        mystr += " "
        mystr += str(self.height);
        mystr += "\n"
        
        
        for i in range(self.height):
            for j in range(self.width):
                mystr += str(self.array[i][j].getY())
                mystr += " "
                mystr += str(self.array[i][j].getU())
                mystr += " "
                mystr += str(self.array[i][j].getV());
                mystr += "\n"

        return(mystr);
    
    
    def toFile(self, file):
        
        try:
            file.truncate(0)
            
            mystr = self.toString();
            file.write(mystr)
        
        except IOError:
           print("An error occurred during reading");
    
    def equalize(self):
        histogram = Histogram(self);
        histogram.equalize();
        
        #copy in a yuv array the balanced one
        for i in range(self.height):
            for j in range(self.width):
                    value = self.array[i][j].getY();
                    self.array[i][j].setY(histogram.balancedHistogramArray[value]);

