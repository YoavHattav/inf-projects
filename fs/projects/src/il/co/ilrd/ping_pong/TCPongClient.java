package il.co.ilrd.ping_pong;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class TCPongClient {
	Socket socket = null;
	DataInputStream in = null;
	DataOutputStream out = null;
	
	public TCPongClient(String address, int port) {
		try {
			socket = new Socket(address, port);
			in = new DataInputStream(socket.getInputStream());
			out = new DataOutputStream(socket.getOutputStream());
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		TCPongClient client = new TCPongClient("localhost", 4449);
		String str = "4ping";
		while (true) {
			//send
			try {
				client.out.writeBytes(str);
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			//reciving
			try {
				int loop = client.in.read() - 48;
				for (int i = 0; i < loop; ++i) {
					System.out.print((char)(client.in.read()));
				}
				System.out.println("");
				
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}
