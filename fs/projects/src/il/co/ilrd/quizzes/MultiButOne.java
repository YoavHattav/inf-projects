package il.co.ilrd.quizzes;

import java.util.HashMap;
import java.util.Map;

public class MultiButOne {
	
	public int[] multiButOne(int[] array) {
		int[] newArray = new int[array.length];
		for (int i = 0; i < array.length; ++i) {
			newArray[i] = 1;
			for (int j = 0; j < array.length; ++j) {
				if (j == i) {
					continue;
				}
				newArray[i] *= array[j];
			}
		}
		
		return newArray;
	}
	public int[] multiButOneFix(int[] array) {
		int[] newArray = new int[array.length];
		int sum = 1;
		for (int i = 0; i < array.length; ++i) {
			sum *= array[i];
		}
		for (int j = 0; j < array.length; ++j) {
				newArray[j] = sum / array[j];
		}
		
		return newArray;
	}
	public static void main(String[] args) {
		int[] array = {1, 2, 3, 4, 5, 6};
		MultiButOne m = new MultiButOne();
		int[] newArray = m.multiButOne(array);
		for (int i = 0; i < array.length; ++i) {
			System.out.println(newArray[i]);
		}
		System.out.println();
		newArray = m.multiButOneFix(array);
		for (int i = 0; i < array.length; ++i) {
			System.out.println(newArray[i]);
		}

	}

}
