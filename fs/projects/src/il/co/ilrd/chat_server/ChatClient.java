package il.co.ilrd.chat_server;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.channels.SocketChannel;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

import il.co.ilrd.chat_server.TCPCommunication.SocketPeer;


public class ChatClient {
	Socket clientSocket = null;
	Set<String> groupNames = new HashSet<>();
	int clientId = 0;
	
	
	public ChatClient() {
		try {
			this.clientSocket = new Socket("localhost", 55554);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	// i need to find a way to catch the different responses and deal with the info.
	public void responseThread() {
		new Thread(() -> {ObjectInputStream ois = null;
		try {
			ois = new ObjectInputStream(new DataInputStream(clientSocket.getInputStream()));
		} catch (IOException e) {
			e.printStackTrace();
		}
		Response res = null;
		try {
			res = (Response) ois.readObject();
			ResponseOps.valueOf(res.getOpId().toString());
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}
		System.out.println(res.getMsgID());
		System.out.println(res.getStatus());
		System.out.println(res.getOpId());}).start();
	}
	
	public void other() {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		OutputStream outToServer = null;
		try {
			outToServer = clientSocket.getOutputStream();
		} catch (IOException e) {
			e.printStackTrace();
		}
		ObjectOutputStream out = null;

		Scanner myObj = new Scanner(System.in); 
		System.out.println("Enter operation");
		String operation = myObj.nextLine(); 

		try {
			out = new ObjectOutputStream(bos);
			Request req = ClientOps.valueOf(operation).handleMsg(myObj);
			out.writeObject(req);
			out.flush();
			byte[] yourBytes = bos.toByteArray();
			outToServer.write(yourBytes);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args) throws IOException, ClassNotFoundException {
		ChatClient chatClient = new ChatClient();
		chatClient.responseThread();
		chatClient.other();
	}

	public enum ClientOps {
		LOGIN {
			@Override
			public Request handleMsg(Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestLogin(userEmail, userName);

			}
		},
		CREATE_GROUP {
		  	@Override
			public Request handleMsg(Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestCreateGroup(userId, groupName);

			}
		},
		JOIN_GROUP {
			@Override
			public Request handleMsg(Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestJoinGroup(userId, groupName);

			}
		},
		LEAVE_GROUP {
			@Override
			public Request handleMsg(Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestLeaveGroup(userId, groupName);

			}
		},
		SEND_MSG {
			@Override
			public Request handleMsg(Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestSend(userId, groupName, msg);

			}
		};

		/*LOGOUT {
			@Override
			public Request handleMsg(Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestLogin(userEmail, userName);

			}
		};*/

		public abstract Request handleMsg(Scanner s);
	}
	
	public enum ResponseOps {
		LOGIN {
			@Override
			public void handleResponse(Response response) {
				// TODO Auto-generated method stub
				
			}
		},
		CREATE_GROUP {
			@Override
			public void handleResponse(Response response) {
				// TODO Auto-generated method stub
				
			}
		},
		JOIN_GROUP {
			@Override
			public void handleResponse(Response response) {
				// TODO Auto-generated method stub
				
			}
		},
		LEAVE_GROUP {
			@Override
			public void handleResponse(Response response) {
				// TODO Auto-generated method stub
				
			}
		},
		SEND_MSG {
			@Override
			public void handleResponse(Response response) {
				// TODO Auto-generated method stub
				
			}
		};

		public abstract void handleResponse(Response response);
	}
}
