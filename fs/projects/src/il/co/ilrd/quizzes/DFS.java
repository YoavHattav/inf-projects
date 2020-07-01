package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.List;

public class DFS {
	private static Integer depthsumHelper(List<Object> list, int n) {
		Integer sum = 0, recSum = 0;
		int lvl = n;
		for (Object obj : list) {
			if (obj instanceof Integer) {
				sum += (Integer)obj;
			}
			else {
				recSum += depthsumHelper((List)obj, ++n);
			}
		}
		return (sum * lvl) + recSum;
	}
	public static Integer depthSum(List<Object> list) {
		Integer sum = 0;
		sum += depthsumHelper(list, 1);

		return sum;
	}
	
	public static void main(String[] args) {
		List<Object> list_one = new ArrayList<Object>();
		List<Object> list_two = new ArrayList<Object>();
		List<Object> list_three = new ArrayList<Object>();

		list_one.add(new Integer(1));
		list_one.add(new Integer(2));
		list_two.add(new Integer(3));
		list_two.add(new Integer(4));
		list_three.add(new Integer(5));
		list_three.add(new Integer(6));
		list_one.add(list_two);
		list_two.add(list_three);
		list_one.add(2);
		System.out.println(list_one);

		System.out.println(DFS.depthSum(list_one));
	}
}
