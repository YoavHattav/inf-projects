package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.concurrent.Semaphore;

public class ProdCons3_2_2 {
	
	static LinkedList<Integer> list = new LinkedList<Integer>();
	private final static Semaphore sem_1 = new Semaphore(0);
	static final int num_of_threads = 5;
	Integer number = 5;
	
	public class Producer implements Runnable {
		@Override
		public void run() {
			synchronized (ProdCons3_2_2.this) {
				System.out.println("add");
				list.add(++number);
				sem_1.release();
			}
		}
	}
	public class Consumer implements Runnable {
		@Override
		public void run() {
			
			try {
				sem_1.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			synchronized (ProdCons3_2_2.this) {
				System.out.println("remove " + list.remove());
			}
		}
	}
	public static void main(String[] args) {
		
		for (int i = 0; i < num_of_threads; ++i)
		{
			(new Thread(new ProdCons3_2_1().new Consumer())).start();
			(new Thread(new ProdCons3_2_1().new Producer())).start();
		}
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
