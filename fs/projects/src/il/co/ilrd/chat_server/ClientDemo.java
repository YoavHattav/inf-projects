package il.co.ilrd.chat_server;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;

public class ClientDemo {

	private static void send(Msg req, Socket clientSocket) throws IOException {
		OutputStream ops = clientSocket.getOutputStream();
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		ObjectOutputStream oot = new ObjectOutputStream(bos);
		oot.writeObject(req);
		oot.flush();
		ops.write(bos.toByteArray());
	}
	
	private static Object receive(Socket clientSocket ) throws IOException, ClassNotFoundException {
		ObjectInputStream ois = new ObjectInputStream(new DataInputStream(clientSocket.getInputStream()));
		return ois.readObject();
	}
	
	public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {

		Socket clientSocket = new Socket("localhost", 55554);

		RequestLogin req = new RequestLogin("benja@g.c", "Benny");
		send((Msg)req,clientSocket);
		
		ResponseLogin rep = (ResponseLogin) receive(clientSocket);
		
		int userID = rep.getUserId();
		System.out.println("userID: " + rep.getUserId());
		System.out.println("msgId: " + rep.getMsgID());
		System.out.println("status: " + rep.getStatus());
		
		RequestCreateGroup create = new RequestCreateGroup(userID, "FS8081");
		
		System.out.println(create.getOpId());
		
		send((Msg)create, clientSocket);
		
		ResponseCreateGroup created = ((ResponseCreateGroup) receive(clientSocket));
		System.out.println(created.getUserId());
		System.out.println(created.getGroupName());
		System.out.println(created.getMsgID());
		System.out.println(created.getStatus());
		
		for(int i = 0; i < 5; ++i)
		{
			send((Msg)new RequestSend(userID, "FS8081", "Helloooo"), clientSocket);
			System.out.println(((ResponseSend) receive(clientSocket)).getMsg());
		}
		Thread.sleep(50000);
		
		
	}

}
