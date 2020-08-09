package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.Collections;

public class GreaterThanNumEqul2NumInArray {
	public int solve(ArrayList<Integer> list) {
		Collections.sort(list);
		int i = 1;
		for (Integer curr : list) {
			if ((list.size() - i) == curr) {
				System.out.println(curr);
				return 1;
			}
			++i;
		}
		return -1;
	}
	public static void main(String[] args) {
		ArrayList<Integer> list = new ArrayList<>();
		list.add(1);
		list.add(2);
		list.add(3);
		list.add(4);
		list.add(5);
		list.add(6);

		System.out.println((new GreaterThanNumEqul2NumInArray()).solve(list));
		

	}

}
