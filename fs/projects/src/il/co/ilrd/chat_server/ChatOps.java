package il.co.ilrd.chat_server;

import java.nio.channels.SocketChannel;

import il.co.ilrd.chat_msg.*;

public enum ChatOps {
	LOGIN {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestLogin loginRequest = (RequestLogin)msg;
			commun.server.logIn(loginRequest.getMsgID(), loginRequest.getEmail(), (loginRequest).getUserName(), commun.new SocketPeer(clientSocket));
		}
	},
	CREATE_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestCreateGroup newGroupRequest = (RequestCreateGroup)msg;
			commun.server.createNewGroup(newGroupRequest.getMsgID(), newGroupRequest.getUserId(), newGroupRequest.getGroupName());
		}
	},
	JOIN_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestJoinGroup joinRequest = (RequestJoinGroup)msg;
			commun.server.joinGroup(joinRequest.getMsgID(), joinRequest.getUserId(), joinRequest.getGroupName());
		}
	},
	LEAVE_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestLeaveGroup leaveRequest = (RequestLeaveGroup)msg;
			commun.server.leaveGroup(leaveRequest.getMsgID(), leaveRequest.getUserId(), leaveRequest.getGroupName());
		}
	},
	SEND_MSG {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestSend sendRequest = (RequestSend)msg;
			commun.server.sendMsg(sendRequest.getMsgID(), sendRequest.getUserId(), sendRequest.getGroupName(), sendRequest.getMsg());
		}
	},

	LOGOUT {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
		}
	};
	
	public abstract void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun);
}


