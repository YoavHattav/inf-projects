package il.co.ilrd.quizzes;

public class WaitMyNotify {
	String lock = "";
	boolean flag = false;
	
	public void func() {
		synchronized (lock) {
			while (!flag) {
				try {
					System.out.println("first");
					lock.wait();
				} catch (Exception e) {
					// TODO: handle exception
				}
			}
			flag = false;
		}
	}
	public void func2() {
		synchronized (lock) {
			flag = true;
			lock.notify();
		}
	}
	public static void main(String[] args) {
		WaitMyNotify m = new WaitMyNotify();
		m.func();
		m.func2();
	}

}
