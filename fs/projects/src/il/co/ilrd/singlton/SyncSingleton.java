package il.co.ilrd.singlton;

public class SyncSingleton {
	
	static SyncSingleton instance = null;
	private int x;
	
	private SyncSingleton() {
		x = 0;
	}
	
	public static SyncSingleton getInstance() {
		if (null == instance)
		{
			instance = new SyncSingleton();
		}
		return instance;
	}

	public int getX() {
		return x;
	}

	public void setX() {
		this.x = 5;
	}
}
