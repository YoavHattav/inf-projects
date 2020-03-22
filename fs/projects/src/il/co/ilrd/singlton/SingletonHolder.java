package il.co.ilrd.singlton;

public class SingletonHolder {
	private int x; 
	
	private SingletonHolder() {
		x = 0; 
	}
	
	private static class Singleton {
		public static Singleton instance = new Singleton();
	}
	
	public static Singleton getInstance() {
		return Singleton.instance;
	}
	
	public int getX() {
		return x;
	}

	public void setX() {
		this.x = 5;
	}
}
