package il.co.ilrd.chat_server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client_one {
	public static void main(String[] args) {
		try {
			SocketChannel socketChannel = SocketChannel.open();
			socketChannel.connect(new InetSocketAddress("localhost", 80));
			socketChannel.configureBlocking(false);
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
