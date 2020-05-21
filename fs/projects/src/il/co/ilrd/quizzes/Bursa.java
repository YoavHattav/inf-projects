package il.co.ilrd.quizzes;

public class Bursa {
	public int bestBuy(int[] array) {
		int min = array[0];
		int maxProfit = 0;
		int currentProfit = 0;
		for (int current : array) {
			currentProfit = current - min;
			if (currentProfit < 0) {
				min = current;
			}
			else if (maxProfit < currentProfit) {
				maxProfit = currentProfit;
			}
		}
		return maxProfit;
	}
	
	public static void main(String[] args) {
		Bursa b = new Bursa();
		int[] array = {9, 11, 8, 5, 7, 10, 2};
		System.out.println(b.bestBuy(array));
	}

}
