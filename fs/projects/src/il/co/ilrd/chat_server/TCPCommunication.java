package il.co.ilrd.chat_server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;
import java.util.StringTokenizer;

public class TCPCommunication implements Communication {
	
	private ChatServer server;
	private SocketChannel client = null;
	
	public TCPCommunication(ChatServer server) {
		this.server = server;
		new Thread(()-> Init()).start();
	}
	
	@Override
	public void Init() {
		try {
			Selector selector = Selector.open();
			ServerSocketChannel socket = ServerSocketChannel.open();
			ServerSocket serverSocket = socket.socket();
			serverSocket.bind(new InetSocketAddress("localhost", 8089));
			 socket.configureBlocking(false);
			 socket.register(selector, SelectionKey.OP_ACCEPT);
			 while (true) {
				 selector.select();
				 Set<SelectionKey> selectedKeys = selector.selectedKeys();
				 Iterator<SelectionKey> readyChannelIterator = selectedKeys.iterator();
		
				 while (readyChannelIterator.hasNext()) {
					 SelectionKey key = readyChannelIterator.next();
		          
					 if (key.isAcceptable()) {
					        client = socket.accept();
					        client.configureBlocking(false);
					        client.register(selector, SelectionKey.OP_READ);			       
					 }
					 
					 else if (key.isReadable()) {
						 client = (SocketChannel) key.channel();
						 ByteBuffer buffer = ByteBuffer.allocate(1024);
					     client.read(buffer);
					     buffer.flip();
					     String recievedMsg = new String(buffer.array()).trim();
					     StringTokenizer st = new StringTokenizer(recievedMsg, "[]");
					     Function.valueOf(st.nextToken()).activateServerFunction(this, st, new SocketPeer(client));
					     buffer.clear();
				     }
					 readyChannelIterator.remove();
				 }
			 }
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	private enum Function {
		LOGIN        (1){
			@Override
			void activateServerFunction(TCPCommunication communication, StringTokenizer st, Peer peer) {
				communication.server.logIn(st.nextToken(), st.nextToken(), peer);}},
		ADD_TO_GROUP (2) {
			@Override
			void activateServerFunction(TCPCommunication communication, StringTokenizer st, Peer peer) {
				communication.server.joinGroup(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));}},
		SEND         (3) {
				@Override
				void activateServerFunction(TCPCommunication communication, StringTokenizer st, Peer peer) {
					communication.server.sendMsg(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), st.nextToken());}},
		CREATE_GROUP (4) {
					@Override
					void activateServerFunction(TCPCommunication communication, StringTokenizer st, Peer peer) {
						communication.server.createNewGroup(Integer.parseInt(st.nextToken()), st.nextToken());}},
		LEAVE_GROUP  (5) {
						@Override
						void activateServerFunction(TCPCommunication communication, StringTokenizer st, Peer peer) {
							communication.server.leaveGroup(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));}};
		
		private int functionNum;
		private Function(int functionNum) {
			this.functionNum = functionNum;		
		}

		abstract void activateServerFunction(TCPCommunication communication, StringTokenizer st, Peer peer);
	}
	
	private class SocketPeer implements Peer {

		private SocketChannel clientSocket = null;

		public SocketPeer(SocketChannel clientSocket) {
			this.clientSocket = clientSocket;
		}
		
		@Override
		public void sendMessage(String senderName, int groupID, UsrProperties prop, String message) {
		}

		@Override
		public void sendAddToGRoup(int status) {}

		@Override
		public void sendNewGroupMember(int newUsrID) {}
		
		@Override
		public void sendLogin(int userID, int... groupID) {}
		
		@Override
		public void sendCreateGroup(int groupID, int groupName) {}
		
		@Override
		public void sendLeaveGroup(int status) {}

	}
}