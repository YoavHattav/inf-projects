package il.co.ilrd.quizzes;


public class FlipBTree {
	 class Node<T>{
		private T data;
		Node<T> left;
		Node<T> right;
		public T getData() {
			return data;
		}
		public void setData(T data) {
			this.data = data;
		}
	}
	public static Node<Integer> flipBTree(Node<Integer> root) {
		Node<Integer> curr = root, prev = null, next = null, temp = null;
		while (null != curr) {
			next = curr.left;
			curr.left = temp;
			temp = curr.right;
			curr.right = prev;
			prev = curr;
			curr = next;
		}
		return prev;
	}
}
