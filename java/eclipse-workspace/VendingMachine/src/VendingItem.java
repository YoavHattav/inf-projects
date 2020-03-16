
enum Item {
	COLA(15, 4),
	ZERO(15, 4),
	TEA(5, 6),
	WATER(10, 3),
	TUTIT(10, 5),
	MANGO(10,4),
	FANTA(10, 4);
	
	public int price;
	public int quantity;
	
	private Item(int quantity, int price) {
		this.price = price;
		this.quantity = quantity;
	}
	
	public int getPrice() {
		return price;
	}
	
	public int getQuantity() {
		return quantity;
	}

	public void setPrice(int price) {
		this.price = price;
	}

	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}
}
