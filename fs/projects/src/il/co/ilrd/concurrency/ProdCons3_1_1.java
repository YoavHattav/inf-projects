package il.co.ilrd.concurrency;

public class ProdCons3_1_1 {
	
	volatile static int x = 0;
	volatile static boolean flag = true;
	
	public class Consumer implements Runnable {
		@Override
		public void run() {
			while (flag)
			{
				if (1 == x)
				{
					System.out.println("pong");
					--x;
				}
			}
		}
	}
	public class Producer implements Runnable {
		@Override
		public void run() {
			while (flag)
			{
				if (0 == x)
				{
					System.out.println("ping");
					++x;
				}
			}
		}
	}
	static void stopFlag() {
		flag = false;
		System.out.println("stop that!");
	}
	public static void main(String[] args) {
		Producer ping = new ProdCons3_1_1().new Producer();
		Consumer pong = new ProdCons3_1_1().new Consumer();
		
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
