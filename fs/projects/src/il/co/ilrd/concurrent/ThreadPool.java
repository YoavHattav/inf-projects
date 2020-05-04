package il.co.ilrd.concurrent;

import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.collections.WaitableQueue;

public class ThreadPool {

	private volatile int totalThreads;
	private WaitableQueue<Task<?>> queue;
	private LinkedBlockingQueue<WorkerThread> threadPool = new LinkedBlockingQueue<>();
	private volatile boolean shtDFlag = false;
	private volatile boolean pause_flag = false;
	private volatile int pause_counter = 0;
	private Semaphore sem = new Semaphore(0);
	
	public ThreadPool(int totalThreads) {
		this.totalThreads = totalThreads;
		queue = new WaitableQueue<Task<?>>();
		
		for (int i = 0; i < this.totalThreads; ++i) {
			WorkerThread obj = new WorkerThread(queue);
			obj.start();
		}
	}
	
	public enum Priority {
		LOW  (1),
		MID  (2),
		HIGH (3);
		
		private int priority;
		
		private Priority(int priority) {
			this.priority = priority;
		}
		public int getPriority() {
			return priority;
		}
	}

	private static class WorkerThread extends Thread {
	
		private volatile boolean run_flag = true;
		private WaitableQueue<Task<?>> queue;
		
		public WorkerThread(WaitableQueue<Task<?>> queue) {
			this.queue = queue;
		}
		
