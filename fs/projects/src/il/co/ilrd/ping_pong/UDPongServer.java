package il.co.ilrd.ping_pong;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UDPongServer {
	
	public static void main(String[] args) {
		int server_port = 4445;
		byte[] recieveBuf = new byte[5];
		
		
		DatagramSocket socket = null;
		
		try {
			socket = new DatagramSocket(server_port);
		} catch (SocketException e1) {
			e1.printStackTrace();
		}
		DatagramPacket packet;
		
		long timer = System.currentTimeMillis();
		packet = new DatagramPacket(recieveBuf, recieveBuf.length);
		
		while (true) {
			//reciving
			try {
				socket.receive(packet);
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			String input = new String(packet.getData(), 0, packet.getLength());
			System.out.println(input);
			
			//sending
			byte[] buffer = {'p','o','n','g'};
			packet = new DatagramPacket(buffer, buffer.length, packet.getAddress(), packet.getPort());
			try {
				socket.send(packet);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
