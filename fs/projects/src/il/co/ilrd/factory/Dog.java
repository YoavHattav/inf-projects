package il.co.ilrd.factory;

public class Dog extends Animal{
	int num_of_masters;
	
	public Dog() {
		num_of_masters = 5;
	}
	
	public String whatAmI(String I) {
		return ( I + "Dog");
	}
	
	public int getNum_of_masters() {
		return num_of_masters;
	}
	
	public void setNum_of_masters(int num_of_masters) {
		this.num_of_masters = num_of_masters;
	}
	
	public static String bark(String I) {
		return (I + "woffing dog");
	}
}
