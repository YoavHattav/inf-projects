package il.co.ilrd.generics_exercises;

public class Generics {
		
	protected static <T> void printArray(T[] t){
		for (T i : t) {
			System.out.println(i);
		}
	}
	
	public static void main(String[] args) {
		Integer[] intArray = {1,2,3};
		Double[] doubleArray = {1.2,2.4,3.0};
		Character[] charArray = {'Y','O','A','V'};
		Integer b = 42;
		printArray(intArray);
		printArray(doubleArray);
		printArray(charArray);
		FooReference<Integer> foo = new FooReference<Integer>(47);
	}
}