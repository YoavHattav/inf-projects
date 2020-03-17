package il.co.ilrd.example;

class Yoav{
	static {
		System.out.println("hey mama");
	}
}
public class TestClassLoading {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Yoav x = new Yoav();
		Other y = new Other();
	}

}
