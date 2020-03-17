package il.co.ilrd.java_intro;

import java.util.ArrayList; 

class Jconsol { 
    public static void main(String[] args) 
    { 
        int n = 1000;
        int num_of_elements = 100000; 
        Runtime r_class = Runtime.getRuntime();

        // Here aList is an ArrayList of ArrayLists
        ArrayList<int[]> aList = new ArrayList<int[]>();

        while (n > 0)
        {
            System.out.println("total: " + r_class.totalMemory());
            System.out.println("free: " + r_class.freeMemory());
        }
    } 
} 