package il.co.ilrd.crud;

public class CrudTest {
	public static void main(String[] args) {
		
		FileObserver file_observer = new FileObserver("/home/yoav/Desktop/output.txt");
		FileMonitor monitor = new FileMonitor("/var/log/syslog");
		
		monitor.addObserver(file_observer);
		monitor.start();
		
		try {
			Thread.sleep(20000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		monitor.stop();
		file_observer.close();
	}
}