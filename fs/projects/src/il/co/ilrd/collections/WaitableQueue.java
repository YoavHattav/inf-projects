package il.co.ilrd.collections;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.TimeUnit;
	
public class WaitableQueue<E> {
	private Queue<E> queue;
	private  final int DEFAULT_CAPACITY; 
	
	public WaitableQueue() {
		DEFAULT_CAPACITY = 11; 
		queue = new PriorityQueue<>(DEFAULT_CAPACITY);
	}
	
	public WaitableQueue(int DEFAULT_CAPACITY, Comparator<E> comparator) {
		this.DEFAULT_CAPACITY = DEFAULT_CAPACITY;
		queue = new PriorityQueue<E>(DEFAULT_CAPACITY,comparator);
	}
	
	/**
	 * add the element given to the queue
	 * @param element
	 */
	public void enqueue(E element) {
		synchronized(this) {
			try {
				queue.add(element);
				
			} catch (ClassCastException e) { 
				System.out.println("ClassCastException");
			
			} catch (NullPointerException n) {
				System.out.println("NullPointerException");
			}
			
			notify();
		}	
	}
	
	/**
	 * blocking if the queue is empty, will return E element
	 * @return the element dequeued
	 * @throws InterruptedException
	 */
	public  synchronized E dequeue() throws InterruptedException {
		while (queue.isEmpty()) {
				wait();
		}
		
		return queue.remove();
	}
	
	/**
	 * blocking if the queue is empty for maximum of timeInSeconds seconds 
	 * @param timeInSeconds
	 * @return E element or null if the waiting time ends
	 * @throws InterruptedException
	 */
	public E dequeueWithTimeout(long timeInMillSeconds,  TimeUnit unit) throws InterruptedException{
		long startTime = System.currentTimeMillis();
		while (unit.toSeconds(timeInMillSeconds) > System.currentTimeMillis() - startTime) {
			synchronized(this) {
				if(!queue.isEmpty()) {
					return queue.remove();
				}	
			}
		}
		
		return null;
	}
}
