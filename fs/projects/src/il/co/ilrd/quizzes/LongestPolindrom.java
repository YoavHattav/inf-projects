package il.co.ilrd.quizzes;

public class LongestPolindrom {
	private int poliLength(char[] charStr, int index) {
		int counter = 3;
		int desRunner = index - 2;
		int incRunner = index + 2;
		while ((desRunner >= 0) && (incRunner < charStr.length) && (charStr[desRunner] == charStr[incRunner])) {
			counter += 2;
			++incRunner;
			--desRunner;
		}
		return counter;
	}
	public int longestPalSubstr(String str) {
		char[] charStr = str.toCharArray();
		int counter = 0;
		int maxCounter = 0;
		for (int i = 1; i < (charStr.length - 1); ++i) {
			if (charStr[i - 1] == charStr[i + 1]) {
				maxCounter = poliLength(charStr, i);
				counter = (counter > maxCounter ? counter : maxCounter);
			}
		}
		return counter;
	}
	
	public static void main(String[] args) {
		LongestPolindrom lp = new LongestPolindrom();
		String str = "dddaaaddd";
		System.out.println(lp.longestPalSubstr(str));
	}

}
