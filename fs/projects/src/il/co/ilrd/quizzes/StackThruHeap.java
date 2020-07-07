package il.co.ilrd.quizzes;

import java.util.PriorityQueue;
import java.util.Queue;

public class StackThruHeap<E> {
	private Integer counter = 0;
	Queue<StackPair> queue = new PriorityQueue<>();
	class StackPair implements Comparable<StackPair>{
		private E data;
		private Integer order;
		
		public StackPair(E data, Integer order) {
			this.data = data;
			this.order = order;
		}

		@Override
		public int compareTo(StackPair arg0) {
			if (this.order > arg0.order) {
				return -1;
			}
			else if (this.order < arg0.order) {
				return 1;
			}
			return 0;
		}
	}
	public void push(E data) {
		queue.add(new StackPair(data, ++counter));
	}
	public E pop() {
		if (queue.isEmpty()) {
			return null;
		}
		return queue.poll().data;
	}
	public static void main(String[] args) {
		StackThruHeap<Integer> stack = new StackThruHeap<Integer>();
		stack.push(1);
		stack.push(2);
		stack.push(3);
		stack.push(4);
		stack.push(5);
		System.out.println(stack.pop());
		System.out.println(stack.pop());
		System.out.println(stack.pop());

	}
}
