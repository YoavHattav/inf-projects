package il.co.ilrd.example;

public class Other {

int y = 3;
    static int i;
    int j;
          static {
        i = 10;
        System.out.println("static block called ");
    }
         
     {
         System.out.println("Other Inside instance initializer block writen Before Constructor");
      }
          public Other(){
         System.out.println("Inside Constructor");
          }
         
    {
        System.out.println("Other Inside instance initializer block writen After Constructor");
    }
} 
