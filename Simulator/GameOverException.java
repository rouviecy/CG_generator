import java.io.IOException;

public class GameOverException extends Exception {
	public GameOverException() { super(); }
	public GameOverException(String message) { super("Game over\n" + message); }
}
