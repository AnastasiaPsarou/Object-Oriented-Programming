from RGBImage import RGBImage
from RGBPixel import RGBPixel
from UnsupportedFileFormatException import UnsupportedFileFormatException
import os
import numpy as np
import os.path
import io
import imghdr
from os.path import exists
from os import path

class PPMImage(RGBImage):
        
    def __init__(self, f): #throws FileNotFoundException, UnsupportedFileFormatException//a copy of a ppm image
           
        #if f is an image
        if(isinstance(f, RGBImage)):
            self.height = f.height;
            self.width = f.width;
            self.colordepth = f.colordepth;
            self.array = np.empty(shape = (self.width, self.height), dtype = RGBPixel);
            
            for i in range(self.height):
                for j in range(self.width):
                    self.array[i][j]= f.array[i][j];
        
        #if the f is a file
        elif(isinstance(f, io.IOBase)):
            times = 0; #mas leei se poia metavliti anaferetai h kathe timi pou yparxei sto arxeio
            first = 1; #distinguish height, width, colordepth from red, blue, green
            heightHelp = 0;
            widthHelp = 0;
            var = 0;
            
            self.f = f;
            
            try:
                strPpm = os.path.basename(f.name)
                if((strPpm[len(strPpm) - 4 : len(strPpm)]) != '.ppm'):
                    raise UnsupportedFileFormatException()
                
                string = f.read().rstrip('\n')
       
                splits = string.split(); #traverse first object(P3)
                
                #read the information from the .ppm file and save them to array, width, height, colordepth
                for split in splits:
                    var = var + 1
                    if(var == 1):
                        continue
                    
                    times = times + 1;
                    if first == 1:
                        if times == 1:
                            self.width = int(split);
                        elif times == 2:
                            self.height = int(split);
                        elif times == 3:
                            self.colordepth = int(split);
                            
                            self.array = np.empty(shape = (self.height, self.width), dtype = RGBPixel)
                            for k in range(self.height): #initialisation rgb array
                                for j in range(self.width):
                                    self.array[k][j] = RGBPixel(0, 0, 0, 255);
                                    
                            first = 0;
                            times = 0;
        
                    else:
                       if times == 1: #times = 1 ->red colour
                            self.array[heightHelp][widthHelp].Red = int(split);
        
                       elif times == 2: #times = 2 ->green colour
                            self.array[heightHelp][widthHelp].Green = int(split);
                        
                       elif times == 3: #times = 3 ->blue colour
                            self.array[heightHelp][widthHelp].Blue = int(split);
                            times = 0; #initialisation of height/width for next loop
                            
                            if (heightHelp == self.height - 1) & (widthHelp == self.width - 1):
                                break;
                                
                            elif widthHelp == (self.width - 1): #reinitialise so that colours get in the right pixels
                                widthHelp = 0;
                                heightHelp = heightHelp + 1;
                                
                            else:
                                widthHelp = widthHelp + 1;
                            
            except FileNotFoundError:
                print("File not Found!")
            except UnsupportedFileFormatException:
                print("UnsupportedFileFormatException")
                
                
        else:
            self.height = 0;
            self.width = 0;
            self.colordepth = 0;
            self.array = np.empty(shape = (self.width, self.height), dtype = RGBPixel);            
                
    
    
    #initilisation of an image created from ppmimagestacker
    def PPMImage_fromstacker(self, img, number):
        self.height = img.height;
        self.width = img.width;
        self.colordepth = img.colordepth;
        self.array = np.empty(shape = (self.width, self.height), dtype = RGBPixel);
    
    def toString(self):        
        mystr = "P3\n"
        mystr += str(self.width);
        mystr += " "
        mystr += str(self.height);
        mystr += "\n"
        mystr += str(self.colordepth);
        mystr += "\n"
        
        for i in range(self.height):
            for j in range (self.width):
                 mystr += str(self.array[i][j].Red)
                 mystr += " "
                 mystr += str(self.array[i][j].Green)
                 mystr += " "
                 mystr += str(self.array[i][j].Blue)
                 mystr += " "
                 
            mystr += "\n"
        
        return(mystr)
    
    def toFile(self, file):
        try:
            self.f = file
            
            #delete the contents of the file
            file.truncate(0)
            
            string = "P3";
            string += "\n";
            string += str(self.width);
            string += " ";
            string += str(self.height);
            string += "\n";
            string += "255";
            string += "\n";
        
            for i in range(self.height):
                for j in range(self.width):
                    string += str(self.array[i][j].Red)
                    string += " ";
                    string += str(self.array[i][j].Green)
                    string += " ";
                    string += str(self.array[i][j].Blue)
                    string += " ";
                string += "\n";
            
            file.write(string)
        
        except IOError:
            print("An error occurred during writing");
    
