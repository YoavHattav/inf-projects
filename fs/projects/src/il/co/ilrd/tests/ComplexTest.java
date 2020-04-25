package il.co.ilrd.tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import il.co.ilrd.complex.Complex;

class ComplexTest {

	/*@Test
	void testHashCode() {
	}*/

	@Test
	void testAdd() {
		Complex c1 = new Complex(2, 2);
		Complex c2 = new Complex(3, 3);
		
		Complex c3 = c1.add(c2);
		Complex c4 = c2.add(c1);

		assertEquals(c3, c4, "add failed");
	}

	@Test
	void testSubtract() {
		Complex c1 = new Complex(2, 2);
		Complex c2 = new Complex(3, 3);
		
		Complex c3 = c1.subtract(c2);
		Complex c4 = c2.subtract(c1);

		assertEquals(c3.getImg(), -1, "sub failed");
		assertEquals(c3.getReal() , -1, "sub failed");
		assertEquals(c4.getImg(), 1, "sub failed");
		assertEquals(c4.getReal(), 1, "sub failed");
	}

	@Test
	void testMultiplyBy() {
		Complex c1 = new Complex(2, 2);
		Complex c2 = new Complex(3, 3);
		
		Complex c3 = c1.add(c2);
		Complex c4 = c2.add(c1);

		assertEquals(c3, c4, "add failed");
	}

	@Test
	void testDivideBy() {
		Complex c1 = new Complex(2, 2);
		Complex c2 = new Complex(3, 3);
		
		Complex c3 = c1.add(c2);
		Complex c4 = c2.add(c1);

		assertEquals(c3, c4, "add failed");
	}
/*
	@Test
	void testSetReal() {
		fail("Not yet implemented");
	}

	@Test
	void testSetImg() {
		fail("Not yet implemented");
	}

	@Test
	void testSetValue() {
		fail("Not yet implemented");
	}

	@Test
	void testIsReal() {
		fail("Not yet implemented");
	}

	@Test
	void testIsImg() {
		fail("Not yet implemented");
	}

	@Test
	void testParse() {
		fail("Not yet implemented");
	}

	@Test
	void testCompareTo() {
		fail("Not yet implemented");
	}

	@Test
	void testToString() {
		fail("Not yet implemented");
	}

	@Test
	void testEqualsObject() {
		fail("Not yet implemented");
	}
*/
}
