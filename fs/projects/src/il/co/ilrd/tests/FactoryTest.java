package il.co.ilrd.tests;

import org.junit.Test;

import il.co.ilrd.design_patterns.Factory;
import il.co.ilrd.factory.*;

class FactoryTest {

	@Test
	void test() {
		Factory<Integer, Animal, String> factory = new Factory<>();
		
		factory.Add(1, AnimalFactory::getAnimal);
		
		Animal animal = factory.Create(1, "Animal");
		Dog dog = (Dog)factory.Create(1, "Dog");
		Cat cat = (Cat)factory.Create(1, "Cat");

		//intance method reference
		Factory<Integer, String, String> factory2 = new Factory<>();
		factory2.Add(1, animal::whatAmI);
		factory2.Add(2, dog::whatAmI);
		factory2.Add(3, cat::whatAmI);
		System.out.println(factory2.Create(1, "i am a "));
		System.out.println(factory2.Create(2, "i am a "));
		System.out.println(factory2.Create(3, "i am a "));
		
		//static method reference
		factory2.Add(4, Dog::bark);
		System.out.println(factory2.Create(4, "?"));
		
		//arbitrery method reference
		Factory<Integer, Long, Integer> arbi_factory = new Factory<>();
		arbi_factory.Add(1, Integer::longValue);
		System.out.println(arbi_factory.Create(1, 10));
		
		//constructor method reference
		Factory<Integer, Integer, Integer> const_factory = new Factory<>();
		const_factory.Add(1, Integer::new);
		System.out.println(const_factory.Create(1, 10));
	}
}
