package il.co.ilrd.quizzes;

import java.util.Stack;

public class MyStackQueue {
	Stack<Integer> popStack;
	Stack<Integer> pushStack;
	
	public MyStackQueue() {
		this.popStack = new Stack<Integer>();
		this.pushStack = new Stack<Integer>();
	}
	public void push(Integer data) {
		pushStack.push(data);
	}
	public Integer pop() {
		if (popStack.isEmpty() && (!pushStack.isEmpty())) {
			while (!pushStack.isEmpty()) {
				popStack.push(pushStack.pop());
			}
		}
		return (popStack.isEmpty()) ? null : popStack.pop();
	}
	public Integer peek() {
		if (popStack.isEmpty() && (!pushStack.isEmpty())) {
			while (!pushStack.isEmpty()) {
				popStack.push(pushStack.pop());
			}
		}
		return (popStack.isEmpty()) ? null : popStack.peek();
	}
	public boolean isEmpty() {
		if (popStack.isEmpty() && pushStack.isEmpty()) {
			return true;
		}
		return false;
	}
	public static void main(String[] args) {
		MyStackQueue queue = new MyStackQueue();
		queue.push(5);
		queue.push(4);
		queue.push(3);
		queue.push(2);
		queue.push(1);
		for (Integer i = 50; i > 0; --i) {
			queue.push(i);
		}
		System.out.println(queue.peek());
		while (!queue.isEmpty()) {
			System.out.println(queue.pop());
		}
	}
}
