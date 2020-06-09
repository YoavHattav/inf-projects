package il.co.ilrd.quizzes;

public class Sam implements Man, Person{

}
// we had to change the names of the methods "sayHello".
interface Man {
	default public void SayHello() {
		System.out.println("Hi");
	}
}
interface Person {
	default public void sayHello() {
		System.out.println("Hello");
	}
}