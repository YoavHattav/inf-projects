package il.co.ilrd.quizzes;

public class RootToLeafSum {
	class TreeNode {
		public TreeNode left = null;
		public TreeNode right = null;
		public String value = null;
		public TreeNode(String value) {
			this.value = value;
		}
	}
	
	private String helper(TreeNode root) {
		if (root.left == null && root.right == null) {
			return root.value;
		}
		
		return null;
	}
	public Integer rootToLeafSum(TreeNode root) {
		
		return null;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
