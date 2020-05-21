package il.co.ilrd.quizzes;

import java.util.PriorityQueue;

public class MedienQ {
	PriorityQueue<Integer> queue = new PriorityQueue<Integer>();
	Integer[] array = null;
	public void add(Integer num) {
		queue.add(num);
	}
	public float getMedien() {
		float medien;
		int length = queue.size();
		array = new Integer[length];
		queue.toArray(array);
		if (length % 2 == 0) {
			medien = (float)(array[length / 2] + array[(length / 2) - 1]) / 2;
		}
		else {
			medien = (float)array[length / 2];
		}
		for (Integer i : queue) {
			System.out.print(i);
		}
		System.out.println("");
		return medien;
	}
	public static void main(String[] args) {
		MedienQ medienQ = new MedienQ();
		medienQ.add(1);
		medienQ.add(2);
		medienQ.add(3);
		medienQ.add(4);
		medienQ.add(5);
		medienQ.add(6);
		medienQ.add(7);
		
		medienQ.add(8);
		medienQ.add(9);
		medienQ.add(10);
		medienQ.add(2);
		medienQ.add(2);
		medienQ.add(2);

		medienQ.add(11);
		medienQ.add(12);
		medienQ.add(13);
		medienQ.add(14);
		System.out.println(medienQ.getMedien());
	}
}
