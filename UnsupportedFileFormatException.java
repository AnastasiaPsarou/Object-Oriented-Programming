
package ce326.hw2;


class UnsupportedFileFormatException extends java.lang.Exception{
    static final long serialVersionUID = -4567891456L;
    
    public UnsupportedFileFormatException(){};
    
    public UnsupportedFileFormatException(String msg){
        super(msg);
    };

}
