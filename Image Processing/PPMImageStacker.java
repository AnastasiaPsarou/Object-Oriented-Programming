
package ce326.hw2;
import java.io.FileNotFoundException;
import java.util.*;
import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;

public class PPMImageStacker{
    PPMImage finalImage;
    ArrayList<File> listfiles;
    
    public PPMImageStacker(java.io.File dir) throws FileNotFoundException{ 
        listfiles = new ArrayList<File>();
        
        try{
            String strNotExists = String.format("[ERROR] Directory %s does not exist!", dir.getName());
            String strNotDir = String.format("[ERROR] %s is not a directory!", dir.getName());
            
            if(!dir.exists()){//if directory does not exist
                throw new FileNotFoundException(strNotExists);
            }
            if(!dir.isDirectory()){//if there is a file with the same name but not a directory
                throw new FileNotFoundException(strNotDir);
            }
            
            //list in which every node is a file of the directory
            for(int i = 0; i < dir.listFiles().length; i++){
                listfiles.add(dir.listFiles()[i]);
            }
            
        }
        catch(FileNotFoundException e){
        }
    }
 
    public void stack() throws UnsupportedFileFormatException { 
        
        try{
            int numberOfFiles = listfiles.size();
            Iterator<File> i = listfiles.iterator();
            PPMImage image;

            File f = i.next();//first dir image
            image = new PPMImage(f);
            finalImage = new PPMImage();
            finalImage.height = image.height;
            finalImage.width = image.width;
            finalImage.colordepth = image.colordepth;
            finalImage.array = new RGBPixel[image.height][image.width];
            finalImage.array = image.array;


            while(i.hasNext()){
                f = i.next();//next dir image

                image = new PPMImage(f);

                for(int j = 0; j < finalImage.height; j++){
                    for(int k = 0; k < finalImage.width; k++){
                        finalImage.array[j][k].Red += image.array[j][k].Red;
                        finalImage.array[j][k].Green += image.array[j][k].Green;
                        finalImage.array[j][k].Blue += image.array[j][k].Blue;
                    }
                }

            }

            for(int j = 0; j < finalImage.height; j++){
                for(int k = 0; k < finalImage.width; k++){
                    finalImage.array[j][k].Red /= (short) numberOfFiles ;
                   finalImage.array[j][k].Green /= (short) numberOfFiles ;
                    finalImage.array[j][k].Blue /= (short) numberOfFiles ;
                }
            }
        }
        catch(IOException e){
            
        }

    }
    
    public PPMImage getStackedImage(){
        return(finalImage);
    }
    
}
