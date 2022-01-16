package ce326.hw2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Histogram {
    double[] histogramArray;//array with the histogram of the given array
    int[] balancedHistogramArray;
    int totalElements;//number of cells of the array array
    YUVImage img;
    String histogram;
    double[] arrayPossibilities;
    double[] CDFArray;
    
    
    public Histogram(YUVImage img){
        this.img = img;
        histogramArray = new double[236];
        CDFArray = new double[236];
        totalElements = img.height * img.width;
        
        for(int i = 0; i < 236; i++){//array initialisation
            histogramArray[i] = 0;
            CDFArray[i] = 0;
        }
        
        //in histogramArray[0] gets the number of cells of img.array with brightness 0 etc
        for(int i = 0; i < img.height; i++){
            for(int j = 0; j <img.width; j++){
                histogramArray[img.array[i][j].getY()] ++;
            }
        }
 
    }
 
    public String toString(){
        String histogram = "";
        StringBuilder strBuilder = new StringBuilder("");
        String foteinotita;
        
        for(int i = 0; i < histogramArray.length; i++){
            foteinotita = String.format("%3d", i);
            histogram += "\n";
            histogram += foteinotita;
            histogram += ".(";
            foteinotita = String.format("%4d", (int)histogramArray[i]);
            histogram += foteinotita;
            histogram += ")\t";            
            for(int j = 1; j <  histogramArray[i]/1000; j++){
                histogram += '#';
            }
            for(int j = 1; j <  histogramArray[i]/100; j++){
                histogram += '$';
            }
            for(int j = 1; j <  histogramArray[i]/10; j++){
                histogram += '@';
            }
            for(int j = 0; j <  histogramArray[i]; j++){
                histogram += '*';
            }            
        }
        
        histogram += '\n';
        
        return(histogram);
        
    }
    
    public void equalize(){
        double[] arrayPossibilities = new double[236];
        balancedHistogramArray = new int[236];
        
        arrayPossibilities[0] = histogramArray[0] / totalElements;
        CDFArray[0] = histogramArray[0];
        
        for(int i = 1; i < 236; i++){
            arrayPossibilities[i] = histogramArray[i] / totalElements;//possibility array
            CDFArray[i] = arrayPossibilities[i] + CDFArray[i-1];//value of last cell + doubleArray[i]
        }
       
        for(int i = 0; i < 236; i++){//balanced histogram
            balancedHistogramArray[i] = (int) ( 235 * CDFArray[i]);
        }
        
    }
    
    public short getEqualizedLuminocity(int luminocity){
        
        return((short) balancedHistogramArray[luminocity]);
        
    }
    
    public void toFile(File file){
        try{
            BufferedWriter bw = new BufferedWriter(new FileWriter(file));
            bw.write(toString());
            bw.close();
        }
        catch(IOException e){
        }
        
    }
    
    
}
