
package ce326.hw2;


public class YUVPixel {
    private short Y;
    private short U;
    private short V;
    
    public YUVPixel(short Y, short U, short V){
        this.Y = Y;
        this.U = U;
        this.V = V;
    }
    
    public YUVPixel(YUVPixel pixel){
        this.Y = pixel.Y;
        this.U = pixel.U;
        this.V = pixel.V;
    }
    
    public YUVPixel(RGBPixel pixel){
        this.Y = (short) (((66 * pixel.Red + 129 * pixel.Green +  25 * pixel.Blue + 128) >> 8) + 16);
        this.U = (short) ((( -38 * pixel.Red -  74 * pixel.Green + 112 * pixel.Blue + 128) >> 8) + 128);
        this.V = (short) ((( 112 * pixel.Red -  94 * pixel.Green -  18 * pixel.Blue + 128) >> 8) + 128);
    }
    
    public YUVPixel(){
        
    }
    
     public short getY(){
         return(Y);
     }
     
     public short getU(){
         return(U);
     }
     
     public short getV(){
         return(V);
     }
      
     void setY(short Y){
         this.Y = Y;
     }
     
     void setU(short U){
         this.U = U;
     }
     
     void setV(short V){
         this.V = V;
     }
}
