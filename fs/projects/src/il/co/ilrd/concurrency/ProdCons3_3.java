package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class ProdCons3_3 {
	
	static final int num_of_threads = 5;
	private final static Semaphore sem_1 = new Semaphore(-num_of_threads + 1);
	static int data = 0;
	static Object lock = new Object();

	public class Consumer implements Runnable {
		@Override
		public void run() {
			while (true)
			{
				sem_1.release();
				synchronized (lock)
				{
					try
					{
						lock.wait();
						System.out.println("consumer reads: "+ data);
				
					}
					catch (InterruptedException e)
					{
							e.printStackTrace();
					}
				}
			}	
		}	
	}
		
	public class Producer implements Runnable {
		@Override
		public void run() {
			while (true)
			{
				try
				{
					sem_1.acquire();
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
				synchronized(lock)
				{
					++data;
					System.out.println("producer: " + data);
					lock.notifyAll();
				}
			}		
		}		
	}
	public static void main(String[] args) {
		
		for (int i = 0; i < num_of_threads; ++i)
		{
			(new Thread(new ProdCons3_3().new Consumer())).start();
		}
		(new Thread(new ProdCons3_3().new Producer())).start();
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
