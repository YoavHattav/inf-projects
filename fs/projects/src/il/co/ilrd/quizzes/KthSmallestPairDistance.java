package il.co.ilrd.quizzes;

import java.util.Arrays;

public class KthSmallestPairDistance {
	public static int kthSmallestPairDistance(int[] array, int k) {
		int len = 0;
		int[] dis_array;
		for (int i = array.length - 1; i > 0; --i)
		{
			len += i; 
		}
		dis_array = new int[len];
		int j = 0;
		for (int i = 0; i < array.length-1; ++i) {
			for (int c = i + 1; c < array.length; ++c) {
				dis_array[j] = Math.abs(array[i] - array[c]);
				++j;
			}
		}
		Arrays.sort(dis_array);
		
		return dis_array[k];
	}
	
	public static void main(String[] args) {
		int[] array = {1,13,4,53,6,23,14,2,32};
		System.out.println(KthSmallestPairDistance.kthSmallestPairDistance(array, 0));

	}

}
