package il.co.ilrd.VendingMachine;

class Item {
	
	final String name;
	final int price;
	int quantity;
	
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
