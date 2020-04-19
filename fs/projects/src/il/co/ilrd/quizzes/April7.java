package il.co.ilrd.quizzes;

public class April7<T> {
	
	interface Person {
		default void Hi() {
			System.out.println("Hello");
		}
	}
	interface Male {
		default void Hi() {
			System.out.println("Hi");
		}
	}
	class Sam implements Person, Male {

		@Override
		public void Hi() {
			Male.super.Hi();
		}
		
	}
	
	Sam sam = new Sam();
	sam.Hi();
	Sam secSam = new Sam();
	secSam.Hi();
	
	public static void main(String[] args) {

	}

}
