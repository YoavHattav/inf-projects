package il.co.ilrd.quizzes;

public class NonAdjacentSum {
	
	public int nonAdjacentSum(int[] array) {
        int incl = array[0];
        int prev = 0;
        int possible;
        int i;
  
        for (i = 1;  i < array.length;  ++i)  {

            possible = (incl > prev) ? incl : prev;
  
            incl = prev + array[i];
            prev = possible;
        }
  
        return ((incl > prev) ? incl : prev);
    }

	public static void main(String[] args) {
		int[] array = {13, 1 ,-6 , 2, 43 , 65 ,-18 ,14 ,13, 22};

	}

}
