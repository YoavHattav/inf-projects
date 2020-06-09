package il.co.ilrd.crud;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class SQLCrud implements GenericCrud<String, Integer>{
	Connection myCon;
	private String url;
	private String user;
	private String password;
	String station_id = "3";
	ResultSet resultSet = null;
	boolean flag = true;
	
	public SQLCrud(String url, String user, String password) {
		this.url = url;
		this.user = user;
		this.password = password;
		try {
			myCon = DriverManager.getConnection(url, user, password);
			myCon.setAutoCommit(false);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void close() throws Exception {
		flag = false;
		myCon.close();
	}

	public Integer create(String msg) {
		PreparedStatement stmt = null;
		Integer id = null;
		String newMsg = msg.replaceAll("'", "");
		try {
			String sql = "INSERT INTO file_log (station_id, data) VALUES ('" + 
							station_id + 
							"', '" + 
							newMsg +
							"')";
			stmt = myCon.prepareStatement(sql);
			stmt.execute();
			sql = "SELECT MAX(id) FROM file_log WHERE station_id = " + station_id;
			resultSet = stmt.executeQuery(sql);
			
			if (resultSet.next() && flag && resultSet != null){
				id = (Integer) resultSet.getInt("MAX(id)");
			}
			myCon.commit();
		} catch (SQLException e) {
			try {
				myCon.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			System.out.println(newMsg);
			e.printStackTrace();
		}

		return id;
	}
	@Override
	public String read(Integer key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void update(Integer key, String obj) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public String delete(Integer key) {
		// TODO Auto-generated method stub
		return null;
	}

	
	
}
