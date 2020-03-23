package il.co.ilrd.buffer_sort;

public class DictionaryLetterCounter {
	
	private static int start_index = 0;
	private static int end_index = 0;
	private static final int num_of_threads = 5;
	private static char[] param;
	static final String words_path = "/usr/share/dict/words";
	
	private static void updateIndexes(int iter) {
		
		int len = param.length;
		start_index = end_index + 1;
		end_index = (len / num_of_threads) * (iter + 1) - 1;
	}
	
	public static void main(String[] args) {
		
		int i = 0;
		int[] histograma;

		fileToStringToChar translateObj = new fileToStringToChar(words_path);
		param = translateObj.generateShuffledCharArray();
		
		
		updateIndexes(i);
		start_index = 0;
		for (i = 1; i < num_of_threads; ++i)
		{
			(new Thread(new CountingSort(start_index, end_index, param))).start();
			updateIndexes(i);
		}
		(new Thread(new CountingSort(param.length/num_of_threads * (--i), param.length - 1, param))).start();
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		histograma = (new CountingSort(i, i, param)).getHisto();
		for (int j = 0; j < 256; ++j)
		{
			System.out.println((char)j + " = " + histograma[j]);
		}
		/*
		String final_product = new String();
		for (i = (int)'A'; i < (int)'Z'; ++i)
		{
			System.out.println("char is: " + (char)i);
			for (int j = histograma[i]; j > 0 ; --j)
			{
				final_product = final_product + (char)i;
			}
		}
		for (i = (int)'a'; i < (int)'z'; ++i)
		{
			System.out.println("char is: " + (char)i);
			for (int j = histograma[i]; j > 0 ; --j)
			{
				final_product = final_product + (char)i;
			}
		}
		System.out.println(final_product);*/
	}
}
