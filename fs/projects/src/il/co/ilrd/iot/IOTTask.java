package il.co.ilrd.iot;

import java.util.concurrent.Callable;

public class IOTTask implements Callable<V>{
	String key;
	Json data;
	
	public IOTTask(String key, JSON data) {
		this.key = key;
		this.data = data;
	}
	public String getKey() {
		return key;
	}
	
	public JSON getData() {
		return data;
	}
	@Override
	public V call() throws Exception {
		
		return null;
	}

}
