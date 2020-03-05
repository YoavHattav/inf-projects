package SLL;

public class SLL {
	
	private node head = new node(null, null);
	
	public Boolean isEmpty(){
		return (null == head.nextNode);
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

	private class listIteratorImp implements ListIterator {
		
		node itr;
		
		public listIteratorImp() {
			itr = head;
		}
		
		@Override
		public Object next() {
			Object data_holder = itr.getData();
			itr = itr.nextNode;
			
			return data_holder;
		}

		@Override
		public boolean hasNext() {
			return (null != itr.nextNode);
		}
	}
}







