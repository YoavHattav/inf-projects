package example;

public class RTTITest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Useful[] x = {
				new Useful(),
				new MoreUseful()
		};
		x[0].f();
		x[1].g();
		x[1].i();
		((MoreUseful)x[1]).i();
		((MoreUseful)x[0]).i();
	}
}
