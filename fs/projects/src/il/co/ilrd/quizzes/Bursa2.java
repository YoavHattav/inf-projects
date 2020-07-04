package il.co.ilrd.quizzes;

public class Bursa2 {
	public static int bursa(int[] array) {
		int min = array[0];
		int current_profit = 0;
		int max_profit = 0;
		int buy_index = 0;
		int sell_index = 0;
		int temp_min_index = 0;
		
		for (int i = 1; i < array.length; ++i) {
			current_profit = array[i] - min;
			if (array[i] < min) {
				min = array[i];
				temp_min_index = i;
			}
			else if (max_profit < current_profit) {
				max_profit = current_profit;
				buy_index = temp_min_index;
				sell_index = i;
			}
		}
		System.out.println(buy_index + " " + sell_index);
		return max_profit;
	}
	
	public static void main(String[] args) {
		int[] array = {12,3,4,23,7,5,10,80, 2, 1, 33};
		System.out.println(Bursa2.bursa(array));
	}

}
