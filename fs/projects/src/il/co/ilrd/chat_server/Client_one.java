package il.co.ilrd.chat_server;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.channels.SocketChannel;

public class Client_one {
	public static void main(String[] args) {
		try (SocketChannel socketChannel = SocketChannel.open();
			OutputStream ops = socketChannel.socket().getOutputStream();
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			ObjectOutputStream oos = new ObjectOutputStream(baos);)  {
			
			socketChannel.connect(new InetSocketAddress("localhost", 80));
			socketChannel.configureBlocking(false);
			RequestLogin logIn = new RequestLogin("yoavhattav@gmail.com", "yoav");
			baos.writeTo(ops);
			oos.writeObject(logIn);
			try {
				Thread.sleep(3000);
			} catch (InterruptedException e) {
				
				e.printStackTrace();
			}finally {
				//RequestLogOut and close socket and tell the selector not to listen on the channel.
			}
		} catch (IOException e) {
						e.printStackTrace();
		}
	}
}
