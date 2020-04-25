package il.co.ilrd.hashmap;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import il.co.ilrd.pair.Pair;

public class HashMap<K,V> implements Map<K, V>{

	private List<List<Pair<K, V>>> hashMap;
	private final int capacity;
	private final static int DEFAULT_VALUE = 16;
	private int currentMode = 0;
	
	public HashMap() {
		this(DEFAULT_VALUE);
	}
	
	public HashMap(int capacity) {
		this.capacity = capacity;
		hashMap = new ArrayList<List<Pair<K, V>>>();
		for (int i = 0; i < capacity; ++i)
		{
			hashMap.add(new LinkedList<Pair<K, V>>());
		}
	}
	
	@Override
	public void clear() {
		++currentMode;
		for (List<Pair<K, V>> element : hashMap)
			element.clear();
	}
	
	@Override
	public boolean containsKey(Object key) {
		
		Pair<K, V> entry = getEntry(key);
		
		if (null == entry)
		{
			return false;
		}
		if (entry.getKey().equals(key))
		{
			return true;
		}
		
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		for (List<Pair<K, V>> bucket : hashMap)
		{
			for (Pair<K, V> entry : bucket) {
				if (entry.getValue().equals(value)) {
					return true;
				}
			}
		}
		return false;
	}

	@Override
	public Set<Map.Entry<K, V>> entrySet() {
		
		return new EntrySet();
	}

	@Override
	public V get(Object key) {
		Pair<K, V> entry = getEntry(key);
		
		if (entry == null) {
			return null;
		}
		
		return entry.getValue();
	}

	@Override
	public boolean isEmpty() {
		return size() == 0;
	}

	@Override
	public Set<K> keySet() {
		
		return new KeySet();
	}

	@Override
	public V put(K key, V value) {
		
		List<Pair<K, V>> bucket = hashMap.get(getBucket(key));
		++currentMode;

		for (Pair<K, V> entry : bucket) {
			if (entry.getKey().equals(key)) {
				return entry.setValue(value);
			}
		}
		bucket.add(Pair.of(key, value));
		
		return null;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		++currentMode;
		for (Map.Entry<? extends K, ? extends V> entry : m.entrySet()) {
			put(entry.getKey(), entry.getValue());
		}
	}

	@Override
	public V remove(Object key) {
		++currentMode;
		Pair<K, V> pair = getEntry(key);
		hashMap.get(getBucket(key)).remove(pair);
		
		return pair.getValue();
	}

	@Override
	public int size() {
		int size = 0;

		for(List<Pair<K,V>> bucket : hashMap) {
			size += bucket.size();
		}

		return size;
	}

	@Override
	public Collection<V> values() {
		
		return new ValueCollection();
	}
	
	private int getBucket(Object key){
		if (key == null) {
			return 0;
		}
		
		return key.hashCode() % capacity;
	}
	
	private Pair<K,V> getEntry(Object arg0){
		for(Pair<K,V> pair : this.hashMap.get(getBucket(arg0))) {
			if(pair.getKey().equals(arg0)) {
				return pair;
			}
		}
		
		return null;
	}

	private class EntrySet extends AbstractSet<Map.Entry<K, V>>{
		
		private int expectedMode;

		@Override
		public Iterator<Map.Entry<K, V>> iterator() {
			expectedMode = currentMode;
			return new EntryIterator();
		}

		@Override
		public int size() {
			return HashMap.this.size();
		}
		
		private class EntryIterator implements Iterator<Map.Entry<K, V>>{
			
			Iterator<List<Pair<K, V>>> bucketIter = hashMap.iterator();
			Iterator<Pair<K, V>> internalIter = bucketIter.next().iterator();
			
			public EntryIterator() {
				while(!internalIter.hasNext() && bucketIter.hasNext()) {
					internalIter = bucketIter.next().iterator();
				}
			}
			
			@Override
			public boolean hasNext() {
				return(internalIter.hasNext() || bucketIter.hasNext());	
			}

			@Override
			public Map.Entry<K,V> next() {
				checkIteratorValidation();
				Map.Entry<K, V> entry = internalIter.next();
				while(!internalIter.hasNext() && bucketIter.hasNext()) {
					internalIter = bucketIter.next().iterator();
				}
				
				return entry;
			}
			
		}
		final void checkIteratorValidation() {
			if (currentMode != expectedMode)
				throw new ConcurrentModificationException();
		}

	}
	
	private class KeySet extends AbstractSet<K> implements Iterator<K> {
		
		private Iterator<Entry<K, V>> iter = new EntrySet().iterator();		
		
		@Override
		public boolean hasNext() {
			return iter.hasNext();
		}

		@Override
		public K next() {
			return iter.next().getKey();
		}

		@Override
		public Iterator<K> iterator() {
			return new KeySet();
		}

		@Override
		public int size() {
			return HashMap.this.size();
		}
		
	}
	
	private class ValueCollection extends AbstractCollection<V> implements Iterator<V> {

		private Iterator<Entry<K, V>> iter = new EntrySet().iterator();
		
		@Override
		public boolean hasNext() {
			return iter.hasNext();
		}

		@Override
		public V next() {
			return iter.next().getValue();
		}

		@Override
		public Iterator<V> iterator() {
			return new ValueCollection();
		}

		@Override
		public int size() {
			
			return HashMap.this.size();
		}
	}
}
