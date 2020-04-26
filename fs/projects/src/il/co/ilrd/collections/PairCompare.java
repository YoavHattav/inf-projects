package il.co.ilrd.collections;

import java.util.Comparator;

public class PairCompare<T extends Comparable<T>> implements Comparator<T> {

	@Override
	public int compare(T o1, T o2) {
		if (o1.compareTo(o2) > 0)
		{
			return 1;
		}
		return 0;
	}
}
