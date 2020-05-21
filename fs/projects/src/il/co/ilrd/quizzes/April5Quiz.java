package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.List;

public class April5Quiz {
	//was April5Quiz<T> in the quiz.. made it string for it to compile.

	public void printFall(List<String> list) {
		System.out.println(list.toString());
	}
	
	public static void main(String[] args) {
		//was April5Quiz<Object> in the quiz.. made it string for it to compile.
		April5Quiz ap = new April5Quiz();
		List<String> list = new ArrayList<String>();
		ap.printFall(list);
	}
}
