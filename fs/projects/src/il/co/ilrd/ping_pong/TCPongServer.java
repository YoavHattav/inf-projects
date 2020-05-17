package il.co.ilrd.ping_pong;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class TCPongServer {
	Socket socket = null;
	ServerSocket server = null;
	DataInputStream in = null;
	DataOutputStream out = null;
	
	public TCPongServer(String address, int port) {
		try {
			server = new ServerSocket(port);
			socket = server.accept();
			
			in = new DataInputStream(socket.getInputStream());
			out = new DataOutputStream(socket.getOutputStream());
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		TCPongServer server = new TCPongServer("localhost", 4449);
		String str = "4pong";
		while (true) {
			
			//reciving
			try {
				int loop = server.in.read() - 48;
				for (int i = 0; i < loop; ++i) {
					System.out.print((char)(server.in.read()));
				}
				System.out.println("");
			} catch (IOException e) {
				e.printStackTrace();
			}
			//send
			try {
				server.out.writeBytes(str);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
