package il.co.ilrd.collection_ws;

import java.util.HashMap;
import java.util.Map;

public class WeekDayMap {
	public static void main(String[] args) {
		Map<String, String> map = new HashMap<>();
		
		map.put("Sunday", "One");
		map.put("Monday", "Two");
		map.put("Tuesday", "Three");
		map.put("Wednesday", "Four");
		map.put("Thursday", "Five");
		map.put("Friday", "Six");
		map.put("Saturday", "Seven");
		
		for (Map.Entry<String, String> entry : map.entrySet()) {
			System.out.println(entry);
		}
		for (String key : map.keySet()) {
			System.out.println(key);
		}
		for (String value : map.values()) {
			System.out.println(value);
		}
	}

}
