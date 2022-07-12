
package ce326.hw2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import static java.lang.Character.isWhitespace;
import java.util.Scanner;
import ce326.hw2.YUVPixel;

public class YUVImage {
    YUVPixel[][] array;
    int width;
    int height;
    
    
    public YUVImage(int width, int height){
        this.width = width;
        this.height = height;
        
        array = new YUVPixel[height][width];
        
        for(int i= 0; i < height; i++){
            for(int j = 0; j < width; j++){
                array[i][j] = new YUVPixel((short)16, (short)128, (short)128);
            }
        }
    }
    
    public YUVImage(YUVImage copyImg){
        this.width = copyImg.width;
        this.height = copyImg.height;
        
        array = new YUVPixel[height][width];
        
        for(int i= 0; i < height; i++){
            for(int j = 0; j < width; j++){
                array[i][j] = new YUVPixel(copyImg.array[i][j].getY(), copyImg.array[i][j].getU(), copyImg.array[i][j].getV());
            }
        }
    }
    
    public YUVImage(RGBImage RGBImg){
        this.width = RGBImg.width;
        this.height = RGBImg.height;
        
        array = new YUVPixel[height][width];
        
        for(int i= 0; i < height; i++){
            for(int j = 0; j < width; j++){
                array[i][j] = new YUVPixel(RGBImg.array[i][j]);
            }
        }
    }
    
    public YUVImage(java.io.File file){
        int times = 0;//mas leei se poia metavliti anaferetai h kathe timi pou yparxei sto arxeio
        int first = 1;//distinguish height, width, colordepth from red, blue, green
        int heightHelp = 0;
        int widthHelp = 0;
        String strPpm;
        
        try{
            strPpm = file.getName();
            if(!((strPpm.charAt(strPpm.length() - 1) == 'v') & (strPpm.charAt(strPpm.length() - 2) == 'u') & (strPpm.charAt(strPpm.length() - 3) == 'y') & (strPpm.charAt(strPpm.length() - 4) == '.'))){
                throw new UnsupportedFileFormatException();
            }
            
            Scanner readerFile = new Scanner(file);
            readerFile.next();
            
            while(readerFile.hasNext()){
                String nextString = readerFile.next();
                times++;
                if(first == 1){
                    if(times == 1){
                        width = Integer.parseInt(nextString);
                    }
                    else if(times == 2){
                        height = Integer.parseInt(nextString);

                        array = new YUVPixel[height][width];
                        for(int k = 0; k < height; k++){//initialisation rgb array
                            for(int j = 0; j < width; j++){
                                array[k][j] = new YUVPixel();
                            }
                        }

                        first = 0;
                        times = 0;
                    }
                }
                else{
                    if(times == 1){
                        array[heightHelp][widthHelp].setY(Short.valueOf(nextString));
                    }
                    else if(times == 2){
                        array[heightHelp][widthHelp].setU(Short.valueOf(nextString));
                    }
                    else if(times == 3){
                        array[heightHelp][widthHelp].setV(Short.valueOf(nextString));
                        times = 0;
                        if((heightHelp == height-1) & (widthHelp == width-1)){
                            break;
                        }
                        else if(widthHelp == (width-1)){//reinitialisation
                            widthHelp = 0;
                            heightHelp++;
                        }
                        else{
                            widthHelp++;
                        }
                    } 

                }
                

            }
            readerFile.close();
            
        }
        catch(FileNotFoundException e){}
        catch(UnsupportedFileFormatException ex){} 
    }
    
    @Override
    public String toString(){
        String str = "";
        StringBuilder strbuilderHelp = new StringBuilder(str);
        strbuilderHelp.insert(strbuilderHelp.length(), "YUV3");
        strbuilderHelp.insert(strbuilderHelp.length(), String.format(" %d %d", width, height));
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                strbuilderHelp.insert(strbuilderHelp.length(), String.format(" %d %d %d", array[i][j].getY(), array[i][j].getU(), array[i][j].getV()));
            }
        }  
       
        str = String.valueOf(strbuilderHelp);
        System.out.println(str);

        return(str);
    }
    
    
    public void toFile(java.io.File file) {
        PrintWriter pw = null;
        
        try{
            
            if(file.exists()){//if file already exists -> empty
                PrintWriter print_writer = new PrintWriter(file);
                print_writer.print("");
                print_writer.close();
            }
            
            FileWriter writer = new FileWriter(file, true);
            pw = new PrintWriter(file);
            pw.println("YUV3" + "\n" + width + " " + height);
            for(int i = 0; i < height; i++){
                for(int j = 0; j <width; j++){
                    pw.println(array[i][j].getY() + " " + array[i][j].getU() + " " + array[i][j].getV());
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
    
    public void equalize(){
        Histogram histogram = new Histogram(this);
        histogram.equalize();
        short value;
        
        //copy in a yuv array the balanced one
        for(int i = 0; i < this.height; i++){
            for(int j = 0; j < this.width; j++){
                value = this.array[i][j].getY();
                this.array[i][j].setY((short) histogram.balancedHistogramArray[value]);
            }
        }
    }
    
    
    
}
