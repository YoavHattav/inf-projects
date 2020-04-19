package il.co.ilrd.collection_ws;

public class DataObject {
	
	private String code;
	private int value;
	
	public DataObject(String code, int value) {
		super();
		this.code = code;
		this.value = value;
	}
	
	public static void main(String[] args) {
		DataObject[] dataArray = new DataObject[10];
		String j = "yoav";
				
		for (int i = 0; i < 10; ++i) {
			dataArray[i] = new DataObject(j, i);
		}
	}
}
