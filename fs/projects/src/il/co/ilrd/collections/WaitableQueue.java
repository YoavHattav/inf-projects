package il.co.ilrd.collections;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class WaitableQueue<E>{
	private Queue<E> queue;
	private final Semaphore sem = new Semaphore(0);
	
	public WaitableQueue(Comparator<E> compare) {
		queue = new PriorityQueue<>(compare);
	}
	
	public WaitableQueue() {
		this(new Comparator<>());
	}
	/**
	 * 
	 * synchronized on ???
	 * @return
	 */
	public void enqueue(E element) {
		
		//sem.release();
		
	}
	/**
	 * blocking if the queue is empty, will return E element
	 * @return
	 * @throws InterruptedException 
	 */
	public E dequeue() throws InterruptedException {
		
		//sem.acquire();
		
		return null;
	}
	//blocking if the queue is empty for maximum of timeInSeconds seconds,
	//will return E element or null timeout 
	public E dequeueWithTimeot(int timeInSeconds) throws InterruptedException{
		return null;
	}
}
