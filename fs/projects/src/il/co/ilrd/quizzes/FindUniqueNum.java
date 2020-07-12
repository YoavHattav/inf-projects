package il.co.ilrd.quizzes;

public class FindUniqueNum {
	public static Integer findUniqueNum(int[] array) {
		Integer sum = 0;
		for (Integer num : array) {
			sum ^= num;
		}
		return sum;
	}
	public static void main(String[] args) {
		int[] array = {1, 2, 3, 4, 5, 1, 2, 3, 4};
		System.out.println(FindUniqueNum.findUniqueNum(array));
	}

}
