package il.co.ilrd.quizzes;

import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;

import il.co.ilrd.collections.HashMap;

public class TopKFrequent {
	Map<Integer, Integer> map = new HashMap<>();
	Queue<Integer> queue = new PriorityQueue<>();
	int[] counter;
	public int[] topKFrequent(int[] array, int k) {
		counter = new int[k];
		for (int num : array) {
			if (map.containsKey(num) == true) {
				int temp = map.get(num) + 1;
				map.put(num, temp);
			}
			else {
				map.put(num, 1);
			}
		}
		for (Integer num : map.values()) {
			queue.add(num);
		}
		for (int i = 0; i < k; ++i) {
			counter[i] = queue.remove();
		}
		return counter;
	}
	
	public static void main(String[] args) {
		TopKFrequent obj = new TopKFrequent();
		int[] array = {0,1,1,1,1,2,2,2,2,2,4,4,5,56,6,4,4,4,4,4};
		int [] result = obj.topKFrequent(array, 3);
		for (int i : result) {
			System.out.println(i);
		}
	}

}
