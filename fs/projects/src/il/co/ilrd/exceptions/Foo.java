package il.co.ilrd.exceptions;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class Foo {
	static void func1() throws IOException {
		File file = new File("test.txt");
		FileInputStream fileInputStream = null;
        try{
            fileInputStream = new FileInputStream(file);
            fileInputStream.read();
        }catch (IOException e){         
            e.printStackTrace();
        }
        finally{
            try{
                if (fileInputStream != null){
                    fileInputStream.close();
                }
            }catch (IOException e){
                e.printStackTrace();
            }
        }

	}
	public void print() {
		System.out.println("that's awesome");
	}
	static void func2(Foo obj) {
		obj.print();
	}
	public static void main(String args[]) {
		Foo obj = null;
		try {
			func1();
		} catch (IOException e) {
			e.printStackTrace();
		}
		func2(obj);
	}
}