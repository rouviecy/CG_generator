import java.io.IOException;

public class InvalidInputException extends Exception {
	public InvalidInputException() { super(); }
	public InvalidInputException(String message, String line) { super("Input invalide :\n" + line + "\n" + message); }
}
