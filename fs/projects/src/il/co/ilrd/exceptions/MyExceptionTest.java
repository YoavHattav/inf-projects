package il.co.ilrd.exceptions;

public class MyExceptionTest {
	
	public static void Foo3(int yoav) throws MyException1{
		try {
			if (0 == yoav)
			{
				throw new MyException1("yoav can't be worth nothing");
			}
		} catch (MyException1 e) {
			e.printStackTrace();
		}
	}
	public static void Foo4(int yoav) {
		try {
			if (0 > yoav)
			{
				throw new MyException1("yoav can't be worth less than nothing");
			}
		} catch (MyException1 e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String args[])
	{
		int[] exam = new int[100]; 
		Foo3(0);
		Foo4(-1);
		System.out.println(exam[100]);
	}
}
