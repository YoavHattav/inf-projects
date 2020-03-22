package il.co.ilrd.vending_machine;

class Item {
	
	private final String name;
	private final int price;
	private int quantity;
	
	public Item(String name, int price, int quantity) {
		this.name = name;
		this.price = price;
		this.quantity = quantity;
	}
	public void setQuantity(int quantity) {
			this.quantity = quantity;
	}
	public int getQuantity() {
		return quantity;
	}
	public String getName() {
		return name;
	}

	public int getPrice() {
		return price;
	}
	
}
