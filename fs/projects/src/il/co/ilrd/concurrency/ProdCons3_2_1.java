package il.co.ilrd.concurrency;

import java.util.LinkedList;

public class ProdCons3_2_1 {
	
	LinkedList<Integer> list = new LinkedList<Integer>();
	Object lock = new Object();
	Integer number = 5;
	
	public class Consumer implements Runnable {
		@Override
		public void run() {
			while (true)
			{
				synchronized (lock) {
					System.out.println("add");
					list.add(number);
				}
			}
		}
	}
	public class Producer implements Runnable {
		@Override
		public void run() {
			while (true)
			{
				while (list.isEmpty())
				{
					synchronized (lock) {
						System.out.println("remove" + list.remove());
					}
				}
			}
			
		}
	}
	public static void main(String[] args) {
		final int num_of_threads = 5;
		
		for (int i = 0; i < num_of_threads; ++i)
		{
			(new Thread(new ProdCons3_2_1().new Consumer())).start();
		}
		for (int i = 0; i < num_of_threads; ++i)
		{
			(new Thread(new ProdCons3_2_1().new Producer())).start();
		}
		//Producer ping = new ProdCons3_2_1().new Producer();
		//Consumer pong = new ProdCons3_2_1().new Consumer();
		
		//Thread thread_pro = new Thread(ping);
		//Thread thread_cons = new Thread(pong);
		
		//thread_pro.start();
		//thread_cons.start();
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
