package il.co.ilrd.chat_server;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

public class TCPCommunication implements Communication {
	private volatile boolean runFlag = true;
	private Selector selector;
	ChatServer server;
	int portNum;
	private ServerSocketChannel serverChannel;
	private ServerSocket serverSocket;
	private SocketChannel channel;
		
	public TCPCommunication(ChatServer server,int portNum) {
		this.server = server;
		this.portNum = portNum;
		Init();
	}
	
	@Override
	public void Init() {
		try {
			selector = Selector.open();
			serverChannel = ServerSocketChannel.open();
			serverSocket = serverChannel.socket();
			serverSocket.bind(new InetSocketAddress("localhost", portNum));
			serverChannel.configureBlocking(false);
			serverChannel.register(selector, SelectionKey.OP_ACCEPT);
		} catch (IOException e) {
			System.err.println(e.getMessage());
			e.printStackTrace();
		}
		try {
			while(true) {

				selector.select();
				Iterator<SelectionKey> keyIterator = selector.selectedKeys().iterator();

				while(keyIterator.hasNext()) {
					SelectionKey currentKey = keyIterator.next();
					if (currentKey.isAcceptable()) {
						System.out.println("accepted");
						ServerSocketChannel server = (ServerSocketChannel) currentKey.channel();
						SocketChannel client = server.accept();
						client.configureBlocking(false);
						client.register(selector, SelectionKey.OP_READ, ByteBuffer.allocate(2000));
					}
					else if(currentKey.isReadable()) {
						System.out.println("reading");
						channel = (SocketChannel) currentKey.channel();
						ByteBuffer buffer = (ByteBuffer)currentKey.attachment();
						Request request = null;
						channel.read(buffer);
						ByteArrayInputStream bis = new ByteArrayInputStream(buffer.array());
			            ObjectInputStream ois = new ObjectInputStream(bis);
						request = (Request)ois.readObject();
						ChatOps.valueOf(request.getOpId().toString()).handleMsg(request, channel, this);
					}
					keyIterator.remove(); 
				}
			}
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		} 
	}
	
	class SocketPeer implements Peer {
		private SocketChannel clientSocket;

		public SocketPeer(SocketChannel clientSocket) {
			this.clientSocket = clientSocket;
		}

		@Override
		public void responseLogin(int msgID, int userID, Set<String> groupNames, Status status) {
			ResponseLogin response = new ResponseLogin(msgID, userID, groupNames, status);

			try (OutputStream ops = clientSocket.socket().getOutputStream();
					ByteArrayOutputStream baos = new ByteArrayOutputStream();
					ObjectOutputStream oos = new ObjectOutputStream(baos)) {
				baos.writeTo(ops);
				oos.writeObject(response);
			} catch (IOException e) {
				e.printStackTrace();
			}

		}

		@Override
		public void responseCreateGroup(int msgID, String groupName, Status status) {
			ResponseCreateGroup response = new ResponseCreateGroup(msgID, groupName, status);

			try (OutputStream ops = clientSocket.socket().getOutputStream();
					ByteArrayOutputStream baos = new ByteArrayOutputStream();
					ObjectOutputStream oos = new ObjectOutputStream(baos)) {
				baos.writeTo(ops);
				oos.writeObject(response);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void responseJoinGroup(int msgID, int userID, String userName, String groupName, Status status) {
			ResponseJoinGroup response = new ResponseJoinGroup(msgID, userID, userName, groupName, status);

			try (OutputStream ops = clientSocket.socket().getOutputStream();
					ByteArrayOutputStream baos = new ByteArrayOutputStream();
					ObjectOutputStream oos = new ObjectOutputStream(baos)) {
				baos.writeTo(ops);
				oos.writeObject(response);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void responseLeaveGroup(int msgID, int userID, String userName, String groupName, Status status) {
			ResponseLeaveGroup response = new ResponseLeaveGroup(msgID, userID, userName, groupName, status);

			try (OutputStream ops = clientSocket.socket().getOutputStream();
					ByteArrayOutputStream baos = new ByteArrayOutputStream();
					ObjectOutputStream oos = new ObjectOutputStream(baos)) {
				baos.writeTo(ops);
				oos.writeObject(response);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void responseMessage(int msgID, int userID, String userName, String groupName, UsrProperties prop,
				String message, Status status) {
			ResponseSend response = new ResponseSend(msgID, userID, userName, groupName, message, prop, status);

			try (OutputStream ops = clientSocket.socket().getOutputStream();
					ByteArrayOutputStream baos = new ByteArrayOutputStream();
					ObjectOutputStream oos = new ObjectOutputStream(baos)) {
				baos.writeTo(ops);
				oos.writeObject(response);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void main(String [] args) {
		ChatServer server = new ChatServerHub();
		new TCPCommunication(server, 55554);
	}
}
