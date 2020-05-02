package il.co.ilrd.collections;

import java.util.Comparator;
import java.util.Map;

public class Pair<K, V> implements Map.Entry<K, V>{
	
	private K key;
	private V value;
	
	private Pair(K key, V value) {
		this.key = key;
		this.value = value;
	}
	
	public static<K, V> Pair<K, V> of(K key, V value) {
		return new Pair<K, V>(key, value);
	}
	
	public static<K, V> Pair<V, K> swap(Pair<K, V> pair) {
		return new Pair<V, K> (pair.getValue(), pair.getKey());
	}
	
	@Override
	public K getKey() {
		return this.key;
	}
	
	@Override
	public V getValue() {
		return this.value;
	}
	
	@Override
	public V setValue(V value) {
		V oldValueHolder = this.value;
		this.value = value;
		
		return oldValueHolder;
	}
	
	public K setKey(K key) {
		K oldKeyHolder = this.key;
		this.key = key;
		
		return oldKeyHolder;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((key == null) ? 0 : key.hashCode());
		result = prime * result + ((value == null) ? 0 : value.hashCode());
		return result;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Pair<K, V> other = (Pair<K, V>) obj;
		if (key == null) {
			if (other.key != null)
				return false;
		} else if (!key.equals(other.key))
			return false;
		if (value == null) {
			if (other.value != null)
				return false;
		} else if (!value.equals(other.value))
			return false;
		return true;
	}
	
	@Override
	public String toString() {
		return "Pair [key=" + key + ", value=" + value + "]";
	}
	
	public static<T extends Comparable<T>> Pair<T, T> minMax(T[] array) {
		
		T min;
		T max;
		Pair<T, T> pair = Pair.of(null, null);
		
		if (array == null || array.length < 1)
			return pair;
	 	 
		if (array.length == 1) {
			
			return Pair.of(array[0], array[0]);
		}
	 
		if (array[0].compareTo(array[1]) > 0) {
			max = array[0];
			min = array[1];
		} else {
			max = array[1];
			min = array[0];
		}
	 
		for (int i = 2; i <= array.length - 2; i = i + 2) {
			if (array[i].compareTo(array[i + 1]) > 0) {
				min = (min.compareTo(array[i + 1]) > 0) ? array[i + 1] : min;
				max = (max.compareTo(array[i]) > 0) ? max : array[i];
			} else {
				min = (min.compareTo(array[i]) > 0) ? array[i] : min;
				max = (max.compareTo(array[i + 1]) > 0) ? max : array[i + 1];
			}
	 
		}
	 
		if (array.length % 2 == 1) {
			min = (min.compareTo(array[array.length - 1]) > 0) ? array[array.length - 1] : min;
			max = (max.compareTo(array[array.length - 1]) > 0) ? max : array[array.length - 1];
		}
	 
		pair.setKey(min);
		pair.setValue(max);
		
		return pair;
	}

	public static<T> Pair<T, T> minMax(T[] array, Comparator<T> compare) {
		
		T min;
		T max;
		Pair<T, T> pair = Pair.of(null, null);
		
		if (array == null || array.length < 1)
			return pair;
	 	 
		if (array.length == 1) {
			return Pair.of(array[0], array[0]);
		}
	 
		if (compare.compare(array[0],array[1]) > 0) {
			max = array[0];
			min = array[1];
		} else {
			max = array[1];
			min = array[0];
		}
	 
		for (int i = 2; i <= array.length - 2; i = i + 2) {
			if (compare.compare(array[i], array[i + 1]) > 0) {
				min = (compare.compare(min,array[i + 1]) > 0) ? array[i + 1] : min;
				max = (compare.compare(max,array[i]) > 0) ? max : array[i];
			} else {
				min = (compare.compare(min, array[i]) > 0) ? array[i] : min;
				max = (compare.compare(max,array[i + 1]) > 0) ? max : array[i + 1];
			}
	 
		}
	 
		if (array.length % 2 == 1) {
			min = (compare.compare(min, array[array.length - 1]) > 0) ? array[array.length - 1] : min;
			max = (compare.compare(max,array[array.length - 1]) > 0) ? max : array[array.length - 1];
		}
	 
		pair.setKey(min);
		pair.setValue(max);
		
		return pair;
	}
}


