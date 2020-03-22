package il.co.ilrd.singleton;

public class StaticFinalSingleton {

	static final StaticFinalSingleton instance = new StaticFinalSingleton();
	private int x;
	
	private StaticFinalSingleton() {
		x = 0;
	}
	
	public static StaticFinalSingleton getInstance() {
		return instance;
	}

	public int getX() {
		return x;
	}

	public void setX() {
		this.x = 5;
	}
}
