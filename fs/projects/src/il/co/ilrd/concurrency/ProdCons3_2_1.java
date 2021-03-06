package il.co.ilrd.concurrency;

import java.util.LinkedList;

public class ProdCons3_2_1 {
	
	static LinkedList<Integer> list = new LinkedList<Integer>();
	Integer number = 5;
	
	public class Consumer implements Runnable {
		@Override
		public void run() {
			synchronized (ProdCons3_2_1.this) {
				System.out.println("add");
				list.add(number);
			}
		}
	}
	public class Producer implements Runnable {
		@Override
		public void run() {
			
		while (list.isEmpty()){}
			synchronized (ProdCons3_2_1.this) {
				System.out.println("remove " + list.remove());
			}
		}
	}
	public static void main(String[] args) {
		final int num_of_threads = 5;
		
		for (int i = 0; i < num_of_threads; ++i)
		{
			(new Thread(new ProdCons3_2_1().new Consumer())).start();
			(new Thread(new ProdCons3_2_1().new Producer())).start();
		}
		
		
		try {
			Thread.sleep(100000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
