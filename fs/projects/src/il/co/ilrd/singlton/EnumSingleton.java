package il.co.ilrd.singlton;

public class EnumSingleton {
	enum Singleton {
		INSTANCE(0);
		
		private int x;
		
		private Singleton(int x) {
			this.x = x;
		}
		
		public int getX() {
			return x;
		}

		public void setX() {
			this.x = 5;
		}
	}
}
