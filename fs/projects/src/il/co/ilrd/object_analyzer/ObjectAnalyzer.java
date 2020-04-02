package il.co.ilrd.object_analyzer;

import java.lang.reflect.*;

public class ObjectAnalyzer implements Runnable{
	
	int instance_yoav = 5;
	static int static_yoav = 6;
	static final int STATIC_FINAL_YOAV = 7;
	private int private_yoav = 8;
	public int public_yoav = 9;
	
	@Override
	public void run() {
		
	}
	
	public int getPrivate_yoav() {
		return private_yoav;
	}

	public void setPrivate_yoav(int private_yoav) {
		this.private_yoav = private_yoav;
	}
	
	public static void main(String[] args) {
		Class c = (new ObjectAnalyzer()).getClass();
		System.out.println("the class is: " + c);
		System.out.println("class modifier: " + Modifier.toString(c.getModifiers()));
		java.lang.reflect.Type[] intfs = c.getGenericInterfaces();
	    if (intfs.length != 0) {
		for (java.lang.reflect.Type intf : intfs)
		    System.out.println("implemented interface: " + intf.toString());
	    }
	    
	    Field[] fields = c.getDeclaredFields();
        for(int i = 0; i < fields.length; i++) {
           System.out.println("Field = " + fields[i].toString());
        }
        c = c.getSuperclass();
		System.out.println("superclass of this one is: " + c);
		
		ObjectAnalyzer new_obj = new ObjectAnalyzer();
		System.out.println(new_obj.getPrivate_yoav());
	}
}
