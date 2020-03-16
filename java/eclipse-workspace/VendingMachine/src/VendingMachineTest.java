import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class VendingMachineTest {

	@Test
	void testInsertCoinAndPlaceOrder() {
		VendingMachine vendingMachine = new VendingMachine();

		vendingMachine.placeOrder("COLA");	
		for (Item p : Item.values()) {
			System.out.print(p + " : ");
			System.out.println(p.getQuantity());
		}
		
		vendingMachine.insertCoin(5);
		assertEquals(vendingMachine.getBalance(), 5);

		for (int i = 0; i < 32; ++i) {
			/*vendingMachine.insertCoin(4);*/
			/*assertEquals(vendingMachine.getBalance(), 9);*/
			vendingMachine.placeOrder("COLA");	
		}
			

		for (Item p : Item.values()) {
			System.out.print(p + " : ");
			System.out.println(p.getQuantity());
		}
		
		for (Item p : Item.values()) {
				if (p.name() == "TEA") {
					p.setQuantity(100);
					assertEquals(p.getQuantity(), 100);
				}
			}
	}
}
		/*for (product p : vendingMachine.stock) {
			System.out.print(p + " : ");
			System.out.println(p.getQuantity());		
			}*/


