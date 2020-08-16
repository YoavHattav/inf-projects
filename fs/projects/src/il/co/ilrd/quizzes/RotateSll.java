package il.co.ilrd.quizzes;

public class RotateSll {
	
	static class Node {
		int data;
		Node next;
		Node(int d)
		{
			data = d;
			next = null;
		}
	}
	
	public static Node rotateRight(int k, Node head, int size) {
		// O(n)
		k = k % size;
		Node temp = head;
		Node newHead = null;
		
		for (int i = 0; i < k - 2; ++i) {
			temp = temp.next;
		}
		
		newHead = temp.next;
		temp.next = null;
		temp = newHead;
		
		while (temp.next != null) {
			temp = temp.next;
		}
		temp.next = head;
		
		return newHead;
	}
	
	public static void printSll(Node head) {
		Node temp = head;
		while (temp != null) {
			System.out.print(temp.data);
			temp = temp.next;
		}
		System.out.println();
	}
	
	public static void main(String[] args) {
		Node head = new Node(1);
		head.next = new Node(2);
		head.next.next = new Node(3);
		head.next.next.next = new Node(4);
		head.next.next.next.next = new Node(5);
		
		printSll(head);
		printSll(rotateRight(3, head, 5));
	}

}
