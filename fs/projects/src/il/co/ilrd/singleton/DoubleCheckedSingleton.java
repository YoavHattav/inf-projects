package il.co.ilrd.singleton;

public class DoubleCheckedSingleton {
	private volatile static DoubleCheckedSingleton instance = null;
	private int x = 0; 
	
	private DoubleCheckedSingleton() {
		x = 0; 
	}
	
	public static DoubleCheckedSingleton getInstance() { 
        if (instance == null)
        {
        	synchronized (DoubleCheckedSingleton.class) {
        		if (instance == null)
        		{
        			instance = new DoubleCheckedSingleton();
        		}         			
        	}
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
