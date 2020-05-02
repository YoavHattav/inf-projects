package il.co.ilrd.concurrent;

import java.util.Comparator;
import java.util.Queue;
import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;

import il.co.ilrd.collections.WaitableQueue;

public class ThreadPool {
	
	static final int STOP = 0;
	static final int PAUSE = 4;
	
	private int totalThreads;
	private WaitableQueue<Task<?>> queue;
	private Queue<WorkerThread> threadPool;
	private volatile boolean shtDFlag = false;
	
	public ThreadPool(int totalThreads) {
		this.totalThreads = totalThreads;
		queue = new WaitableQueue<Task<?>>();
		
		for (int i = 0; i < this.totalThreads; ++i) {
			WorkerThread obj = new WorkerThread();
			obj.start();
		}
	}
	
	public enum Priority {
		LOW  (1),
		MID  (2),
		HIGH (3);
		
		private int priority;
		
		Priority(int priority) {
			this.priority = priority;
		}
		public int getPriority() {
			return priority;
		}
	}
	
	private static class WorkerThread extends Thread {
		
		boolean run_flag = true;
		
		@Override
		public void run() {
			while (run_flag) {
				queue.dequeue
			}
		}
		
	}
	
	private static class Task <T>{
		private int priority;
		private FutureTask<T> future;
		private Callable<T> cb; //turn runnable to callable
		
		public Task(int priority, Callable<T> cb) {
			this.priority = priority;
			future = new FutureTask<T>(cb);
			this.cb = cb;
		}			
	}
	/*
	public class PairCompare<T extends Comparable<T>> implements Comparator<T> {

		@Override
		public int compare(T o1, T o2) {
			if (o1.compareTo(o2) > 0)
			{
				return 1;
			}
			return 0;
		}
	}*/
	
	public Future<Object> submit(Runnable r, Priority p) {
		Task<Object> task = new Task<>(p.getPriority(), Executors.callable(r));
		if (!shtDFlag)
		{
			queue.enqueue(task);
		}
		
		
		return task.future;
	}
	
	public <T> Future<T> submit(Runnable r, Priority p, T value) {
		Task<T> task = new Task<>(p.getPriority(), Executors.callable(r));
		queue.enqueue(task);
		
		return task.future;
	}
	
	public <T> Future<T> submit(Callable<T> cb) {
	//	Task<Object> task = new Task<>(, Executors.callable(r));

		return null;
	}
	
	public <T> Future<T> submit(Callable<T> cb, Priority p) {
		return null;
	}
	
	public void setNumOfThreads(int num) {
		if (totalThreads > num) {
			for (int i = 0; i < (totalThreads - num); ++i) {
				WorkerThread obj = new WorkerThread();
				obj.start();
			}
		}
		else if (num > totalThreads) {
			Callable<Object> cb = new Callable<Object>() {
				
				@Override
				public Object call() throws Exception {
					threadPool.add((WorkerThread)Thread.currentThread());
					((WorkerThread)Thread.currentThread()).run_flag = false;
					return null;
				}
			};
			Task<Object> shut_down = new Task<Object>(STOP, cb);
			for (int i = 0; i < (num - totalThreads); ++i) {
				queue.enqueue(shut_down);
			}
		}
	}
	
	public void shutdown() {
		Callable<Object> cb = new Callable<Object>() {
			
			@Override
			public Object call() throws Exception {
				threadPool.add((WorkerThread)Thread.currentThread());
				((WorkerThread)Thread.currentThread()).run_flag = false;
				return null;
			}
		};
		Task<Object> shut_down = new Task<Object>(STOP, cb);
		for (int i = 0; i< totalThreads; ++i) {
			queue.enqueue(shut_down);
		}
		shtDFlag = true;
	}
	
	public void awaitTermination(int timeInSec, TimeUnit unit) throws IllegalStateException {
		for (int i = 0; i < totalThreads; ++i) {
			try {
				threadPool.remove().join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public void pause() {
		Callable<Object> cb = new Callable<Object>() {
			
			@Override
			public Object call() throws Exception {
				wait();
				return null;
			}
		};
		Task<Object> pause_task = new Task<Object>(PAUSE, cb);
		for (int i = 0; i< totalThreads; ++i) {
			queue.enqueue(pause_task);
		}
	}
	
	public void resume() {
		notifyAll();
	}
}