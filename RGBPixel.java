
package ce326.hw2;
import java.lang.*;


public class RGBPixel {
    private int value;//integer that contains 3 RGB colours
    short Red;
    short Green;
    short Blue;
    
    public RGBPixel(){
    }
    
    public RGBPixel(short red, short green, short blue){
        Red = red;
        Green = green;
        Blue = blue;
        value  = value | (red << 16);
        value  = value | (green << 8);
        value  = value | (blue);
    }
    
    public RGBPixel(RGBPixel pixel){
        Red = pixel.Red;
        Green = pixel.Green;
        Blue = pixel.Blue;
        value = pixel.value;
    }
    
    public RGBPixel(YUVPixel pixel){
        int redToBe;
        int greenToBe;
        int blueToBe;
        
        redToBe = ((298*(pixel.getY() - 16) + 409 * (pixel.getV() - 128) + 128) >> 8) ;
        greenToBe = ((298*(pixel.getY() - 16) - 100 * (pixel.getU() - 128) -208 * (pixel.getV() - 128) + 128) >> 8) ;
        blueToBe = ((298*(pixel.getY() - 16) + 516 * (pixel.getU() - 128) + 128) >> 8) ;
        
        if(redToBe < 0){
            setRed((short)0);
        }
        else if(redToBe > 255){
            setRed((short)255);
        }
        else{
            setRed((short)redToBe);
        }
        
        if(greenToBe < 0){
            setGreen((short) 0);
        }
        else if(greenToBe > 255){
            setGreen((short) 255);
        }
        else{
            setGreen((short) greenToBe);
        }
        
        if(blueToBe < 0){
            setBlue((short) 0);
        }
        else if(blueToBe > 255){
           setBlue((short) 255);
        }
        else{
            setBlue((short) blueToBe);
        }
    
    }
    
    short getRed(){
        return(Red);
    }
    
    short getGreen(){
        return(Green);
    }
    
    short getBlue(){
        return(Blue);
    }
    
    void setRed(short red){        
        Red = red;
        value = value & 0x0000ffff;
        
        value = (red << 16) | value;
    }
    
    void setGreen(short green){        
        
        Green = green;
        
        value = value & 0xffff00ff;
        
        value = value | (green << 8);        
    }
    
    void setBlue(short blue){
        Blue = blue;
        
        value = value & 0x00ffff00;
        
        value = blue | value;
       
    }
    
    int getRGB(){/
        return(value);
    }
    
    void setRGB(int value){
        
        setRed((short) ((value & 0x00ff0000) >> 16));
        setBlue((short) (value & 0x00000ff));
        setGreen((short) ((value & 0x0000ff00) >> 8));
      
    }
    
    final void setRGB(short red, short green, short blue){
        Red = red;
        Green = green;
        Blue = blue;
    }
    
    @Override
    public String toString(){
        String str = String.format(Short.toUnsignedInt(Red) + " " + Short.toUnsignedInt(Green) + " " + Short.toUnsignedInt(Blue));
        return(str);
    }
    
    

}
