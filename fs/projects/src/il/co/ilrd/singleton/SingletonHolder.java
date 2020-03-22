package il.co.ilrd.singleton;

public class SingletonHolder {
	private int x; 
	
	private SingletonHolder() {
		x = 0; 
	}
	
	private static class Singleton {
		public static SingletonHolder instance = new SingletonHolder();
	}
	
	public static SingletonHolder getInstance() {
		return Singleton.instance;
	}
	
	public int getX() {
		return x;
	}

	public void setX() {
		this.x = 5;
	}
}
