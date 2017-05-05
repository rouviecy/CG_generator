import java.io.IOException;

public class LostException extends Exception {
	public LostException() { super(); }
	public LostException(String message, int number) { super(message); }
}
