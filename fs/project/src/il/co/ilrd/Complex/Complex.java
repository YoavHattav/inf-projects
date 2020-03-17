package il.co.ilrd.Complex;

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
		return new Complex(this.getReal() + c.getReal(), this.getImg() + c.getImg());
	}
	
	public Complex subtract(Complex c) {
		return new Complex(this.getReal() - c.getReal(), this.getImg() - c.getImg());
	}
	
	public Complex multiplyBy(Complex c) {
		return new Complex(this.getReal() * c.getReal() - this.getImg() * c.getImg(), this.getReal() * c.img + this.img * c.getReal());
	}
	
	public Complex divideBy(Complex c) {
		return new Complex((this.getReal()*c.getReal() + this.getImg() * c.getImg())/(c.getReal()*c.getReal() +c.getImg()*c.getImg()), (c.getReal()*this.getImg() - this.getReal()*c.getImg())/(c.getReal()*c.getReal() +c.getImg()*c.getImg()));
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
		return (0 == this.getImg());
	}
	
	public boolean isImg(double img) {
		return (0 == this.getReal());
	}
	
	public static Complex parse(String str) {
		
        str = str.replaceAll(" ","");
        Complex parsed = null;
        if(str.contains(String.valueOf("+")) || (str.contains(String.valueOf("-")) && str.lastIndexOf('-') > 0))
        {
            String re = "";
            String im = "";
            str = str.replaceAll("i","");
            str = str.replaceAll("I","");
            if(str.indexOf('+') > 0)
            {
                re = str.substring(0,str.indexOf('+'));
                im = str.substring(str.indexOf('+')+1,str.length());
                parsed = new Complex(Double.parseDouble(re),Double.parseDouble(im));
            }
            else if(str.lastIndexOf('-') > 0)
            {
                re = str.substring(0,str.lastIndexOf('-'));
                im = str.substring(str.lastIndexOf('-')+1,str.length());
                parsed = new Complex(Double.parseDouble(re),-Double.parseDouble(im));
            }
        }
        else
        {
            if(str.endsWith("i") || str.endsWith("I"))
            {
                str = str.replaceAll("i","");
                str = str.replaceAll("I","");
                parsed = new Complex(0, Double.parseDouble(str));
            }
            else
            {
                parsed = new Complex(Double.parseDouble(str),0);
            }
        }
        return parsed;
    }
	
	@Override
	public int compareTo(Complex o) {
		if (this.real == o.getReal())
		{
			if(this.img == o.getImg())
			{
				return 1;
			}
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