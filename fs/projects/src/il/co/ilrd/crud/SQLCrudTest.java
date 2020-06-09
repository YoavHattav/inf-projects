package il.co.ilrd.crud;

public class SQLCrudTest {

	public static void main(String[] args) {
		
		
		FileMonitor monitor = new FileMonitor("/var/log/syslog");
		try (SQLFileObserver crud_file_observer = new SQLFileObserver("jdbc:mysql://localhost:3306/observer", "root", "ct,h kvmkhj")){
			
		monitor.addObserver(crud_file_observer);
		monitor.start();
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		monitor.stop();
	}

}
