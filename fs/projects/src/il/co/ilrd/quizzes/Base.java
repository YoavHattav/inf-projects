package il.co.ilrd.quizzes;

class Base {

	public Base() {
		System.out.println("base");
	}
	
}
class derived extends Base{

	public derived() {
		System.out.println("derived");
	}
	
}
class Deriderived extends derived{

	public Deriderived() {
		System.out.println("Deriderived");
	}
	
}
class Test {
	public static void main(String[] args) {
		derived d = new Deriderived();
	}
}