package cache;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LRUCache<K extends Comparable, V> implements Cache<K, V> {
	
	Map<K, Item> cacheMap = Collections.synchronizedMap(new HashMap<K, Item>());
	Item start = new Item();
	Item end = new Item();
	int maxSize;
	Lock lock = new ReentrantLock();
	
	static class Item {
		public Comparable key;
		public Object value;
		public long expires;
		public Item previous;
		public Item next;
		
		public Item() {};
		
		public Item(Comparable key, Object value, long e) {
			this.key = key;
			this.value = value;
			this.expires = e;
		}
		
	}
	
	public LRUCache(int max) {
		this.maxSize = max;
	}
	
	public void removeItem(Item item) {
		lock.lock();
		item.previous.next = item.next;
		item.next.previous = item.previous;
		lock.unlock();
	}
	
	public void insertHead(Item item) {
		lock.lock();
		item.next = start;
		start.previous = item;
		start = item;
		lock.unlock();
	}
	
	public void moveToHead(Item item) {
		lock.lock();
		item.previous.next = item.next;
		item.next.previous = item.previous;
		item.next = start;
		start.previous = item;
		start = item;
		lock.unlock();
	}
	
	@Override
	public V get(K key) {
		Item cur = cacheMap.get(key);
		if (cur == null)
			return null;
		if (System.currentTimeMillis() > cur.expires) {
			cacheMap.remove(key);
			removeItem(cur);
			return null;
		}
		if (cur != start) {
			moveToHead(cur);
		}
		return (V) cur.value;
	}

	@Override
	public void put(K key, V value) {
		put(key, value, -1);
	}
	
	@Override
	public void put(K key, V value, long validTime) {
		//cacheMap.put(key, new Item(key, value, e)
		Item cur = cacheMap.get(key);
		if (cur != null) {
			cur.value = value;
			cur.expires = ((validTime > 0) ? (System.currentTimeMillis() + validTime) : Long.MAX_VALUE);
			moveToHead(cur);
			return ;
		}
		if (cacheMap.size() >= maxSize) {
			Item tmp = end;
			cacheMap.remove(tmp.key);
			removeItem(tmp);
		}
		long expires = ((validTime > 0) ? (System.currentTimeMillis() + validTime) : Long.MAX_VALUE);
		Item newItem = new Item(key, value, expires);
		cacheMap.put(key, newItem);
		insertHead(newItem);
	}

	@Override
	public void remove(K key) {
		
		Item item = cacheMap.get(key);
		if (item != null) {
			cacheMap.remove(key);
			removeItem(item);
		}
	}

	@Override
	public int size() {
		return cacheMap.size();
	}

}
