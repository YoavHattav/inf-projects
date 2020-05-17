package il.co.ilrd.quizzes;

public class EncodeStr {
	public String encodeStr(String src) {
		StringBuilder dest = new StringBuilder();
		int char_counter = 1;
		char[] charArray = src.toCharArray();
		
		for (int i = 1; i < charArray.length; ++i) {
			if (charArray[i] == charArray[i - 1])
			{
				++char_counter;
				continue;
			}
				dest.append(charArray[i - 1]);
				dest.append(char_counter);
				char_counter = 1;
			
		}
		if (charArray[charArray.length - 1] != charArray[charArray.length - 2])
		{
			char_counter = 1;
		}
		dest.append(charArray[charArray.length - 1]);
		dest.append(char_counter);
		
		return dest.toString();
	}
	public static void main(String[] args) {
		String str = "yyyyyooooaaavv";
		EncodeStr obj = new EncodeStr();
		System.out.println(obj.encodeStr(str));
	}
}
