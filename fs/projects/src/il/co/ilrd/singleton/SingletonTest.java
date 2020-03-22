package il.co.ilrd.singleton;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import il.co.ilrd.singleton.EnumSingleton.Singleton;

class SingletonTest {

	@Test
	void StaticFinal() {
		StaticFinalSingleton obj1 = StaticFinalSingleton.getInstance(); 
		StaticFinalSingleton obj2 = StaticFinalSingleton.getInstance(); 
		StaticFinalSingleton obj3 = StaticFinalSingleton.getInstance();
  
        obj1.setX();
        
        assertEquals(obj1.getX(), obj2.getX());
        assertEquals(obj1.getX(), obj3.getX());
	}
	
	@Test
	void Volatile() {
		DoubleCheckedSingleton obj1 = DoubleCheckedSingleton.getInstance(); 
		DoubleCheckedSingleton obj2 = DoubleCheckedSingleton.getInstance(); 
		DoubleCheckedSingleton obj3 = DoubleCheckedSingleton.getInstance();
  
		obj1.setX();
        
        assertEquals(obj1.getX(), obj2.getX());
        assertEquals(obj1.getX(), obj3.getX());
	}
	
	@Test
	void SyncSingleton() {
		SyncSingleton obj1 = SyncSingleton.getInstance(); 
		SyncSingleton obj2 = SyncSingleton.getInstance(); 
		SyncSingleton obj3 = SyncSingleton.getInstance();
  
		obj1.setX();
        
        assertEquals(obj1.getX(), obj2.getX());
        assertEquals(obj1.getX(), obj3.getX());
	}
	
	@Test
	void HolderSingleton() {
		SingletonHolder obj1 = SingletonHolder.getInstance(); 
		SingletonHolder obj2 = SingletonHolder.getInstance(); 
		SingletonHolder obj3 = SingletonHolder.getInstance();
  
		obj1.setX();
        
        assertEquals(obj1.getX(), obj2.getX());
        assertEquals(obj1.getX(), obj3.getX());
	}
	
	@Test
	void EnumSingleton() {
		Singleton obj1 = Singleton.INSTANCE;
		Singleton obj2 = Singleton.INSTANCE;
		Singleton obj3 = Singleton.INSTANCE;
  
		obj1.setX();
        
        assertEquals(obj1.getX(), obj2.getX());
        assertEquals(obj1.getX(), obj3.getX());
	}
}
