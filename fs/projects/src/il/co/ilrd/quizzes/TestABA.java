package il.co.ilrd.quizzes;

public class TestABA {
	protected int x;
	protected int y;
	public TestABA(int x, int y) {
		this.x = x;
		this.y = y;
	}
	protected void printY() {
		System.out.println("class A printY: " + y);
	}
	protected void printX() {
		System.out.println("class A printx: " + x);
	}
	protected void f(int z) {
		x += z;
		z = x;
	}
	public String toString() {
		return "im A";
	}
	public static void main(String[] args) {
		B b1 = new C(1, 7);
		int z = 6;
		b1.f(z);
		System.out.println("z = " + z);
		B b2 = new B(11, 17);
		TestABA a1 = b1;
		System.out.println(b1.toString());
		System.out.println(a1.toString());
		System.out.println(b2.toString());
		a1.printX();
		b2.printX();
		a1.printY();
		b2.printY();
	}
}
class B extends TestABA {
	public B(int x, int y) {
		super(x,y);
	}
	int j;
	
	protected void printY() {
		System.out.println("class B printY: " + y);
	}
	public String toString() {
		return "im B and " + super.toString();
	}
}
class C extends B {
	public C(int x, int y) {
		super(x, y);
	}
	protected void printX() {
		System.out.println("Class c printX : " + x);
	}
}
















