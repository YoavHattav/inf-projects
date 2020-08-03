package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class LargestNumBuilder {

	public String largestNumber(final int [] arr) {
		List<String> list = new ArrayList<>();
		StringBuilder str = new StringBuilder();
		for (int i = 0; i < arr.length; ++i) {
			list.add(Integer.toString(arr[i]));
		}
		list.sort(new Comparator<String>(){

			@Override
			public int compare(String X, String Y) { 

				String XY=X + Y; 
				String YX=Y + X; 

				return XY.compareTo(YX) > 0 ? -1:1; 
			} 
		});
		
		for (String curr : list) {
			str.append(curr);
		}
		return str.toString();
	}
	public static void main(String[] args) {
		final int[] arr = {3, 30, 34, 5, 9};
		System.out.println(new LargestNumBuilder().largestNumber(arr));
	}
}
