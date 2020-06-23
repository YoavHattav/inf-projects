package il.co.ilrd.quizzes;

public class MaxHotelCapacity {
	private static final int numOfRoomsInTheHotel = 8;
	private static int maxInArray(int[] start, int[] end) {
		int max = 0;
		for (int i : start) {
			max = (i > max) ? i : max;
		}
		for (int i : end) {
			max = (i > max) ? i : max;
		}
		return max;
	}
	public static int maxOverlapIntervalCount(int[] start, int[] end){
		int counter = 0;
		int[] array = new int[/*numOfRoomsInTheHotel or*/ maxInArray(start, end)];
		for (int i = 0; i < start.length; ++i) {
			for (int j = start[i]; j < end[i]; ++j) {
				++array[j];
				counter = (array[j] > counter) ? array[j] : counter;
			}
		}
		return counter;
	}
	public static void main(String[] args) {
		int[] start = {0, 3, 4, 7, 1};
		int[] end = {2, 7, 6, 8, 5};
		System.out.println(maxOverlapIntervalCount(start, end));		
	}
}
