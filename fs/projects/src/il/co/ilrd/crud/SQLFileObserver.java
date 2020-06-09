package il.co.ilrd.crud;

import java.util.Observable;
import java.util.Observer;

public class SQLFileObserver implements Observer, AutoCloseable{

	GenericCrud<String, Integer> crud;

	public SQLFileObserver(String url, String user, String password) {
		crud = new SQLCrud(url, user, password);
	}

	@Override
	public void update(Observable o, Object line) {
		crud.create((String)line);
	}
	@Override
	public void close() {
		try {
			crud.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
