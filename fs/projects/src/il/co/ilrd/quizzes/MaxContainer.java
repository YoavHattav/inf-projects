package il.co.ilrd.quizzes;

public class MaxContainer {
	static public Integer maxArea(int[] array, int n) {
		Integer currMax = Math.min(array[0], array[n-1]) * (n-1);
		Integer posibleMax = 0;
		int i = 0;
		while (i < n) {
			if (array[i] == array[n-1]) {
				++i;
			}
			else {
				if (array[i] > array[n-1]) {
					--n;
				}
				else {
					++i;
				}
			}
			posibleMax = Math.min(array[i], array[n-1]) * ((n-1) - i);
			currMax = currMax > posibleMax ? currMax : posibleMax;
		}
		return currMax;
	}
	public static void main(String[] args) {
		int[] array = {1, 8, 6, 2, 5, 4, 8, 3, 7};
		MaxContainer max = new MaxContainer();
		System.out.println(max.maxArea(array, 9));

	}
}
