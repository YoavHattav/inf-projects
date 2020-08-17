package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;


public class FirstRepeating {
	
	
	static char firstReperatingN(char[] str) {
		Map<Character, Boolean> map = new HashMap<>();
		for (char ch : str) {
			if (map.containsKey(ch)) {
				return ch;
			}
			map.put(ch, true);
		}
		return '?';
	}
	
	static char firstRepeatingNOnN(char[] str) {
		for (int i = 0; i < str.length; ++i) {
			for (int j = 0; j < (i) ; ++j) {
				if (str[i] == str[j]) {
					return str[i];
				}
			}
		}
		return '?';
	}
	
	public static void main(String[] args) {
		char[] str1 = {'a','b','c','d','e','f'};
		char[] str2 = {'a','b','c','d','e','f','a'};
		
		char[] str3 = {'a', 'c', 'b', 'b', 'a', 'c'};
		
		for (char ch : str3) {
			System.out.print(ch);
		}
		
		System.out.println(firstRepeatingNOnN(str1));
		System.out.println(firstRepeatingNOnN(str2));
		
		System.out.println(firstReperatingLogN(str1));
		System.out.println(firstReperatingLogN(str2));
		
		System.out.println(firstReperatingN(str1));
		System.out.println(firstReperatingN(str2));
		
		
		System.out.println(firstRepeatingNOnN(str3));
		System.out.println(firstReperatingLogN(str3));
		System.out.println(firstReperatingN(str3));


	}
}
