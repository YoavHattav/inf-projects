package il.co.ilrd.concurrency;

import java.util.concurrent.*;

public class ProdCons3_1_2 {
	
	volatile static int x = 0;
	volatile static boolean flag = true;
	
	private final static Semaphore sem_1 = new Semaphore(1);
	private final static Semaphore sem_2 = new Semaphore(0);
	
	public class Consumer implements Runnable {
		@Override
		public void run() {
			while (flag)
			{
				try {
					sem_1.acquire();
					
				} catch(InterruptedException e) {
					e.printStackTrace();
				}
				
				System.out.println("pong");
				sem_2.release();
			}
		}
	}
	public class Producer implements Runnable {
		@Override
		public void run() {
			while (flag)
			{
				try {
					sem_2.acquire();
					
				} catch(InterruptedException e) {
					e.printStackTrace();
				}
				
				System.out.println("ping");
				sem_1.release();
			}
		}
	}
	static void stopFlag() {
		flag = false;
		System.out.println("stop that!");
	}
	public static void main(String[] args) {
		Producer ping = new ProdCons3_1_2().new Producer();
		Consumer pong = new ProdCons3_1_2().new Consumer();
		
		Thread thread_pro = new Thread(ping);
		Thread thread_cons = new Thread(pong);
		
		thread_pro.start();
		thread_cons.start();
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		stopFlag();
	}
}
