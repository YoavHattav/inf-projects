package exercises;

public abstract class shape {
	
	String color;
	boolean filled;
	
	shape() {
		color = "green";
		filled = true;
	}
	shape(String color, boolean filled) {
		this.color = color;
		this.filled = filled;
	}
	public String getColor() {
		return color;
	}
	public void setColor(String color) {
		this.color = color;
	}
	public boolean isFilled() {
		return filled;
	}
	public void setFilled(boolean filled) {
		this.filled = filled;
	}
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "A shape with color " + color + " and " + (isFilled() == true ? "filled" : "not filled");
	}
	
	abstract public double getArea();
	abstract public double getPerimeter();
}
