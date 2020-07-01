package il.co.ilrd.quizzes;

public class ConsecutiveSum {
	
	public static Integer calcImp(int[] array, int k) {
		int sum = 0, current_sum = 0, length = array.length, sub_size = k;
		if (length - k < 0) {
			System.out.println("the array does not hold a sub array of that size");
			return 0;
		}
		for (int i = 0; i < k; ++i) {
			sum += array[i];
		}
		current_sum = sum;
		for (int i = sub_size; i < length; ++i, ++k) {
			current_sum = current_sum - array[i - sub_size] + array[k];
			sum = (current_sum > sum) ? current_sum : sum;
		}
		return sum;
	}
	
	public static void main(String[] args) {
		int k1 = 4, k2 = 4, k3 = 3, k4 = 2;
		int[] array_one = {1, 2, 3, 4, 5, 6, 7, 8, 9, -10, 100};
		int[] array_two = {1,4,2,10,23,3,1,0,20};
		int[] array_three = {2, 3};
		int[] array_four = {100, 200, 300, 400};
		
		System.out.println("should be 30 : " + ConsecutiveSum.calcImp(array_one, k1));
		System.out.println("should be 39 : " + ConsecutiveSum.calcImp(array_two, k2));
		System.out.println("should be invalid : " + ConsecutiveSum.calcImp(array_three, k3));
		System.out.println("should be 700 : " + ConsecutiveSum.calcImp(array_four, k4));
	}
}
