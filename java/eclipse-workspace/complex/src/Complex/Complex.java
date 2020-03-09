package Complex;

import sun.awt.util.IdentityArrayList;

public class Complex implements Comparable<Complex> {
	private double real, img;
	
	public Complex(){
		real = 0;
		img = 0;
	}
	
	public Complex(double real, double img) {
		this.img = img;
		this.real = real;
	}
	
	public Complex add(Complex c) {
		return new Complex(this.real + c.real, this.img + c.img);
	}
	
	public Complex subtract(Complex c) {
		return new Complex(this.real - c.real, this.img - c.img);
	}
	
	public Complex multiplyBy(Complex c) {
		return new Complex(this.real * c.real - this.img * c.img, this.real * c.img + this.img * c.real);
	}
	
	public Complex divideBy(Complex c) {
		return new Complex((this.real*c.real + this.img*c.img)/(c.real*c.real +c.img*c.img), (c.real*this.img - this.real*c.img)/(c.real*c.real +c.img*c.img));
	}

	public double getReal() {
		return real;
	}

	public void setReal(double real) {
		this.real = real;
	}

	public double getImg() {
		return img;
	}

	public void setImg(double img) {
		this.img = img;
	}
	
	public void setValue(double real, double img) {
		this.real = real;
		this.img = img;
	}
	
	public boolean isReal(double real) {
		return (0 == real);
	}
	
	public boolean isImg(double img) {
		return (0 == img);
	}
	
	public static Complex parse(String str) {
		return new Complex(str.charAt(0)-48, str.charAt(2)-48);
	}
	
	@Override
	public int compareTo(Complex o) {
		
		Double thisRealholder = this.real;
		Double oRealholder = o.real;
		
		double diff = thisRealholder.compareTo(oRealholder);
		
		if (0 == diff)
		{
			diff = 
		}
		
		
		return 0;
	}
	
	@Override
	public String toString() {
		return "Complex [real=" + real + ", img=" + img + "i]";
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Complex other = (Complex) obj;
		if (Double.doubleToLongBits(img) != Double.doubleToLongBits(other.img))
			return false;
		if (Double.doubleToLongBits(real) != Double.doubleToLongBits(other.real))
			return false;
		return true;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		long temp;
		temp = Double.doubleToLongBits(img);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(real);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		return result;
	}
}
