import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintStream;

public class PlayerReferee{

	private BufferedReader cin = null;
	private PrintStream cout = null;
	private PrintStream cerr = null;
	private int id = -1;

	public PlayerReferee(int id, InputStream inputStream, PrintStream outputStream, PrintStream errorStream){
		this.id = id;
		this.cout = outputStream;
		this.cerr = errorStream;
		this.cin = new BufferedReader(new InputStreamReader(inputStream));
	}

	public void PrintInput(String input){
		cout.println(input);
	}
	
	public void PrintErr(String error){
		cerr.println(error);
	}
	
	public String ReadOutput() throws IOException{
		return cin.readLine();
	}

	public int GetId(){
		return id;
	}

}
