import java.util.ArrayList;

public class VendingMachine {

	private static State state;
	private double balance;
	
	ArrayList<Item> stock = new ArrayList<Item>();
	
	public void setNewProduct(Item product) {
		stock.add(product);
	}
	
	Monitor monitor = null;
	
	private enum State {
		INIT{

			@Override
			void gotOrder(VendingMachine machine, String order) {
				state = State.WAIT_FOR_COIN;
			}
	
			@Override
			void gotCoin(VendingMachine machine, int coin) {
				state = State.WAIT_FOR_COIN;
			}
	
			@Override
			void initialize() {
				state = State.WAIT_FOR_COIN;
			}
		},	
	 
		WAIT_FOR_COIN
		 {
	
			@Override
			void gotOrder(VendingMachine machine, String order) {
				machine.monitor.write("insert coin pls");
				state = State.WAIT_FOR_COIN;
			}
	
			@Override
			void gotCoin(VendingMachine machine, int coin) {
				machine.balance += coin;
				state = State.WAIT_FOR_ORDER;
			}
	
			@Override
			void initialize() {
			}
		},
		
		WAIT_FOR_ORDER
		 {

			@Override
			void gotOrder(VendingMachine machine, String order) {
				final int one = 1;
				for(Item item : machine.stock) 
				{
					if (item.getName() == order)
					{
						if (item.getQuantity() >= 1) 
						{
							if (machine.balance >= item.getPrice())
							{	
								machine.balance -= item.getPrice();
								item.setQuantity(item.getQuantity() - one);
								state = State.WAIT_FOR_COIN;
							}
							else
							{
								machine.monitor.write("insert coin pls");
								state = State.WAIT_FOR_COIN;
							}
						}
						else
						{
							machine.monitor.write("out of stock");
							state = State.WAIT_FOR_ORDER;
						}
					}
				}
			}

			@Override
			void gotCoin(VendingMachine machine, int coin) {
				machine.balance += coin;
				state = State.WAIT_FOR_ORDER;
			}

			@Override
			void initialize() {
			}
			
		};	
			
		abstract void gotOrder(VendingMachine machine, String order);
		abstract void gotCoin(VendingMachine machine, int coin);
		abstract void initialize();

	}
	public VendingMachine(Monitor monitor) {
		this.monitor = monitor;
		state = State.INIT;
		balance = 0;
	}
	public void insertCoin(int coin) {
		state.gotCoin(this, coin);
	}

	public double placeOrder(String order) {
		state.gotOrder(this, order);
		double change = balance;
		balance = 0;
		return change;
	}

	public double getBalance() {
		return balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}
}
