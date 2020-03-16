
public class VendingMachine {

	public State state;
	public double balance;

	private enum State {
		INIT {

			@Override
			public State initialize() {return WAIT_FOR_COIN;}

			@Override
			public State gotCoin() {return null;}

			@Override
			public State gotOrder() {return null;}

		},
		WAIT_FOR_ORDER {

			@Override
			public State gotCoin() {return WAIT_FOR_ORDER;}

			@Override
			public State gotOrder() {return WAIT_FOR_COIN;}

			@Override
			public State initialize() {return null;}

		},
		WAIT_FOR_COIN {

			@Override
			public State initialize() {return null;}

			@Override
			public State gotCoin() {return WAIT_FOR_ORDER;}

			@Override
			public State gotOrder() {return WAIT_FOR_COIN;}
		};

		public abstract State initialize();
		public abstract State gotCoin();
		public abstract State gotOrder();
	}
	
	public VendingMachine() {
		Monitor print_obj = new MonitorIMP();
		state = State.INIT.initialize();
		balance = 0;
		print_obj.write("Hey there, how can i help?");
	}
	public State getState() {
		return state;
	}

	public void setState(State state) {
		this.state = state;
	}

	public double getBalance() {
		return balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}

	public void insertCoin(int coin) {
		setBalance(coin);
		state = state.gotCoin();
	}

	public double placeOrder(String order) {
		
		Monitor print_obj = new MonitorIMP();
		if (state == State.WAIT_FOR_ORDER) {
			for (Item item : Item.values()) {
				if (item.name() == order) {
					if ((balance >= item.getPrice()) && (item.getQuantity() > 0)) {
						final int one = 1;
						balance = balance - item.getPrice();
						item.setQuantity(item.getQuantity() - one);
						state = state.gotOrder();
						print_obj.write("enjoy your drink");

						return balance;
					}
					else
					{
						print_obj.write("Could not complete order");
					}
				}
			}
		}
		else
		{
			print_obj.write("Insert coin pls");
		}
		
		balance = 0;
		return balance;
	}
}
