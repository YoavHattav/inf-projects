package il.co.ilrd.chat_server;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client_one {
	public static void main(String[] args) {
		try {
			SocketChannel socketChannel = SocketChannel.open();
			socketChannel.connect(new InetSocketAddress("localhost", 80));
			socketChannel.configureBlocking(false);
			
			
			RequestLogin logIn = new RequestLogin(ChatOps.LOGIN, "yoavhattav@gmail.com", "yoav");
			ObjectOutputStream oos = new ObjectOutputStream(socketChannel.socket().getOutputStream());
			oos.writeObject(logIn);
			
			
			
			
			
			String logInData = "[][yoavhattav@gmail.com][yoav]";
			ByteBuffer buf = ByteBuffer.allocate(1024);
			buf.clear();
			buf.put(logInData.getBytes());
			buf.flip();
			while (buf.hasRemaining()) {
				socketChannel.write(buf);
			}
		} catch (IOException e) {
						e.printStackTrace();
		}
	}
}
