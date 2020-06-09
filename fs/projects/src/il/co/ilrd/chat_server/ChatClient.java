package il.co.ilrd.chat_server;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

import il.co.ilrd.chat_msg.*;

public class ChatClient {
	Socket clientSocket = null;
	Set<String> groupNames = new HashSet<>();
	int clientId = 0;
	
	
	public ChatClient() {
		try {
			this.clientSocket = new Socket("10.1.0.21", 55554);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void responseCatcherThread() {
		new Thread(() -> {
			while (true) {
				try {
					ObjectInputStream ois = new ObjectInputStream(new DataInputStream(clientSocket.getInputStream()));
					Response response = (Response) ois.readObject();
					ResponseOps.valueOf(response.getOpId().toString()).handleResponse(this, response);
				} catch (ClassNotFoundException | IOException e) {
					System.out.println("cant connect");
					try {
						Thread.sleep(3000);
					} catch (InterruptedException e1) {
						e1.printStackTrace();
					}
					e.printStackTrace();
				}
			}}).start();
	}
	
	public void operationHandler() {
		Scanner myObj = new Scanner(System.in);
		
		System.out.println("you are loged in");
		while (true) {	
			System.out.println("Enter operation");
			String operation = myObj.nextLine();
			
			try {
				ByteArrayOutputStream bos = new ByteArrayOutputStream();
				OutputStream outToServer = null;
				outToServer = clientSocket.getOutputStream();
			
				ObjectOutputStream out = null;
			
				out = new ObjectOutputStream(bos);
				Request req = ClientOps.valueOf(operation).handleMsg(this, myObj);
				out.writeObject(req);
				out.flush();
				byte[] yourBytes = bos.toByteArray();
				outToServer.write(yourBytes);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void main(String[] args) throws IOException, ClassNotFoundException {
		ChatClient chatClient = new ChatClient();
		chatClient.responseCatcherThread();
		chatClient.operationHandler();
	}

	public enum ClientOps {
		LOGIN {
			@Override
			public Request handleMsg(ChatClient c, Scanner s) {
				System.out.println("Enter name");
				String userName = s.nextLine();
				System.out.println("Enter email");
				String userEmail = s.nextLine();
				return new RequestLogin(userEmail, userName);

			}
		},
		CREATE_GROUP {
		  	@Override
			public Request handleMsg(ChatClient c, Scanner s) {
				System.out.println("Enter group name");
				String groupName = s.nextLine();
				return new RequestCreateGroup(c.clientId, groupName);

			}
		},
		JOIN_GROUP {
			@Override
			public Request handleMsg(ChatClient c, Scanner s) {
				System.out.println("Enter group name");
				String groupName = s.nextLine();
				return new RequestJoinGroup(c.clientId, groupName);

			}
		},
		LEAVE_GROUP {
			@Override
			public Request handleMsg(ChatClient c, Scanner s) {
				System.out.println("Enter group name");
				String groupName = s.nextLine();
				return new RequestLeaveGroup(c.clientId, groupName);
			}
		},
		SEND_MSG {
			@Override
			public Request handleMsg(ChatClient c, Scanner s) {
				System.out.println("Enter group name");
				String groupName = s.nextLine();
				System.out.println("Enter msg");
				String msg = s.nextLine();
				return new RequestSend(c.clientId, groupName, msg);
			}
		};

		public abstract Request handleMsg(ChatClient c, Scanner s);
	}
	
	public enum ResponseOps {
		LOGIN {
			@Override
			public void handleResponse(ChatClient c, Response res) {
				ResponseLogin resp = (ResponseLogin) res;
				c.clientId = resp.getUserId();
				c.groupNames = resp.getGroups();

				System.out.println("welcom to chat hub!");
				System.out.println("your client id is: " + c.clientId);
				if (c.groupNames.size() == 0) {
					System.out.println("You can now join groups and start chatting");
				}
				else {
					System.out.println("you are member in " + c.groupNames.size() + " groups:");
					for (String group : c.groupNames) {
						System.out.println(group);
					}
				}
				System.out.println("Enter any operation...");
			}
		},

		CREATE_GROUP {
			@Override
			public void handleResponse(ChatClient c, Response res) {
				ResponseCreateGroup resp = (ResponseCreateGroup) res;
				String newGroup = resp.getGroupName();
				c.groupNames.add(newGroup);

				System.out.println("Welcome to group " + newGroup);
				System.out.println("Enter any operation...");
			}
		},
		JOIN_GROUP {
			@Override
			public void handleResponse(ChatClient c, Response res) {
				ResponseJoinGroup resp = (ResponseJoinGroup) res;
				int userId = resp.getUserId();
				String newGroup = resp.getGroupName();
				String sender = resp.getSenderName();

				if (userId == c.clientId) {
					c.groupNames.add(newGroup);
					System.out.println("Welcom to group " + newGroup);
				}
				else {
					System.out.println(sender + " has joined group " + newGroup);
					System.out.println("Say hello!");
				}
				System.out.println("Enter any operation...");
			}
		},
		LEAVE_GROUP {
			@Override
			public void handleResponse(ChatClient c, Response res) {
				ResponseLeaveGroup resp = (ResponseLeaveGroup) res;
				int userId = resp.getUserId();
				String group = resp.getGroupName();
				String sender = resp.getSenderName();

				if (userId == c.clientId) {
					c.groupNames.remove(group);
					System.out.println("You just left group " + group);
				}
				else {
					System.out.println(sender + " has left group " + group);
				}
				System.out.println("Enter any operation...");
			}
		},
		SEND_MSG {
			@Override
			public void handleResponse(ChatClient c, Response res) {
				ResponseSend resp = (ResponseSend) res;
				int userId = resp.getUserId();
				String group = resp.getGroupName();
				String sender = resp.getSenderName();
				String msg = resp.getMsg();
				//Color color = resp.getProp().getColor();
				
				if (userId != c.clientId) {
					System.out.println(sender + " in group " + group + " says:");
					System.out.println(msg);
				}
				System.out.println("Enter any operation...");
			}
		};

		public abstract void handleResponse(ChatClient c, Response res);
	}
}

