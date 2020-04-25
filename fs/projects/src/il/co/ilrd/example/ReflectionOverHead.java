package il.co.ilrd.example;

public class ReflectionOverHead {
	
    public static void main(String[] args) throws Exception
    {
        doRegular();
        doReflection();
    }

    public static void doRegular() throws Exception
    {
        long start = System.currentTimeMillis();
        for (int i=0; i<1000000; i++)
        {
        	A a = new A();
            a.doSomeThing();
        }
        System.out.println(System.currentTimeMillis() - start);
    }

    public static void doReflection() throws Exception
    {
        long start = System.currentTimeMillis();
        for (int i=0; i<1000000; i++)
        {
        	A a = (A) Class.forName("A").newInstance();
            a.doSomeThing();
        }
        System.out.println(System.currentTimeMillis() - start);
    }
}
class A {
	int counter;
	public A() {
		counter = 0;
	}
	
	public void doSomeThing() {
		++counter;
	}
}
