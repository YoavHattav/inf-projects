package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class ProdCons3_3 {
	
	private final static Semaphore sem_1 = new Semaphore(0);
	static int data = 0;
	static Object lock = new Object();
	static final int num_of_threads = 5;

	public class Consumer implements Runnable {
		@Override
		public void run() {
			
		}
	}
	public class Producer implements Runnable {
		@Override
		public void run() {
			
		}
	}
	public static void main(String[] args) {
		
		for (int i = 0; i < num_of_threads; ++i)
		{
			(new Thread(new ProdCons3_2_1().new Consumer())).start();
		}
		(new Thread(new ProdCons3_2_1().new Producer())).start();
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
