package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.List;

public class IdLog {
	List<Long> log;
	private int write_index = 0;
	int num_of_items = 0;

	public IdLog(int N) {
		log = new ArrayList<Long>(N);
	}
	
	public void record(Long id) {
		log.add(write_index, id);
		write_index = (write_index + 1) % log.size();
	}
	
	public Long getLast(int index) {
		return (write_index > index) ?
				log.get((write_index + log.size())- index) :
					log.get(write_index - index );
	}
}
