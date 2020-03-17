package il.co.ilrd.VendingMachine;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class VendingMachineTest {

	@Test
	void testInsertCoinAndPlaceOrder() {
		
		 class monitorInterface implements Monitor{

			public void write(String msg) {
				System.out.println(msg);
			}
		}
		
		Monitor monitor = new monitorInterface();
		VendingMachine vendingMachine = new VendingMachine(monitor);
		
		Item tea = new Item("tea", 4, 15);
		vendingMachine.setNewProduct(tea);
		Item cola = new Item("cola", 4, 15);
		vendingMachine.setNewProduct(cola);
		
		vendingMachine.placeOrder("cola");
		for (Item item : vendingMachine.stock) {
			System.out.print(item.getName() + " : ");
			System.out.println(item.getQuantity());
		}
		
		double change = 0;
		
		vendingMachine.insertCoin(10);
		assertEquals(vendingMachine.getBalance(), 10);
		change = vendingMachine.placeOrder("tea");
		assertEquals(vendingMachine.getBalance(), 0);
		System.out.println("change was: "+ change);
		
		for (int i = 0; i < 10; ++i) {
			vendingMachine.insertCoin(10);
			change = vendingMachine.placeOrder("cola");
			System.out.println("change was: "+ change);
			assertEquals(vendingMachine.getBalance(), 0);
		}	

		for (Item item : vendingMachine.stock) {
			System.out.print(item.getName() + " : ");
			System.out.println(item.getQuantity());
		}
		
		for (Item item : vendingMachine.stock) {
				if (item.getName() == "TUT") {
					item.setQuantity(100);
					assertEquals(item.getQuantity(), 100);
				}
			}
	}
}