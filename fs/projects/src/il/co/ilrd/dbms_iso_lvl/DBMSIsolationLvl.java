package il.co.ilrd.dbms_iso_lvl;
import java.sql.*;
public class DBMSIsolationLvl {

	public static void main(String[] args) {
		try {
			// 1. get a connection
			Connection myCon = DriverManager.getConnection("jdbc:mysql://localhost:3306/computers", "root", "ct,h kvmkhj");
			System.out.println(myCon.getTransactionIsolation());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
