package il.co.ilrd.generics_exercises;

public class FooReference <T>{
	private T t;

	public T getT() {
		return t;
	}

	public void setT(T t) {
		this.t = t;
	}

	public FooReference(T t) {
		this.t = t;
	}
	
	public static void main(String[] args) {
		FooReference<Integer> foo = new FooReference<>(47);
		FooReference<String> food = new FooReference<>("teemo is satan");
		System.out.println(foo.getT());
		System.out.println(food.getT());
		System.out.println(foo.getT().getClass());
		System.out.println(food.getT().getClass());
		System.out.println(food.getClass());
	}
}