package il.co.ilrd.quizzes;

public class GridWalking {
	public static int numOfOptions(int m, int n) {
		if (m == 1) {
			return 1;
		}
		if (n == 1) {
			return 1;
		}
		return numOfOptions(m, n - 1) + numOfOptions(m - 1, n);
	}
	public static void main(String[] args) {
		System.out.println(GridWalking.numOfOptions(70, 7));
	}

}
