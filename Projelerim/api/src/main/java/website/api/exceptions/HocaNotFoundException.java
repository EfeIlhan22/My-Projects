package website.api.exceptions;

public class HocaNotFoundException extends RuntimeException{
    private static final long serialVerisionUID = 1;

    public HocaNotFoundException(String message){
        super(message);
    }
    
}
