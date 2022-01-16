
package ce326.hw2;

import ce326.hw2.RGBPixel;
import java.awt.Graphics2D;
import java.awt.Image;
import java.io.File;
import java.io.IOException;
import java.lang.*;

import javax.imageio.ImageIO;

public class RGBImage implements ce326.hw2.Image, Cloneable{
    public int colordepth;
    public int width;
    public int height;
    RGBPixel[][] array;
    public final int MAX_COLORDEPTH = 255;
        
    public RGBImage(){//default constructor
    }
    
    public RGBImage(int width, int height, int colordepth){
        this.width = width;
        this.height = height;
        this.colordepth = colordepth;
        array = new RGBPixel[height][width];
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                array[i][j] = new RGBPixel();
            }
        }
    }
    
    public RGBImage(RGBImage copyImg){//image copy of copyImg
        colordepth = copyImg.colordepth;
        height = copyImg.height;
        width = copyImg.width;
        array = new RGBPixel[height][width];
        array = copyImg.array;
    }
    
    public RGBImage(YUVImage YUVImg){
        colordepth = 255;
        height = YUVImg.height;
        width = YUVImg.width;
        
        array = new RGBPixel[height][width];
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                array[i][j] = new RGBPixel(YUVImg.array[i][j]);
            }
        }
    
    }
    
    int getWidth(){
        return(width);
    }
    
    int getHeight(){
        return(height);
    }
    
    int getColorDepth(){
        return(colordepth);
    }
    
    RGBPixel getPixel(int row, int col){
        return array[row][col];
    }
    
    void setPixel(int row, int col,  RGBPixel pixel){        
        array[row][col]= pixel;
        array[row][col].Red = pixel.Red;
        array[row][col].Green = pixel.Green;
        array[row][col].Blue = pixel.Blue;
    }
    
    public void printRGB(){
         for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                String fs = String.format("%s %s %s\n", array[i][j].Red, array[i][j].Green, array[i][j].Blue);
                System.out.println(fs);
            }
         }
    }
    
    public RGBImage clone() throws CloneNotSupportedException {
        RGBImage b = (RGBImage)super.clone();
        return b;
    }
    
    public void grayscale(){//in every pixel -> red*0.3, green*0.59, blue*0.11
        short gray = 0;//all 3 colours have the same value
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                gray = (short) ((0.11 * array[i][j].Blue) + (0.3 * array[i][j].Red) + (0.59 * array[i][j].Green));
                array[i][j].Blue = gray;
                array[i][j].Red = gray;
                array[i][j].Green = gray;
            }
        }        
    }
   
    public void doublesize(){//brightness of each pixel is copied in different positions
        RGBPixel [][] arrayhelp = new RGBPixel[2*height][2*width];
        for(int i = 0; i < (height*2); i++){
            for(int j = 0; j < (width*2); j++){
               arrayhelp[i][j] = new RGBPixel((short)1, (short)2, (short)3);
            }
        }
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                arrayhelp[2*i][2*j] = array[i][j];
                arrayhelp[2*i + 1][2*j] = array[i][j];
                arrayhelp[2*i][2*j + 1] = array[i][j];
                arrayhelp[2*i + 1][2*j + 1] = array[i][j];
            }   
        }
        array = arrayhelp.clone();
        height = 2*height;
        width = 2*width;
   }
   
    public void halfsize(){//brightness of a pixel = average brightness of other pixels
        int mesosOrosBlue = 0;
        int mesosOrosRed = 0;
        int mesosOrosGreen = 0;
        
        RGBPixel [][] arrayhelp = new RGBPixel[height/2][width/2];
        
        for(int i = 0; i < (height/2); i++){
            for(int j = 0; j < (width/2); j++){
               arrayhelp[i][j] = new RGBPixel((short)1, (short)2, (short)3);
            }
        }
               
        for(int i = 0; i < (height/2); i++){
            for(int j = 0; j < (width/2); j++){
                
                mesosOrosBlue += array[2*i][2*j].Blue;
                mesosOrosBlue += array[2*i + 1][2*j].Blue;
                mesosOrosBlue += array[2*i][2*j + 1].Blue;
                mesosOrosBlue += array[2*i + 1][2*j + 1].Blue;
                
                arrayhelp[i][j].Blue = (short) (mesosOrosBlue/4);
                
                mesosOrosRed += array[2*i][2*j].Red;
                mesosOrosRed += array[2*i + 1][2*j].Red;
                mesosOrosRed += array[2*i][2*j + 1].Red;
                mesosOrosRed += array[2*i + 1][2*j + 1].Red;
                
                arrayhelp[i][j].Red = (short) (mesosOrosRed/4);
                
                mesosOrosGreen += array[2*i][2*j].Green;
                mesosOrosGreen += array[2*i + 1][2*j].Green;
                mesosOrosGreen += array[2*i][2*j + 1].Green;
                mesosOrosGreen += array[2*i + 1][2*j + 1].Green;
                
                arrayhelp[i][j].Green = (short) (mesosOrosGreen/4);
                
                mesosOrosBlue = 0;
                mesosOrosRed = 0;
                mesosOrosGreen = 0;
            }
        }
        
        array = arrayhelp.clone();
        height = height/2;
        width = width/2;
        
   }
   
    public void rotateClockwise(){//rotate a photo 90 degrees clockwise
        RGBPixel[][] arrayHelp = new RGBPixel[width][height];
        int newHeight;
        int newColumn = 0;
        int newRow = 0;
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                arrayHelp[j][height - i -1] = array[i][j];
            }
        }

        array = arrayHelp.clone();
        newHeight = width;
        width = height;
        height = newHeight;
        
    }

   
}
