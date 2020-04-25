package il.co.ilrd.factory;

public class AnimalFactory {
	int legs;
	int num_of_masters;
	String color;
	
	public AnimalFactory(int legs, int num_of_masters, String color) {
		super();
		this.legs = legs;
		this.num_of_masters = num_of_masters;
		this.color = color;
	}
	
	public static Animal getAnimal(String animal) {
		
		switch (animal) {
		case "Dog" :
			return new Dog();
		case "Animal" :
			return new Animal();
		case "Cat" :
			return new Cat();
		}
		return null;
	}
}

