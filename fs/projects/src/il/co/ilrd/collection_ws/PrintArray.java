package il.co.ilrd.collection_ws;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class PrintArray {	
	public static void main(String[] args) {
		Integer[] primitive_array = {5,6,7,8,9,10, 1,2,13,14};
		for (int i = 0; i < 10; ++i)
		{
			System.out.print(primitive_array[i] + " ");
		}
		System.out.println("");
		List<Integer> list = (List<Integer>)Arrays.asList(primitive_array);
		Collections.sort(list);
		for (Object item : list)
		{
			System.out.print(item + " ");
		}
	}
}