		@Override
		public void run() {
			while (run_flag) {
				try {
					Task<?> t = queue.dequeue();
					t.execute();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}

		private void threadStop() {
			run_flag = false;
		}
	}

	private static class Task <T> implements Comparable<Task<T>>{
		private int priority;
		Callable<T> cb = null;
		private FutureImp<T> future = new FutureImp<T>();

		public Task(int priority, Callable<T> cb) {
			this.priority = priority;
			this.cb = cb;
		}

		public void execute() {
			if (!future.isCancelled()) {
				try {
					future.return_value = cb.call();
					future.future_latch.countDown();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}

		@Override
		public int compareTo(Task<T> task_two) {
			return task_two.priority - this.priority;
		}	
	}
	
	private static class FutureImp<E> implements Future<E> {
		private boolean is_done = false;
		private boolean is_caneled = false;
		private E return_value = null;
		private CountDownLatch future_latch = new CountDownLatch(1);
		
		
		@Override
		public boolean cancel(boolean mayInterruptIfRunning) {
			if (isDone()) {
				return is_caneled;
			}
			is_caneled = true;
			is_done = true;
			
			return is_caneled;
		}
		
		/**
		 * @author YH
		 * @return the value of call() return.
		 * @throws InterruptedException
		 */
		@Override
		public E get() throws InterruptedException, ExecutionException {
			if (Thread.interrupted()) {
				 throw new CancellationException("the task could not complete");
			}
			if (isCancelled()) {
				 throw new CancellationException("the task could not complete, it was canceled");
			}
			future_latch.await();
			return return_value;
		}
		
		/**
		 * @author YH
		 * @param timeout the amount of TimeUnit to wait for the termination
		 * @param the time unit in which to count the timeout argument
		 * @return the value of call() return.
		 * @throws InterruptedException
		 */
		@Override
		public E get(long timeout, TimeUnit unit)
				throws InterruptedException, ExecutionException, TimeoutException {
			if (isCancelled()) {
				 throw new CancellationException("the task could not complete, it was canceled");
			}
			if(future_latch.await(timeout, unit)) {
				return return_value;
			}
			return null;
		}
		
		/**
		 * @return a boolean indicating whether the execution was canceled.
		 */
		@Override
		public boolean isCancelled() {return (is_caneled == true);}
		
		/**
		 * @return a boolean indicating whether the execution has finished successfully.
		 */
		@Override
		public boolean isDone() {return (is_done == true);}	
	}
	
	private class ShutDown implements Callable<Object> {
		
		@Override
		public Object call() throws Exception {
			threadPool.add((WorkerThread)Thread.currentThread());
			((WorkerThread)Thread.currentThread()).threadStop();
			return null;
		}
	}
	
	/**
	 * @author YH
	 * @return the number of working threads in the pool
	 */
	public Integer getTotalNumOfThreads() {
		return new Integer(totalThreads);
	}
	
	/**	 
	 * @author YH
	 * @param r a runnable method to be executed
	 * @param p the priority this executable will have over other executables in the queue
	 * @return a Future<object> holding the return value
	 */
	public Future<Object> submit(Runnable r, Priority p) throws RejectedExecutionException {
		return submit(Executors.callable(r), p);
	}
	
	/**
	 * @author YH
	 * @param r a runnable method to be executed
	 * @param p the priority this executable will have over other executables in the queue
	 * @param value the return value of the runnable method given
	 * @return a Future<object> holding the return value
	 */
	public <T> Future<T> submit(Runnable r, Priority p, T value) throws RejectedExecutionException {
		return submit(Executors.callable(r, value), p);	
	}
	
	/**
	 * @author YH
	 * @param cb a callable method to be executed
	 * @return a Future<object> holding the return value
	 */
	public <T> Future<T> submit(Callable<T> cb) throws RejectedExecutionException {
		Priority p = Priority.MID;
		return submit(cb, p);
	}
	
	/**
	 * @author YH
	 * @param cb a callable method to be executed
	 * @param p the priority this executable will have over other executables in the queue
	 * @return a Future<object> holding the return value
	 */
	public <T> Future<T> submit(Callable<T> cb, Priority p) throws RejectedExecutionException {
		if (shtDFlag)
		{
			throw new RejectedExecutionException("cant add, shut down in progress");
		}
		Task<T> task = new Task<>(p.getPriority(), cb);
		queue.enqueue(task);
		
		return task.future;
	}
	
	/**
	 * @author YH
	 * @param num the new number of threads running in the pool
	 */
	public void setNumOfThreads(int num) {
		if (num > totalThreads) {
			int current_num_of_threads = totalThreads;
			for (int i = 0; i < (num - current_num_of_threads); ++i) {
				WorkerThread obj = new WorkerThread(queue);
				obj.start();
				++totalThreads;
			}
		}
		else if (num < totalThreads) {
			int current_num_of_threads = totalThreads;
			for (int i = 0; i < (current_num_of_threads - num); ++i) {
				queue.enqueue(new Task<Object>(Priority.HIGH.getPriority() + 1, () -> {
					threadPool.add((WorkerThread)Thread.currentThread());
					((WorkerThread)Thread.currentThread()).threadStop();
					return null;
				}));
				--totalThreads;
			}
		}
	}
	/**
	 * @author YH
	 * disables enqueueing new tasks and causing the threads to finish execution
	 */
	public void shutdown() {
		for (int i = 0; i < totalThreads; ++i) {
			queue.enqueue(new Task<Object>(Priority.LOW.getPriority() - 1, () -> {
				threadPool.add((WorkerThread)Thread.currentThread());
				((WorkerThread)Thread.currentThread()).threadStop();
				return null;
			}));
		}
		shtDFlag = true;
	}
	
	/**
	 * @author YH
	 * @param timeInSec the amount of seconds to wait for the termination
	 * @param unit the time unit in which to count the waiting time
	 * @return true- if succeeded in waiting for the threads, false- if could not join() or caught InterruptedException
	 * @throws InterruptedException
	 */
	public boolean awaitTermination(long timeInSec, TimeUnit unit) throws InterruptedException {
		long millis = System.currentTimeMillis() + unit.toMillis(timeInSec);
		while (!threadPool.isEmpty()) {
			long current = millis - System.currentTimeMillis();
			if(current > 0) {
				try {
					Thread thread = threadPool.poll(current, TimeUnit.MILLISECONDS);
					if(thread != null) {
						thread.join(current);
					}
					else { return false; }
				} catch (InterruptedException e) {
					return false;
				}
			}
			else { return false; }
		}
		return true;
	}
	
	/**
	 * @author YH
	 * pauses the execution of tasks
	 */
	public void pause() {
		if (!pause_flag) {
			for (pause_counter = 0; pause_counter < totalThreads; ++pause_counter) {
				queue.enqueue(new Task<Object>(Priority.HIGH.getPriority() + 1, () -> {sem.acquire();
				return null;}));
			}
			pause_flag = true;
		}
	}
	
	/**
	 * @author YH
	 * resumes the execution of tasks after pause
	 */
	public void resume() {
		if (pause_flag) {
				sem.release(pause_counter);
			pause_flag = false;
		}
	}
}