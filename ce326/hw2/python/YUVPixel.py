from RGBPixel import RGBPixel

class YUVPixel:
    
    #I created one init function, while before there were 3
    #If pixel is of type YUPixel -> 1st case
    #If pixel is of type RGBPixel -> 2nd case
    #If we get Y, U, V values -> 3rd case
    def __init__(self, Y, U, V, pixel):
        
        if(isinstance(pixel, YUVPixel)):
            self.Y = pixel.Y;
            self.U = pixel.U;
            self.V = pixel.V;
        elif(isinstance(pixel, RGBPixel)):
            self.Y = (((66 * pixel.Red + 129 * pixel.Green +  25 * pixel.Blue + 128) >> 8) + 16);
            self.U = ((( -38 * pixel.Red -  74 * pixel.Green + 112 * pixel.Blue + 128) >> 8) + 128);
            self.V = ((( 112 * pixel.Red -  94 * pixel.Green -  18 * pixel.Blue + 128) >> 8) + 128);
        else:
            self.Y = Y;
            self.U = U;
            self.V = V;
            
    
    def getY(self):
         return(self.Y);
     
    
    def getU(self):
        return(self.U);
    
    
    def getV(self):
        return(self.V);
    
     
    def setY(self, Y):
        self.Y = Y;
    
    
    def setU(self, U):
        self.U = U;
    
    
    def setV(self, V):
        self.V = V;
    

