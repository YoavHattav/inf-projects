package il.co.ilrd.factory;

public class Animal {
	int legs;
	public Animal() {
		legs = 4;
	}
	public String whatAmI(String I) {
		return (I + "Animal");
	}
	public int getLegs() {
		return new Integer(legs);
	}
	public void setLegs(int legs) {
		this.legs = legs;
	}
}
