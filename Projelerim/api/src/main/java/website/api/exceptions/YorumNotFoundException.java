package website.api.exceptions;

public class YorumNotFoundException extends RuntimeException{
    private static final long serialVerisionUID = 2;

    public YorumNotFoundException(String message){
        super(message);
    }
}
