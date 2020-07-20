package il.co.ilrd.quizzes;

import java.util.LinkedList;
import java.util.Queue;

public class ImpStackUsingQ {
	Queue<Integer> q1 = new LinkedList<Integer>();
	Queue<Integer> q2 = new LinkedList<Integer>();
	public Integer curr_size = 0;
	
	public void push(int x) 
    { 
        curr_size++; 

        q2.add(x); 

        while (!q1.isEmpty()) { 
            q2.add(q1.peek()); 
            q1.remove(); 
        } 

        Queue<Integer> q = q1; 
        q1 = q2; 
        q2 = q; 
    } 
	public Integer pop() 
    { 

        if (q1.isEmpty()) 
            return 0;
        curr_size--;
        return q1.remove(); 
    } 
	public static void main(String[] args) {

	}

}
