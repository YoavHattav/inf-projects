package il.co.ilrd.buffer_sort;

public class CountingSort implements Runnable{
	
	static private int[] histo = new int[256];
	private int[] thread_histo = new int[256];
	private int start_index = 0, end_index = 0;
	private char[] param;
	
	public CountingSort(int start_index, int end_index, char[] param) {
		this.start_index = start_index;
		this.end_index = end_index;
		this.param = param;
	}
	
	public int[] getHisto() {
		return histo;
	}

	@Override
	public void run() {
		System.out.println("start " + start_index + " end " + end_index);
		for (int i = start_index; i < end_index; ++i)
		{
			++thread_histo[(int)param[i]];
		}
		synchronized(histo) {
			for (int j = 0; j < 256; ++j)
			{
				histo[j] += thread_histo[j];
			}
		}
	}
}
