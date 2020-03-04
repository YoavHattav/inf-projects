package exercises;

public class Circle extends shape{
	double radius;
	Circle() {
		radius = 1.0;
	}
	
	Circle(double radius) {
		this.radius = radius;
	}
	
	Circle(double radius, String color, boolean filled) {
		this.radius = radius;
	}

	public double getRadius() {
		return radius;
	}

	public void setRadius(double radius) {
		this.radius = radius;
	}
	
	@Override
	public double getPerimeter() {
		return Math.PI*this.radius*2;
	}

	@Override
	public double getArea() {
		return Math.PI*(radius*radius);
	}

	@Override
	public String toString() {
		return "A circle with radius =" + radius + " which is a subclass of " + super.toString();
	}
}
