package il.co.ilrd.singly_linked_list;

public class SLL {
	
	private class node {
		
		private Object data;
		private node nextNode;

		public node(Object data, node nextNode) {
			this.data = data;
			this.nextNode = nextNode;
		}
			
		public Object getData() {
			return data;
		}
		public node getNextNode() {
			return nextNode;
		}
	}
	private node head = new node(null, null);
	
	public Boolean isEmpty(){
		return (null == head.getNextNode());
	}
	
	public ListIterator find(Object data) {
		
		ListIterator itr = begin();
		ListIterator itrPrev = begin();

		while (itr.hasNext())
		{
			if (itr.next().equals(data))
			{
				return itrPrev;
			}
			itrPrev.next();
		}
		
		return itr;
	}
	
	public int size() {
		
		ListIterator itr = begin();
		int size_counter = 0;
		
		while (itr.hasNext())
		{
			++size_counter;
			itr.next();
		}
		
		return size_counter;
	}
	
	public Object popFront(){
		
		Object dataHolder = head.getData();
		head = head.nextNode;
		
		return dataHolder;
	}
	
	public void pushFront(Object data) {
		node new_node = new node(data, head);
		head = new_node;
	}
	
	public ListIterator begin() {
		return new listIteratorImp();
	}

	private class listIteratorImp implements ListIterator {
		
		node node;
		
		public listIteratorImp() {
			node = head;
		}
		
		@Override
		public Object next() {
			Object data_holder = node.getData();
			node = node.getNextNode();
			
			return data_holder;
		}

		@Override
		public boolean hasNext() {
			return (null != node.nextNode);
		}
	}
}







