package il.co.ilrd.WS3_Exercises;

public class Square extends Rectangle{
	
		
	double side;

	Square() {
		side = 1.0;
	}
	
	Square(double side) {
		this.side = side;
	}
	
	Square(double side, String color, boolean filled) {
		this.side = side;
	}

	public double getSide() {
		return side;
	}

	public void setSide(double side) {
		this.side = side;
	}

	@Override
	public String toString() {
		return "A square with side =" + side +
				"which is a subclass of " + super.toString();
	}
}
