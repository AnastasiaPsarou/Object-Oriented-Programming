
package ce326.hw2;

import java.io.FileNotFoundException;
import java.io.File;
import ce326.hw2.UnsupportedFileFormatException;
import java.util.Scanner;
import java.io.File;  
import java.io.IOException; 
import java.io.FileWriter; 
import java.util.Scanner;
import java.io.FileReader;  
import java.io.PrintWriter; 
import java.util.ArrayList;
import java.io.FileInputStream; 
import java.nio.file.FileAlreadyExistsException;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Formatter;
import java.io.*;  
import java.lang.*;
import static java.lang.Character.isWhitespace;

public class PPMImage extends RGBImage{
    File f;
    
    public PPMImage(java.io.File file) throws FileNotFoundException, UnsupportedFileFormatException{//a copy of a ppm image
        int times = 0;//mas leei se poia metavliti anaferetai h kathe timi pou yparxei sto arxeio
        int first = 1;//distinguish height, width, colordepth from red, blue, green
        int heightHelp = 0;
        int widthHelp = 0;
        String strPpm;
        
        try{
            strPpm = file.getName();
            if(!((strPpm.charAt(strPpm.length() - 1) == 'm') & (strPpm.charAt(strPpm.length() - 2) == 'p') & (strPpm.charAt(strPpm.length() - 3) == 'p') & (strPpm.charAt(strPpm.length() - 4) == '.'))){
                throw new UnsupportedFileFormatException();
            }
            
            Scanner readerFile = new Scanner(file);
            readerFile.next();//traverse first object(P3)

            while(readerFile.hasNext()){
                times++;
                if(first == 1){
                    if(times == 1){
                        width = Integer.parseInt(readerFile.next());
                    }
                    else if(times == 2){
                        height = Integer.parseInt(readerFile.next());
                    }
                    else if(times == 3){
                        colordepth = Integer.parseInt(readerFile.next());

                         array = new RGBPixel[height][width];
                                for(int k = 0; k < height; k++){//initialisation rgb array
                                    for(int j = 0; j < width; j++){
                                        array[k][j] = new RGBPixel();
                                    }
                                }

                        first = 0;
                        times = 0;
                    }
                }
                else{
                   if(times == 1){//times = 1 ->red colour
                        array[heightHelp][widthHelp].Red = (short) Integer.parseInt(readerFile.next());
                    }
                    else if(times == 2){//times = 2 ->green colour
                         array[heightHelp][widthHelp].Green = (short) Integer.parseInt(readerFile.next());
                    }
                    else if(times == 3){//times = 3 ->blue colour
                        array[heightHelp][widthHelp].Blue = (short) Integer.parseInt(readerFile.next());
                        times = 0;//initialisation of height/width for next loop
                         if((heightHelp == height-1) & (widthHelp == width-1)){
                            break;
                        }
                        else if(widthHelp == (width-1)){//reinitialise so that colours get in the right pixels
                            widthHelp = 0;
                            heightHelp++;
                        }
                        else{
                            widthHelp++;
                        }
                    } 

                }

            }
        }catch(FileNotFoundException e){
            
        }catch(UnsupportedFileFormatException ex){
            
        }
     
    }

    public PPMImage(RGBImage img){        
        this.height = img.height;
        this.width = img.width;
        this.colordepth = img.colordepth;
        this.array = new RGBPixel[height][width];
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                this.array[i][j]= img.array[i][j];
            }
        }
    }
    
    public PPMImage(){//dhmiourgia epipleon kataskeyasti gia arxikopoiiseis se alles klaseis
        
    }

    public PPMImage(YUVImage img){
        this.height = img.height;
        this.width = img.width;
        this.colordepth = 255;
        this.array = new RGBPixel[height][width];
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                this.array[i][j] = new RGBPixel(img.array[i][j]);
            }
        }
    
    }
    
    
    //initilisation of an image created from ppmimagestacker
    public PPMImage(RGBImage img, int number){
        PrintWriter pw = null;
        System.out.println("mpika mesa stin ppmimage");
        
        this.height = img.height;
        this.width = img.width;
        this.colordepth = img.colordepth;
        this.array = new RGBPixel[height][width];
     }
    
    @Override
    public String toString(){
        String str = "";
        StringBuilder strbuilderHelp = new StringBuilder(str);
        strbuilderHelp.insert(strbuilderHelp.length(), "P3");
        strbuilderHelp.insert(strbuilderHelp.length(), String.format(" %d %d %d", width, height, colordepth));
        
       for(int i = 0; i < height; i++){
           for(int j = 0; j < width; j++){
               strbuilderHelp.insert(strbuilderHelp.length(), String.format(" %d %d %d", array[i][j].Red, array[i][j].Green, array[i][j].Blue));
           }
       }  
       
       str = String.valueOf(strbuilderHelp);
       System.out.println(str);
            
        return(str);
    }
    
    public void toFile(java.io.File file){
        PrintWriter pw = null;
        
        try{
            this.f = file;
            
            if(file.exists()){//if the folder alredy existed -> empty
                PrintWriter print_writer = new PrintWriter(file);
                print_writer.print("");
                print_writer.close();
            }
            
            FileWriter writer = new FileWriter(file, true);
            pw = new PrintWriter(file);
            pw.println("P3" + "\n" + width + " " + height + " " + "255");
            for(int i = 0; i < height; i++){
                for(int j = 0; j <width; j++){
                    pw.println(array[i][j].Red + " " + array[i][j].Green + " " + array[i][j].Blue);
                }
        }
        }catch (IOException e) {
            System.out.println("An error occurred during reading");
        }finally {
            if (pw != null) {
               pw.close();
            }
        }
        
    }      
}


