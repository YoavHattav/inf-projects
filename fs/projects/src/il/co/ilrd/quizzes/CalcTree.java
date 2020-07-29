package il.co.ilrd.quizzes;

import java.util.HashMap;
import java.util.Map;
import java.util.function.BiFunction;

public class CalcTree {
	
	class Node {
		char value;
		Node left, right;
		public Node(char item) {
			value = item;
			left = right = null;
		}
	}
	
	private static BiFunction<Integer, Integer, Integer> plus_func = (x1, x2) -> x1 + x2;
	private static BiFunction<Integer, Integer, Integer> minus_func = (x1, x2) -> x1 - x2;
	private static BiFunction<Integer, Integer, Integer> div_func = (x1, x2) -> x1 / x2;
	private static BiFunction<Integer, Integer, Integer> mult_func = (x1, x2) -> x1 * x2;

	private static Map<Character, BiFunction> operations = new HashMap<>();
	
	public CalcTree() {
		operations.put('+', plus_func);
		operations.put('-', minus_func);
		operations.put('/', div_func);
		operations.put('*', mult_func);
	}
	
	public static Integer calc(Node root) {
		if (root.left == null && root.right == null) {
			return Character.getNumericValue(root.value);
		}
		BiFunction<Integer, Integer, Integer> func = operations.get(root.value);
		
		return func.apply(calc(root.left), calc(root.right));
	}
	
	public static void main(String[] args) {
		CalcTree tree = new CalcTree();
		Node root = tree.new Node('*');
		root.left = tree.new Node('+');
		root.right = tree.new Node('+');
		root.left.left = tree.new Node('3');
		root.left.right = tree.new Node('2');
		root.right.left = tree.new Node('4');
		root.right.right = tree.new Node('+');
		root.right.right.left = tree.new Node('2');
		root.right.right.right = tree.new Node('3');

		System.out.println(calc(root));
	}
}
