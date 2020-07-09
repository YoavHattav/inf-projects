package il.co.ilrd.quizzes;

import java.util.HashMap;
import java.util.Map;

public class TwoNumsInArrayAndASum {
	private static Map<Integer, Integer> map = new HashMap<>();
	public static boolean doesItHoldTheTwo(int[] array, int sum) {
		for (int i = 0; i < array.length; ++i) {
			if (map.containsKey(sum - array[i])) {
				if ((map.get(sum - array[i]) + array[i]) == sum) {
					return true;
				}
			}
			else {
				map.put(array[i], array[i]);
			}
		}
		return false;
	}
	public static void main(String[] args) {
		int[] array = {0,1,2,3,4,5,6,7,8};
		System.out.println(TwoNumsInArrayAndASum.doesItHoldTheTwo(array, 14));
	}
}
