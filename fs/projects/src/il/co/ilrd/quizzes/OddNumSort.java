package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.Arrays;

public class OddNumSort {
	ArrayList<Integer> oddIndex = new ArrayList<>();		
	private boolean swapFlag = true;
	private int swapAid = 0;
	
	public void sortOddNums(int[] array) {
		for (Integer i = 0; i < array.length; ++i) {
			if (array[i] % 2 == 1) {
				oddIndex.add(i);
			}
		}
		
		while (swapFlag) {
			swapFlag = false;
			for (int i = 1; i < oddIndex.size(); ++i) {
				if (array[oddIndex.get(i - 1)] > array[oddIndex.get(i)]) {
					swapFlag = true;
					swapAid = array[oddIndex.get(i - 1)];
					array[oddIndex.get(i - 1)] = array[oddIndex.get(i)];
					array[oddIndex.get(i)] = swapAid;
				}
			}
		}
	}
	
	public static void main(String[] args) {
		int[] array = {5, 3, 13, 17, 6, 7, 8, 11, 1, 3, 9};
		for (Integer i = 0; i < array.length; ++i) {
			System.out.print(array[i] + " ");
		}
		System.out.println();
		OddNumSort sorter = new OddNumSort();
		sorter.sortOddNums(array);
		for (Integer i = 0; i < array.length; ++i) {
			System.out.print(array[i] + " ");
		}
	}

}
