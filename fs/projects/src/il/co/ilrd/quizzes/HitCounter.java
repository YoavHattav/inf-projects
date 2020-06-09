package il.co.ilrd.quizzes;

import java.util.PriorityQueue;
import java.util.Queue;

public class HitCounter {
	Queue<Hit> queue = new PriorityQueue<Hit>();
	
	public void record(Hit value) {
		queue.add(value);
	}
	public int total() {
		return queue.size();
	}
	public int range(Integer upper, Integer lower) {
		int counter = 0;
		for (Hit current : queue) {
			if ((current.compareTo(upper) < 0) && (current.compareTo(lower) < 0)) {
				++counter;
			}
		}
		return counter;
	}
	static class Hit implements Comparable<Integer> {
		Integer timeStamp = 0;
		
		public Hit(Integer time) {
			this.timeStamp = time;
		}

		@Override
		public int compareTo(Integer arg0) {
			if (this.timeStamp > arg0) {
				return 1;
			}
			else if (this.timeStamp < arg0) {
				return -1;
			}
			return 0;
		}
	}
}
