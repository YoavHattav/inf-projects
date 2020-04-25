package il.co.ilrd.factory;

public class Cat extends Animal{
	
	String color;
	public Cat() {
		super();
		color = "blue";
	}

	@Override
	public String whatAmI(String I) {
		return (I + "Cat");
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	static void scrach() {
		System.out.println("ouch cat");
	}

}
