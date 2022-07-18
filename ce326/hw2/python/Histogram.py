import numpy as np

class Histogram:
    
    def __init__(self, img):
        self.img = img;
        self.histogramArray = np.empty(shape = (236), dtype = float)
        self.balancedHistogramArray = np.empty(shape = (236), dtype = int)  
        self.CDFArray = np.empty(shape = (236), dtype = float)
        self.arrayPossibilities = np.empty(shape = (236), dtype = float)
        self.histogram = "";
        
        self.totalElements = img.height * img.width;
        
        for i in range(236): #array initialisation
            self.histogramArray[i] = 0;
            self.CDFArray[i] = 0;
        
        #in histogramArray[0] gets the number of cells of img.array with brightness 0 etc
        for i in range(img.height):
            for j in range(img.width):
                self.histogramArray[img.array[i][j].getY()] = self.histogramArray[img.array[i][j].getY()] + 1;
 
    def toString(self):
        self.histogram = "";
        
        for i in range(len(self.histogramArray)):
            foteinotita = str(i);
            self.histogram += "\n";
            self.histogram += foteinotita;
            self.histogram += ".(";
            foteinotita = str(self.histogramArray[i]);
            self.histogram += foteinotita;
            self.histogram += ")\t";    
            for j in range(int(self.histogramArray[i]/1000)):
                self.histogram += '#';
            for j in range(int(self.histogramArray[i]/100)):
                self.histogram += '$';
            for j in range(int(self.histogramArray[i]/10)):
                self.histogram += '@';
            for j in range(int(self.histogramArray[i])):
                self.histogram += '*';
                
        self.histogram += '\n';
        
        return(self.histogram);
    
    def equalize(self):        
        self.arrayPossibilities[0] = self.histogramArray[0] / self.totalElements;
        self.CDFArray[0] = self.histogramArray[0];
        
        for i in range(235):
            self.arrayPossibilities[i] = self.histogramArray[i] / self.totalElements; #possibility array
            self.CDFArray[i] = self.arrayPossibilities[i] + self.CDFArray[i - 1]; #value of last cell + doubleArray[i]
       
        for i in range(236): #balanced histogram
            self.balancedHistogramArray[i] = (int) ( 235 * self.CDFArray[i]);
            print(self.balancedHistogramArray[i])

    
    def getEqualizedLuminocity(self, luminocity):
        
        return(self.balancedHistogramArray[luminocity]);
        
    
    def toFile(self, file):
        
        try:
            file.truncate(0)
            
            file.write(self.toString())
            file.close()
        
        except IOError:
            print("An error occurred during reading");
        
