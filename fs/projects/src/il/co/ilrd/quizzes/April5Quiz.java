package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.List;

public class April5Quiz<T> {
	
	public void printFall(List<T> list) {
		System.out.println(list.toString());
	}
	
	public static void main(String[] args) {
		April5Quiz<Object> ap = new April5Quiz<Object>();
		List<String> list = new ArrayList<String>();
		ap.printFall(list);
	}
}
