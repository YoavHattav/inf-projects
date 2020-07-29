package il.co.ilrd.quizzes;

import java.util.HashMap;
import java.util.Map;

public class IsPermutaionAPalindrom {
	
	private Map<Character, Integer> map = new HashMap<>();
	
	public boolean isPermutationAPalindrom(String str) {
		for (int i = 0; i < str.length(); ++i) {
			if (map.containsKey(str.charAt(i))) {
				map.remove(str.charAt(i));
			}
			else {
				map.put(str.charAt(i), 1);
			}
		}
		
		if (map.size() > 1) {
			return false;
		}
		
		return true;
	}
	public static void main(String[] args) {
		
		String true_str = "yoavvaoy";
		String false_str = "adsdaf";
		
		IsPermutaionAPalindrom obj = new IsPermutaionAPalindrom();
		System.out.println(obj.isPermutationAPalindrom(true_str));
		System.out.println(obj.isPermutationAPalindrom(false_str));

	}

}
