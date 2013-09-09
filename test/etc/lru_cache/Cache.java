package cache;

public interface Cache<K extends Comparable, V> {
	V get(K key);
	void put(K key, V value);
	void put(K key, V value, long validTime);
	void remove(K key);
	int size();
}

class Pair<K extends Comparable, V> implements Comparable<Pair> {
	public K key;
	public V value;
	@Override
	public int compareTo(Pair p) {
		int tmp = key.compareTo(p.key);
		if (tmp == 0) {
			if (p.value instanceof Comparable)
				return ((Comparable)value).compareTo(p.value);
		}
		return tmp;
	}
	
}
