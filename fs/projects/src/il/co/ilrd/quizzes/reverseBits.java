package il.co.ilrd.quizzes;

public class reverseBits {
	public static Integer reverse(Integer num) {
		Integer mask = 1; Integer result = 0;
		int counter = 0;
		while (num != 0) {
			result |= num & mask;
			num >>= mask; result <<= mask;
			++counter;
		}
		return (result << (31 - counter));
	}
	
	public static Integer reverse8Bit(Integer num) {
		
		return null;
	}
	public static void main(String[] args) {
		Integer test1 = 1;
		System.out.println(reverse(test1));
	}

}
