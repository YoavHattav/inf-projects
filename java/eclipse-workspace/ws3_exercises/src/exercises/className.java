package exercises;

public class className {

	public static void main(String[] args) {
	
		Class cls;
			
		try {
			cls = Class.forName(args[0]);
		    System.out.println("Name: " + cls.getName());
		    System.out.println("class: " + args[0]);
		    System.out.println("classes: " +cls.getClasses());
		    System.out.println("annotations: " + cls.getAnnotations());
		    System.out.println("constructor: " + cls.getConstructors());
		    System.out.println("Feilds: " + cls.getFields());
		    System.out.println("Methods: " + cls.getMethods());
		    System.out.println("modifiers: " + cls.getModifiers());
				   
		} catch (ClassNotFoundException e) {
		
		e.printStackTrace();
		}
	 
	 
	}

}