package SLL;

public class SLL {
	
	private node head = new node(null, null);
	
	public Boolean isEmpty(){
		return ;
	}
	
	public ListIterator find(Object data) {
		
	}
	
	public int size() {
		
		ListIterator itr = begin();
		int size_counter = 0;
		
		while (itr.hasNext())
		{
			++size_counter;
			itr.next();
		}
	}
	public Object popFront(){
		
	}
	
	public void pushFront() {
		
	}
	
	public ListIterator begin() {
		
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
		public listIteratorImp(){
			itr = head;
		}
		@Override
		public Object next() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return null;
		}

	}
}







