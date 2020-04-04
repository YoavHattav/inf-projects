package il.co.ilrd.generic_singly_linked_list;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericSLL<T> implements Iterable<T> {
	
	private Node<T> head = new Node<>(null, null);
	private volatile int modCount = 0;

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

		public Node<T> getNextNode() {
			return nextNode;
		}
	}
	
	public void pushFront(T data) {
		++modCount;
        Node<T> newNode = new Node<>(data, head);
        head = newNode;
	}
	
	public T popFront() {
		
		if(!isEmpty()) {
			++modCount;
			T data = head.data;
			head = head.nextNode;

			return data;	
		}
		
		throw new NullPointerException();
	}
	
	public int size() {
		int counter = 0;
		listIteratorImp<T> itr = new listIteratorImp<T>(this);
		
		while (itr.hasNext())
		{
			++counter;
			itr.next();
		}
		
		return counter;
	}
	
	public Boolean isEmpty(){
		return (null == head.getNextNode());
	}
	
	public Iterator<T> find(T data) {
		listIteratorImp<T> itr = new listIteratorImp<T>(this);
		while ((itr.hasNext()) && !(itr.curr_node.data.equals(data)))
		{
			itr.next();
		}
		return itr;
	}
	
	public static <E> GenericSLL<E> merge(GenericSLL<E> one, GenericSLL<E> two) {
		
		GenericSLL<E> new_sll = new GenericSLL<E>();
		
		for (E elem : one)
		{
			new_sll.pushFront(elem);
		}
		for (E elem : two)
		{
			new_sll.pushFront(elem);
		}
		
		return new_sll;
	}
	
	public static <E> GenericSLL<E> newReverse(GenericSLL<E> sll) {
		GenericSLL<E> new_sll = new GenericSLL<E>();
		for (E elem : sll)
		{
			new_sll.pushFront(elem);
		}
		
		return new_sll;
	}
	
	public static <E> void print(GenericSLL<E> sll) {
		
		for (E elem : sll)
		{
			System.out.println(elem.toString());
		}
	}
	
	@Override
	public Iterator<T> iterator() {
		return new listIteratorImp<T>(this);
	}
	
	private static class listIteratorImp<T> implements Iterator<T>{
		
		private Node<T> curr_node;
		GenericSLL<T> list;
		private volatile int itr_modCount;

		private listIteratorImp(GenericSLL<T> list) {
	        curr_node = list.head;
	        this.list = list;
	        itr_modCount = list.modCount;
	    }
		
		@Override
		public T next() {
			
			if (itr_modCount != list.modCount) {
	            throw new ConcurrentModificationException("ERROR: Data Structre have been modified");
	        }
	        if (list.isEmpty()) {
	            throw new NullPointerException("Can't Iter on empty list");
	        }
	        
			T data_holder = curr_node.getData();
			curr_node = curr_node.getNextNode();
			
			return data_holder;
		}

		@Override
		public boolean hasNext() {
			if (itr_modCount != list.modCount) {
	            throw new ConcurrentModificationException("ERROR: Data Structre have been modified");
	        }
	        return(null != curr_node.nextNode);
		}
	}
}

