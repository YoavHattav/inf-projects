package il.co.ilrd.concurrent;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import org.junit.jupiter.api.Test;

import il.co.ilrd.concurrent.ThreadPool.Priority;

class ThreadPoolTest {

	
	/*@Test
	void test1() {
		ThreadPool tp = new ThreadPool(10);
		Callable<Object> cb1 = new Callable<Object>() {
			
			@Override
			public Object call() throws Exception {
				return "hey there";
			}
		};
		Callable<Object> cb2 = new Callable<Object>() {
			
			@Override
			public Object call() throws Exception {
				return "stranger";
			}
		};
		Runnable rn1 = new Runnable() {
			
			@Override
			public void run() {
				System.out.println("im running");
			}
		};
		
		tp.submit(cb2, Priority.HIGH);
		Future<Object> f1 = tp.submit(cb1);
		Future<Object> f2 = tp.submit(cb2, Priority.HIGH);
		Future<Object> f3 = tp.submit(rn1, Priority.HIGH);
		
		String value = "runnable with T value";
		Future<Object> f4 = tp.submit(rn1, Priority.HIGH, value);

		
		try {
			System.err.println((String)f1.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		try {
			System.err.println((String)f2.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		try {
			System.err.println((String)f3.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		try {
			System.err.println((String)f4.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		
		tp.shutdown();
		try {
			Future<Object> f5 = tp.submit(cb1);
		} catch (Exception e) {
			System.out.println(e);
		}
	}*/
	
	
	@Test
	void test2() {
		ThreadPool tp = new ThreadPool(10);
		Callable<Object> cb1 = new Callable<Object>() {
			
			@Override
			public Object call() throws Exception {
				return "hey there";
			}
		};
		Callable<Object> cb2 = new Callable<Object>() {
			
			@Override
			public Object call() throws Exception {
				return "stranger";
			}
		};
		Runnable rn1 = new Runnable() {
			
			@Override
			public void run() {
				System.out.println("im running");
			}
		};
		
		tp.pause();
		
		Future<Object> f1 = tp.submit(cb1);
		Future<Object> f2 = tp.submit(cb2, Priority.HIGH);
		Future<Object> f3 = tp.submit(rn1, Priority.HIGH);
		
		String value = "runnable with T value";
		Future<Object> f4 = tp.submit(rn1, Priority.HIGH, value);
		
		System.out.println("before resume");
		
		if (f1.isDone())
			{
				try {
					System.err.println((String)f1.get());
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (ExecutionException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		f1.cancel(true);
		
		tp.resume();
		
		if (!f1.isCancelled())
		{
			try {
				System.err.println((String)f1.get());
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (ExecutionException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		try {
			System.err.println((String)f2.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		try {
			System.err.println((String)f3.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		try {
			System.err.println((String)f4.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
	}
	
	@Test
	void test3() {
		ThreadPool tp = new ThreadPool(10);
		
		Runnable rn_high = new Runnable() {
			
			@Override
			public void run() {
				
				System.out.println("im running fast" + Thread.currentThread().getId());
			}
		};
		Runnable rn_low = new Runnable() {
			
			@Override
			public void run() {
				final long one_sec = 1000;
				
					try {
						Thread.sleep(one_sec);
					} catch (InterruptedException e) {
						e.printStackTrace();
					};
				
				System.out.println("im running slow" + Thread.currentThread().getId());
			}
		};
		Future<Object>[] f3 = new Future[100];
		
		for (int i = 0; i < 20; ++i)
		{
			f3[i] = tp.submit(rn_low, Priority.LOW, "get low");
		}
		for (int i = 20; i < 40; ++i)
		{
			f3[i] = tp.submit(rn_high, Priority.HIGH, "get high");
		}
		
		tp.pause();
		
		for (int i = 0; i < 100; ++i) {
			System.out.print("h");
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		tp.resume();
		
		try {
			for (int i = 0; i < 40; ++i)
			{
				System.out.println(f3[i].get());
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		
		tp.shutdown();
		
		try {
			tp.awaitTermination(10, TimeUnit.MILLISECONDS);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("needs to be after 'shut down' ");
	}
	
	@Test
	void test_set_number_of_threads() {
		ThreadPool tp = new ThreadPool(10);
		System.out.println("you currently have " + tp.getTotalNumOfThreads() + " threads in the pool");
		tp.setNumOfThreads(12);
		System.out.println("you currently have " + tp.getTotalNumOfThreads() + " threads in the pool");
		tp.setNumOfThreads(3);
		System.out.println("you currently have " + tp.getTotalNumOfThreads() + " threads in the pool");
	}
}
