package il.co.ilrd.quizzes;

public class April12InnerClasses {
	static int st_yoav;
	int instance_yoav;
	
	private class Ineer {
		st_yoav = 5;
		instance_yoav = 5;
		
	}
	private static class Nested {
		
		static int nested_static_yoav = 5;
		st_yoav = 5;
		instance_yoav = 5;
	}
	void foo() {
		class Local{
			st_yoav = 5;
			instance_yoav = 5;
		}
	}
}
}
