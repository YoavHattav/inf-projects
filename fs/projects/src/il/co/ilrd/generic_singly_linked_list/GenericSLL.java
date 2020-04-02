package il.co.ilrd.generic_singly_linked_list;

import java.util.Iterator;

public class GenericSLL<T> implements Iterable<T> {
	
	private Node<T> head = new Node<>(null, null);
	private boolean modCount = false;

	private static class Node<T> {
		
		private T data;
		private Node<T> nextNode;

		public Node(T data, Node<T> nextNode) {
			this.data = data;
			this.nextNode = nextNode;
		}
			
		public T getData() {
			return data;
		}
		
		public void setNextNode(Node<T> nextNode) {
			this.nextNode = nextNode;
		}

		public Node<T> getNextNode() {
			return nextNode;
		}
	}
	
	public void pushFront(T data) {
		modCount = true;
        Node<T> newNode = new Node<>(data, head.nextNode);
        head.nextNode = newNode;
        System.out.println("HERE");
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
		
		private Node<T> curr_node;
		
		public listIteratorImp() {
			curr_node = head;
		}
		
		@Override
		public T next() {
			T data_holder = curr_node.getData();
			curr_node = curr_node.getNextNode();
			
			return data_holder;
		}

		@Override
		public boolean hasNext() {
			return (null != curr_node.nextNode);
		}
	}

	@Override
	public Iterator<T> iterator() {
		return null;
	}
}
