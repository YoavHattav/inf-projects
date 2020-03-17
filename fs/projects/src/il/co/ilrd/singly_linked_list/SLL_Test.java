package il.co.ilrd.singly_linked_list;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class SLL_Test {
	
	SLL sll = new SLL();

	@Test
	void testSize() {

		assertEquals(sll.size(), 0,"Size Failed");
	}
	
	@Test
	void testSize2() {

		assertEquals(sll.size(), 0, "Size Failed");
	}
	
	@Test
	void testFind() {
		
		sll.pushFront(1);
		assertEquals(sll.size(), 1,"Size Failed");
		sll.pushFront(2);
		assertEquals(sll.size(), 2,"Size Failed");
		assertEquals(sll.find(1).next(), 1,"Find Failed");
	}
}

/*public class singlyLinkedListTest {
	public static void main(String[] args) {
		
		SLL sll = new SLL();
		System.out.println("size 0: " + (0 == sll.size()));
		System.out.println("is empty true: " + (true == sll.isEmpty()));
		sll.pushFront(1);
		System.out.println("size 1: " + (1L == sll.size()));
		System.out.println("is empty false: " + (false == sll.isEmpty()));
		sll.pushFront(2);
		System.out.println("size 2: " + (2 == sll.size()));
		System.out.println("poped 2: " + sll.popFront());
		System.out.println("size 1: " + (1 == sll.size()));
		ListIterator itr = sll.begin();
		System.out.println(itr.next()); // 1
		System.out.println(itr.next()); // null
		System.out.println("find 1: " + sll.find(1).next());
		System.out.println("find 2: " + sll.find(2).next());
		}

}*/