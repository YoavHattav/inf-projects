package il.co.ilrd.chat_server;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

import il.co.ilrd.chat_msg.*;

public class TCPCommunication implements Communication {
	//private volatile boolean runFlag = true;
	private Selector selector;
	ChatServer server;
	int portNum;
	private ServerSocketChannel serverChannel;
	private ServerSocket serverSocket;
	private SocketChannel channel;
	
	public TCPCommunication(ChatServer server, int portNum) {
		this.server = server;
		this.portNum = portNum;
		try {
			selector = Selector.open();
			serverChannel = ServerSocketChannel.open();
			serverSocket =  serverChannel.socket();
			serverSocket.bind(new InetSocketAddress("10.1.0.21", portNum));
			serverChannel.configureBlocking(false);
			serverChannel.register(selector, SelectionKey.OP_ACCEPT);
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		Init();
	}
		
	@Override
	public void Init() {
			while(true) {
				try {
					selector.select();
				} catch (IOException e) {
					e.printStackTrace();
				}
				Iterator<SelectionKey> keyIterator = selector.selectedKeys().iterator();

				while(keyIterator.hasNext()) {
					
						SelectionKey currentKey = keyIterator.next();
						if (currentKey.isAcceptable()) {
							System.out.println("accepting");
							ServerSocketChannel server = (ServerSocketChannel) currentKey.channel();
							SocketChannel client;
							try {
								client = server.accept();
							
							client.configureBlocking(false);
							client.register(selector, SelectionKey.OP_READ);
							}catch (IOException e) {
								e.printStackTrace();
							}
						}
						else if(currentKey.isReadable()) {
							System.out.println("reading");
							channel = (SocketChannel) currentKey.channel();
							ByteBuffer buffer =  ByteBuffer.allocate(1024);
							Request request = null;
							try {
								channel.read(buffer);
								//buffer.flip();
								ByteArrayInputStream bis = new ByteArrayInputStream(buffer.array());
					            ObjectInputStream ois = new ObjectInputStream(bis);
					            Object requestObj = ois.readObject();
					            if (requestObj instanceof Request) {
					            	request = (Request)requestObj;
					            	request.getOpId().handleMsg(request, channel, this);	
					            }
							}catch (IOException e) {
								currentKey.cancel();
								keyIterator.remove();
								continue;
							}catch (ClassNotFoundException e) {
								e.printStackTrace();
							}
						}
						keyIterator.remove();
				}
			}
	}
	
	class SocketPeer implements Peer {
		private SocketChannel clientSocket;

		public SocketPeer(SocketChannel clientSocket) {
			this.clientSocket = clientSocket;
		}

		@Override
		public void responseLogin(int msgID, int userID, Set<String> groupNames, Status status) {
			send(new ResponseLogin(msgID, userID, groupNames, status));
		}
		@Override
		public void responseCreateGroup(int msgID, String groupName, Status status) {
			send(new ResponseCreateGroup(msgID, groupName, status));
		}
		@Override
		public void responseJoinGroup(int msgID, int userID, String userName, String groupName, Status status) {
			send(new ResponseJoinGroup(msgID, userID, userName, groupName, status));
		}
		@Override
		public void responseLeaveGroup(int msgID, int userID, String userName, String groupName, Status status) {
			send(new ResponseLeaveGroup(msgID, userID, userName, groupName, status));
		}
		@Override
		public void responseMessage(int msgID, int userID, String userName, String groupName, UsrProperties prop,
				String message, Status status) {
			send(new ResponseSend(msgID, userID, groupName, message, userName, prop, status));
		}
		private void send(Response reply) {
			if (clientSocket == null) { return; }
			ByteArrayOutputStream bos = new ByteArrayOutputStream();
			ObjectOutputStream out;
			try {
				out = new ObjectOutputStream(bos);
				out.writeObject(reply);
				out.flush();
				ByteBuffer bb = ByteBuffer.wrap(bos.toByteArray());
				clientSocket.write(bb);
			} catch (IOException e) {
				try {
					clientSocket.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}finally {
					clientSocket = null;
				}
			}
		}
	}
	
	public static void main(String [] args) {
		ChatServer server = new ChatServerHub();
		new TCPCommunication(server, 55554);
	}
}

