package il.co.ilrd.generic_singly_linked_list;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Iterator;

import org.junit.jupiter.api.Test;

class GenericSLLTest {

	/*@Test
	void test_exception_change() {
		GenericSLL<Integer> sll_one = new GenericSLL<Integer>();
		assertEquals(0, sll_one.size());
		try { 
			sll_one.pushFront(1);
			Iterator<Integer> itr = sll_one.iterator();
			sll_one.pushFront(2);
			itr.next();
			}catch (Exception e) { 
				e.printStackTrace();
		}
		assertEquals(2, sll_one.size());

	}
	@Test
	void test_exception_empty() {
		GenericSLL<Integer> sll_one = new GenericSLL<Integer>();
		assertEquals(0, sll_one.size());
		try { 
			Iterator<Integer> itr = sll_one.iterator();
			itr.next();
			sll_one.pushFront(2);
			}catch (Exception e) { 
				e.printStackTrace();
		}
		assertEquals(2, sll_one.size());
	}*/
	@Test
	void test_pop_push() {
		GenericSLL<Integer> sll_one = new GenericSLL<Integer>();
		assertEquals(0, sll_one.size());
		assertEquals(true, sll_one.isEmpty());

		try { 
			sll_one.pushFront(2);
			assertEquals(2, sll_one.popFront());
			sll_one.pushFront(3);
			sll_one.pushFront(4);
			sll_one.pushFront(5);
			sll_one.pushFront(6);
			assertEquals(6, sll_one.popFront());
			assertEquals(5, sll_one.popFront());
			}catch (Exception e) { 
				e.printStackTrace();
		}
		assertEquals(2, sll_one.size());
	}
	@Test
	void test_find() {
		GenericSLL<Integer> sll_one = new GenericSLL<Integer>();
		assertEquals(0, sll_one.size());
		try { 
			sll_one.pushFront(2);
			assertEquals(2, sll_one.popFront());
			sll_one.pushFront(3);
			sll_one.pushFront(4);
			sll_one.pushFront(5);
			sll_one.pushFront(6);
			assertEquals(6, sll_one.popFront());
			Iterator<Integer> itr = sll_one.iterator();
			itr = sll_one.find(3);
			assertEquals(3, itr.next());
			}catch (Exception e) { 
				e.printStackTrace();
		}
		assertEquals(3, sll_one.size());
	}
	@Test
	void test_print_merge() {
		GenericSLL<Integer> sll_one = new GenericSLL<Integer>();
		GenericSLL<Integer> sll_two = new GenericSLL<Integer>();

		assertEquals(0, sll_one.size());
		try { 
			sll_one.pushFront(2);
			assertEquals(2, sll_one.popFront());
			sll_one.pushFront(1);
			sll_one.pushFront(2);
			sll_one.pushFront(3);
			sll_one.pushFront(4);
			sll_two.pushFront(5);
			sll_two.pushFront(6);
			sll_two.pushFront(7);
			assertEquals(4, sll_one.popFront());
			Iterator<Integer> itr = sll_one.iterator();
			itr = sll_one.find(3);
			assertEquals(3, itr.next());
			GenericSLL.print(sll_one);
			GenericSLL.print(sll_two);
			
			GenericSLL<Integer> sll_merge;
			sll_merge = GenericSLL.merge(sll_one, sll_two);
			GenericSLL.print(sll_merge);

			}catch (Exception e) { 
				e.printStackTrace();
		}
		assertEquals(3, sll_one.size());
	}
	@Test
	void test_print_reverse() {
		GenericSLL<Integer> sll_one = new GenericSLL<Integer>();
		
		assertEquals(0, sll_one.size());
		try { 
			sll_one.pushFront(2);
			assertEquals(2, sll_one.popFront());
			sll_one.pushFront(11);
			sll_one.pushFront(22);
			sll_one.pushFront(33);
			sll_one.pushFront(44);
			sll_one.pushFront(55);
			sll_one.pushFront(66);
			sll_one.pushFront(77);
			GenericSLL.print(sll_one);
			
			GenericSLL<Integer> sll_reverse;
			sll_reverse = GenericSLL.newReverse(sll_one);
			GenericSLL.print(sll_reverse);

			}catch (Exception e) { 
				e.printStackTrace();
		}
	}
}
