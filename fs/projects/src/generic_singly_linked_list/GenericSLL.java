package generic_singly_linked_list;

import java.util.Iterator;

public class GenericSLL<T> implements Iterable<T> {
	
	private Node head = new Node(null, null);

	private class Node {
		
		private T data;
		private Node nextNode;

		public Node(T data, Node nextNode) {
			this.data = data;
			this.nextNode = nextNode;
		}
			
		public Object getData() {
			return data;
		}
		
		public void setNextNode(Node nextNode) {
			this.nextNode = nextNode;
		}

		public Node getNextNode() {
			return nextNode;
		}
	}
	
	public GenericSLL() {
		
	}
	public void pushFront() {
		
	}
	public T popFront() {
		
	}
	public int size() {
		
	}
	public boolean isEmpty() {
		
	}
	public Iterator<T> find() {
		
	}
	
	public static <E> GenericSLL<E> merge(GenericSLL<E> one, GenericSLL<E> two) {
		
	}
	
	public static <E> GenericSLL<E> newReverse(GenericSLL<E> sll) {
		
	}
	
	public static <E> void print(GenericSLL<E> sll) {
		
	}
	
	private class listIteratorImp implements Iterator<T>{
		
		private Node curr_node;
		
		@Override
		public boolean hasNext() {
			return false;
		}

		@Override
		public T next() {
			return null;
		}
	}

	@Override
	public Iterator<T> iterator() {
		// TODO Auto-generated method stub
		return null;
	}
}
