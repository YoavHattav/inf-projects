package il.co.ilrd.chat_server;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Random;
import java.util.Set;

import il.co.ilrd.collections.HashMap;

public class ChatServerHub implements ChatServer{
	
	private Map<Integer, User> users = new HashMap<>();
	private Map<String, Group> groups = new HashMap<>();
	
	@Override
	public void logIn(int msgId, String email, String name, Peer peer) {
		Collection<User> userCollection = users.values();
		for (User user : userCollection) {
			if (user.email.equalsIgnoreCase(email)) {
				user.peer = peer;
				peer.responseLogin(msgId, user.id, user.groupNames, Status.SUCCESS);
				return;
			}
		}
		User user = new User(name, email, peer);
		users.put(user.id, user);
		peer.responseLogin(msgId, user.id, user.groupNames, Status.SUCCESS);
	}
	
	@Override
	public void createNewGroup(int msgId, Integer userId, String groupName) {
		User user = users.get(userId);
		System.out.println(groupName);
		if (groups.containsKey(groupName)) {
			user.peer.responseCreateGroup(msgId, groupName, Status.GROUP_ALREADY_EXISTS);
			return;
		}
		Group newGroup = new Group(groupName, user);
		groups.put(groupName, newGroup);
		user.peer.responseCreateGroup(msgId, groupName, Status.SUCCESS);
	}
	
	@Override
	public void joinGroup(int msgId, Integer userId, String groupName) {
		User user = users.get(userId);
		Group group = groups.get(groupName);
		if (group == null) {
			user.peer.responseJoinGroup(msgId, user.id, user.name, groupName, Status.GROUP_NOT_FOUND);
			return;
		}
		if (group.usersInGroup.containsKey(user.id)) {
			user.peer.responseJoinGroup(msgId, user.id, user.name, groupName, Status.ALREADY_IN_GROUP);
			return;
		}
		group.usersInGroup.put(userId, new ColorUsrProperties());
		for (Integer id : group.usersInGroup.keySet()) {
			users.get(id).peer.responseJoinGroup(msgId, user.id, user.name, groupName, Status.SUCCESS);
		}
	}
	
	@Override
	public void leaveGroup(int msgId, Integer userId, String groupName) {
		Group group = groups.get(groupName);
		User user = users.get(userId);
		if (group == null) {
			user.peer.responseLeaveGroup(msgId, userId, user.name, groupName, Status.GROUP_NOT_FOUND);
			return;
		}
		if (!group.usersInGroup.containsKey(user.id)) {
			user.peer.responseLeaveGroup(msgId, user.id, user.name, groupName, Status.NOT_IN_GROUP);
			return;
		}
		group.usersInGroup.remove(user.id);
		for (Integer id : group.usersInGroup.keySet()) {
			users.get(id).peer.responseLeaveGroup(msgId, user.id, user.name, groupName, Status.SUCCESS);
		}
	}
	
	@Override
	public void sendMsg(int msgId, Integer userId, String groupName, String msg) {
		Group group = groups.get(groupName);
		User user = users.get(userId);
		if (group == null) {
			user.peer.responseMessage(msgId, user.id, user.name, groupName, null, msg, Status.GROUP_NOT_FOUND);
			return;
		}
		if (!group.usersInGroup.containsKey(user.id)) {
			user.peer.responseMessage(msgId, user.id, user.name, groupName, new ColorUsrProperties(), msg, Status.NOT_IN_GROUP);
			return;
		}
		for (Integer id : group.usersInGroup.keySet()) {
			users.get(id).peer.responseMessage(msgId, user.id, user.name, groupName, group.usersInGroup.get(user.id), msg, Status.SUCCESS);
		}
	}
	
	private static class User {
		private String name;
		private String email;
		private int id;
		private Peer peer;
		private static int counter;
		private Set<String> groupNames = new HashSet<String>(); 
		
		public User(String name, String email, Peer peer) {
			this.name = name;
			this.email = email;
			this.id = ++counter;
			this.peer = peer;
		}	
	}
	
	private static class Group {
		private Map<Integer, UsrProperties> usersInGroup = new HashMap<Integer, UsrProperties>();
		private String name;
		
		public Group(String name, User user) {
			this.name = name;
			usersInGroup.put(user.id, new ColorUsrProperties());
		}	
	}
	private static class ColorUsrProperties implements UsrProperties{
		private Color color;
		private Random rand;
		
		public ColorUsrProperties() {
			rand = new Random();
			float r = rand.nextFloat();
			float g = rand.nextFloat();
			float b = rand.nextFloat();
			this.color = new Color(r, g, b);
		}

		@Override
		public Color getColor() {
			return color;
		}
	}
}