package il.co.ilrd.quizzes;

public class PlusWithoutPlus {
	public int calc(int x, int y) {
		int counter = 0;
		
		while (y != 0) {
			int temp = x & y;
			x = x ^ y;
			y = temp << 1;
			System.out.println(++counter + "  " + temp + "  " + x + "  " + y);
		}
		return x;
	}
	public static void main(String[] args) {
		int x = 5, y = 7;
		System.out.println(new PlusWithoutPlus().calc(x ,y));

	}

}
