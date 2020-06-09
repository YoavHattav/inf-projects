package il.co.ilrd.quizzes;

public class KnapSack {
	
	private int max(int a, int b) { return (a > b)? a : b; } 
	// O(2^n)
	public int knapSack(int W, int wt[], int val[], int n) { 
	    	if (n == 0 || W == 0) {
	        	return 0; 
		}
	       
	    	if (wt[n-1] > W) {
	      		return knapSack(W, wt, val, n-1);
		} 
	       

	        return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1), knapSack(W, wt, val, n-1) ); 
	}
	// O(W*n)
	public int knapSackIter(int W, int wt[], int val[], int n) { 
		int i, w; 
	     int K[][] = new int[n+1][W+1]; 
	       
	     for (i = 0; i <= n; i++) { 
	         for (w = 0; w <= W; w++) { 
	             if (i==0 || w==0) {K[i][w] = 0;} 
	             else if (wt[i-1] <= w) {
	                   K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
	             }
	             else {K[i][w] = K[i-1][w];}
	         } 
	      }
	      
	      return K[n][W]; 
	}
	public static void main(String[] args) {
		int[] wArray = {10, 20, 20};
		int[] vArray = {60, 100, 120};
	}

}
