package il.co.ilrd.chat_server;

import java.util.ArrayList;

public interface Peer {
	public void send(ArrayList<String> parsedMsg);
}
