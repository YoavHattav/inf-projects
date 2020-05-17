package il.co.ilrd.quizzes;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;

public class ReadersWriters {
	private Lock lock;
	private final static Semaphore sem = new Semaphore(30);
	
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
	public void StartWrite() {
		lock.lock();
		for (int i = 0; i < 30; ++i) {
			try {
				sem.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	public void EndWrite() {
		for (int i = 0; i < 30; ++i) {
			sem.release();
		}
		lock.unlock();
	}
}


