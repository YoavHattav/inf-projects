package il.co.ilrd.ping_pong;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UDPongClient {
	
	public static void main(String[] args) {
		int port;
		InetAddress address = null;
		byte[] recieveBuf = new byte[5];
		
		try {
			address = InetAddress.getByName("localhost");
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}
		DatagramSocket socket = null;
		
		try {
			socket = new DatagramSocket();
		} catch (SocketException e1) {
			e1.printStackTrace();
		}
		DatagramPacket packet;
		
		long timer = System.currentTimeMillis();

		while (true) {
			//sending
			byte[] buffer = {'p','i','n','g'};
			packet = new DatagramPacket(buffer, buffer.length, address, 4445);
			try {
				socket.send(packet);
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			//reciving
			packet = new DatagramPacket(recieveBuf, recieveBuf.length);
			try {
				socket.receive(packet);
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			String input = new String(packet.getData(), 0, packet.getLength());
			System.out.println(input);
		}
	}
}
