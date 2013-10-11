package myset;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class MyHashSet<T> implements Iterable<T>{
    private static final int DEFAULT_INITIAL_CAPACITY = 16;
    private List<T>[] entries;
    private int size;
    private int capacity;
    
    public MyHashSet() {
        capacity = DEFAULT_INITIAL_CAPACITY;
        entries = new List[capacity];
        size = 0;
    }
    
    public MyHashSet(int capacity) {
        this.capacity = capacity;
        entries = new List[capacity];
        size = 0;
    }
    
    public int size() {
        return size;
    }
    
    public boolean add(T value) {
        if (contains(value))
            return false;
        int idx = hash(value);
        if (entries[idx] == null)
            entries[idx] = new ArrayList<T>();
        if (entries[idx].add(value)) {
            size++;
            return true;
        }
        return false;
    }
    
    public boolean remove(T value) {
        if (!contains(value))
            return false;
        int idx = hash(value);
        if (entries[idx].remove(value)) {
            size--;
            return true;
        }
        return false;
    }
    
    public boolean contains(T value) {
        int idx = hash(value);
        if (entries[idx] == null || !entries[idx].contains(value))
            return false;
        return true;
    }
    
    private int hash(T value) {
        return value.hashCode() % capacity;
    }
    
    @Override
    public Iterator<T> iterator() {
        return new Iterator<T>() {
            private int index = 0;
            private int cursor = 0;
            private Iterator<T> list;
            
            @Override
            public boolean hasNext() {
                return (index < size);
            }

            @Override
            public T next() {
                if (entries[cursor] == null) {
                    while (entries[cursor] == null)
                        cursor++;
                    list = entries[cursor].iterator();
                    index++;
                    return list.next();
                }
                if (list.hasNext()) {
                    index++;
                    return list.next();
                }
                while (entries[++cursor] == null) ;
                list = entries[cursor].iterator();
                index++;
                return list.next();
            }

            @Override
            public void remove() {
                throw new UnsupportedOperationException();
            }
        };
    }
    
    public static void main(String[] args) {
        MyHashSet<String> myset = new MyHashSet<String>();
        
        myset.add("abc");
        myset.add("bcd");
        myset.add("abd");
        myset.add("efg");
        myset.add("e");
        myset.add("ef");
        myset.add("eg");
        myset.add("g");
        myset.remove("efg");
        for (Iterator<String> it = myset.iterator(); it.hasNext(); ) {
            String s = it.next();
            System.out.println(s);
        }
    }
}
