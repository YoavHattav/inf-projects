package il.co.ilrd.quizzes;

import java.util.Arrays;

public class KnapSack {
	
	
	static int calc(int W, int[] wt, int[] val, int n) {
		int result = 0;
		int[] takenIndex = new int[n];
		int currentW = W;
		
		List<int>wtList = Arrays.asList(wt);
		Arrays.asList(a);
		for (int i = 0; i < n; ++i) {
			if (W - wt[i]) {
				
			}
		}
		
		return n;
	}
	
	public static void main(String args[])
	{
		int val[] = new int[]{60, 100, 120};
		int wt[] = new int[]{10, 20, 30};
		int W = 50;
		int n = val.length;
		System.out.println(KnapSack.calc(W, wt, val, n));
		
	}
}
