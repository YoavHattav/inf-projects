package il.co.ilrd.quizzes;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;

class SyncWritingReading {
	private final Lock lock;
	private Semaphore sem;
	private final int MAX_READERS;
	
	public SyncWritingReading(int MAX_READERS, Lock lock) {
		this.lock = lock;
		this.MAX_READERS = MAX_READERS;
		this.sem = new Semaphore(MAX_READERS);
	}
	
	public void StartWrite() {
		lock.lock();
		while (sem.availablePermits() != MAX_READERS) {}
	}
	
	public void EndWrite() {
		lock.unlock();
	}
	
	public void StartRead() {
		lock.lock();
		try {
			sem.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		lock.unlock();
	}
	
	public void EndRead() {
			sem.release();
	}
}
