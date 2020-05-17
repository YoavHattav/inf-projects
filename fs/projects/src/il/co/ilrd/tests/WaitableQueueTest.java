package il.co.ilrd.tests;

import org.junit.jupiter.api.Test;

import il.co.ilrd.collections.WaitableQueue;

class WaitableQueueTest {
	
	class Enqueue implements Runnable {
		
		private WaitableQueue<Integer> queue;
		Integer num;
		
		public Enqueue(WaitableQueue<Integer> queue, Integer num) {
			this.queue = queue;
			this.num = num;
		}

		@Override
		public void run() {
			for (int i = 0; i < 600; ++i) {
				queue.enqueue(num);
			}
		}	
	}
	
	class Dequeue implements Runnable {
		
		private WaitableQueue<Integer> queue;
		Integer num;
		
		public Dequeue(WaitableQueue<Integer> queue) {
			this.queue = queue;
		}

		@Override
		public void run() {
			for (int i = 0; i < 600; ++i) {
				try {
					num = queue.dequeue();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
	
	class DequeueWithTime implements Runnable {
		
		private WaitableQueue<Integer> queue;
		private long time_to_wait;
		Integer num;
		
		public DequeueWithTime(WaitableQueue<Integer> queue, long time_to_wait) {
			this.queue = queue;
			this.time_to_wait = time_to_wait;
		}

		@Override
		public void run() {
			
				try {
					num = queue.dequeueWithTimeout(time_to_wait, new TimeU);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
	}
	
	@Test
	void waitableQtest() {
		
		WaitableQueue<Integer> queue = new WaitableQueue<Integer>();
		Thread enque_thread = new Thread(new Enqueue(queue, 5));
		Thread deque_thread = new Thread(new Dequeue(queue));
		Thread timed_deque_thread = new Thread(new DequeueWithTime(queue, 2));
		
		deque_thread.start();
		enque_thread.start();

		try {
			enque_thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		try {
			deque_thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		
		timed_deque_thread.start();
		
		try {
			timed_deque_thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
	}
}
