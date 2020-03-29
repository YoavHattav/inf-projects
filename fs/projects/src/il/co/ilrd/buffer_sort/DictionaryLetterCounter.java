package il.co.ilrd.buffer_sort;

public class DictionaryLetterCounter {
	private static final int NUM_OF_THREADS = 10;
	private static char[] dictio_array;
	static final String words_path = "/usr/share/dict/words";
	static long startTime;
	
	public String Sort() {
		int[] histograma;
		Thread myThreads[] = new Thread[NUM_OF_THREADS];
		
		fileToStringToChar translateObj = new fileToStringToChar(words_path);
		dictio_array = translateObj.generateShuffledCharArray();
		
		startTime = System.currentTimeMillis();

		for (int i = 0; i < NUM_OF_THREADS; ++i) {
			myThreads[i] = new Thread(new CountingSort(i * dictio_array.length / NUM_OF_THREADS, ((i + 1) * dictio_array.length) / NUM_OF_THREADS, dictio_array));
			myThreads[i].start();
			
		}
		for (int i = 0; i < NUM_OF_THREADS; ++i)
		{
			try {
				myThreads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			} 
		}
		histograma = (new CountingSort(0, 0, dictio_array)).getHisto();
		/*for (int j = 0; j < 256; ++j)
		{
			System.out.println((char)j + " = " + histograma[j]);
		}*/
		int b = 0;
		for (int i = (int)'A'; i <= (int)'Z'; ++i)
		{
			//System.out.println("char is: " + (char)i);
			for (int j = histograma[i]; j > 0 ; --j)
			{
				dictio_array[++b] = (char)i;
			}
		}
		for (int i = (int)'a'; i <= (int)'z'; ++i)
		{
			//System.out.println("char is: " + (char)i);
			for (int j = histograma[i]; j > 0 ; --j)
			{
				dictio_array[++b] = (char)i;
			}
		}
		return dictio_array.toString();
	}
	
	public static void main(String[] args) {
		
		String final_product = new String();
		final_product = (new DictionaryLetterCounter()).Sort();
		long endTime = System.currentTimeMillis();
		System.out.println("Total execution time: " + (endTime - startTime));
	}
}
