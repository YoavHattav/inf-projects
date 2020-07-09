package il.co.ilrd.quizzes;

public class MinPathSumInTree {
	TreeNode root;
	
	private TreeNode addRecursive(TreeNode current, int value) {
	    if (current == null) {
	        return new TreeNode(value);
	    }
	 
	    if (value < current.data) {
	        current.left = addRecursive(current.left, value);
	    } else if (value > current.data) {
	        current.right = addRecursive(current.right, value);
	    } else {
	        // value already exists
	        return current;
	    }
	 
	    return current;
	}
	
	public void add(int value) {
	    root = addRecursive(root, value);
	}
	
	class TreeNode {
		Integer data = 0;
		TreeNode left;
		TreeNode right;
		
		TreeNode(int data) {
	        this.data = data;
	        right = null;
	        left = null;
	    }
	}
	
	
	public static int minPathSum(TreeNode root) {
		if (root == null) {
			return 0;
		}
		if (root.left == null && root.right == null) {
			return root.data;
		}
		else if (root.left == null) {
			return root.data + minPathSum(root.right);
		}
		else if (root.right == null) {
			return root.data + minPathSum(root.left);
		}
		return root.data + Math.min(minPathSum(root.left), minPathSum(root.right));
	}
	public static void main(String[] args) {
		MinPathSumInTree tree = new MinPathSumInTree();
		
		tree.add(1);
		tree.add(11);
		tree.add(3);
		tree.add(4);
		tree.add(5);
		tree.add(2);
		tree.add(10);
		tree.add(8);
		tree.add(6);
		tree.add(7);
		tree.add(9);

		System.out.println(MinPathSumInTree.minPathSum(tree.root));

	}

}
