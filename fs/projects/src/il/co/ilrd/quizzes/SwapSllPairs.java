package il.co.ilrd.quizzes;


public class SwapSllPairs implements Cloneable{
	private ListNode head = new ListNode(null, null);
	public class ListNode {
		private Integer data;
		private ListNode nextNode;

		public ListNode(Integer data, ListNode next) {
			this.data = data;
			this.nextNode = next;
		}

		public ListNode getNextNode() {
			return nextNode;
		}
		public boolean hasNext() {
			if (this.getNextNode() == null) {
				return false;
			}
			return true;
		}
	}
	public void pushFront(Integer data) {
		ListNode newNode = new ListNode(data, head);
        head = newNode;
	}
	
	public ListNode swapPairs(ListNode head) {
		ListNode curr = head;
		while (curr.hasNext()) {
			Integer temp = curr.data;
			curr.data = curr.nextNode.data;
			curr.nextNode.data = temp;
			if (curr.nextNode.hasNext()) {
				curr = curr.nextNode.nextNode;
			}
			else {
				break;
			}
		}
		return head;
	}
	public static void main(String[] args) {
		SwapSllPairs sll = new SwapSllPairs();
		sll.pushFront(1);
		sll.pushFront(2);
		sll.pushFront(3);
		sll.pushFront(4);
		sll.pushFront(5);
		
		ListNode node = sll.head;
		while (node.hasNext()) {
			System.out.println(node.data);
			node = node.nextNode;
		}
		System.out.println();
		sll.swapPairs(sll.head);
		ListNode new_node = sll.head;
		while (new_node.hasNext()) {
			System.out.println(new_node.data);
			new_node = new_node.nextNode;
		}
		SwapSllPairs and = new SwapSllPairs();
		and.head.data = 5;
		
			try {
				SwapSllPairs yo = (SwapSllPairs)and.clone();
				System.out.println(yo.head.data);
			} catch (CloneNotSupportedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		
		
		}

}
