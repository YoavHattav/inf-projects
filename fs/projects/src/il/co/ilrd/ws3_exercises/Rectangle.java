package il.co.ilrd.ws3_exercises;

public class Rectangle extends shape{
	
	double width;
	double length;
	
	Rectangle() {
		width = 1.0;
		length = 1.0;
	}
	
	Rectangle(double width, double length) {
		this.width = width;
		this.length = length;
	}
	
	Rectangle(double width, double length, String color, boolean filled) {
		this.width = width;
		this.length = length;
	}
	
	public double getWidth() {
		return width;
	}

	public void setWidth(double width) {
		this.width = width;
	}

	public double getLength() {
		return length;
	}

	public void setLength(double length) {
		this.length = length;
	}

	@Override
	public double getPerimeter() {
		return (width + length)*2;
	}

	@Override
	public double getArea() {
		return width*length/2;
	}

	@Override
	public String toString() {
		return "A rectangle with width =" + width + " and lenght = " + length +
				"which is a subclass of " + super.toString();
	}
}
