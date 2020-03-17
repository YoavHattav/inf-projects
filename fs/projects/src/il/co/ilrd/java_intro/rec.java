package il.co.ilrd.java_intro;

class Recursion {
	public static void main(String[] args) {
		int num = 0;
		Recursion.rec(num);
	}
	public static void rec(int num){
		if (10000 > num)
		{
			System.out.println(num);
			Recursion.rec(num + 1);
		}
	}
}