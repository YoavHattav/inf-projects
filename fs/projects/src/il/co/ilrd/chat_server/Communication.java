package il.co.ilrd.chat_server;

import java.io.InputStream;
import java.util.ArrayList;

public interface Communication {
	/**
	 * takes the stream and parses it to the right data.
	 * @return Integer that tells the server which method it should execute. 
	 */
	public ArrayList<String> parse(InputStream in);
	
	
}
