package il.co.ilrd.chat_server;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.ArrayList;

import javax.activation.CommandObject;
import javax.activation.DataHandler;

public class TCPCommunication implements Communication {
	
	private ChatServer server;
	
	public TCPCommunication(ChatServer server) {
		this.server = server;
	}


	@Override
	public ArrayList<String> parse(InputStream in) {
		return null;
	}
	
	class SocketPeer implements Peer {
		private Socket clientSocket = null;

		public SocketPeer(Socket clientSocket) {
			this.clientSocket = clientSocket;
		}

		@Override
		public void send(ArrayList<String> parsedMsg) {
			// TODO Auto-generated method stub
			
		}
	}
}
