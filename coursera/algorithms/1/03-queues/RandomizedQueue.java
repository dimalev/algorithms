import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdOut;

import java.util.NoSuchElementException;
import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> {
  private static final int MIN_SIZE = 8;
  private Object[] memory = new Object[MIN_SIZE];
  private int capacity = MIN_SIZE;
  private int size = 0;

  public RandomizedQueue() {
    // simple constructor
  }

  public boolean isEmpty() {
    return size == 0;
  }

  public int size() {
    return size;
  }

  public void enqueue(Item item) {
    if (item == null) throw new IllegalArgumentException();
    if (size >= capacity) resize(2 * capacity);
    memory[size] = item;
    ++size;
  }

  public Item dequeue() {
    if (size == 0) throw new NoSuchElementException();
    int id = StdRandom.uniform(size);
    Item item = (Item) memory[id];
    --size;
    if (size > 0) {
      memory[id] = memory[size];
    }
    if (size < capacity / 4) resize(capacity / 2);
    return item;
  }

  public Item sample() {
    if (size == 0) throw new NoSuchElementException();
    int id = StdRandom.uniform(size);
    return (Item) memory[id];
  }

  public Iterator<Item> iterator() {
    return new RandomizedQueueIterator<Item>(memory, size);
  }

  private class RandomizedQueueIterator<Item> implements Iterator<Item> {
    private final Object[] items;
    private int id = 0;

    public RandomizedQueueIterator(Object[] memory, int size) {
      int[] indexes = StdRandom.permutation(size);
      items = new Object[size];
      for (int i = 0; i < size; ++i) {
        items[i] = memory[indexes[i]];
      }
    }

    @Override
    public boolean hasNext() {
      return id < items.length;
    }

    @Override
    public Item next() {
      if (id >= items.length) throw new NoSuchElementException();
      Item item = (Item) items[id];
      ++id;
      return item;
    }

    @Override
    public void remove() {
      throw new UnsupportedOperationException();
    }
  }

  private void resize(int newCapacity) {
    if (newCapacity < MIN_SIZE) return;
    if (newCapacity == capacity) return;
    Object[] newMemory = new Object[newCapacity];
    for (int i = 0; i < size; ++i) {
      newMemory[i] = memory[i];
    }
    memory = newMemory;
    capacity = newCapacity;
  }
  public static void main(String[] args) {
    RandomizedQueue<Integer> queue = new RandomizedQueue<Integer>();
    for (int i = 10; i < 100; i += 10) {
      queue.enqueue(i);
    }
    StdOut.println("Samples from [10..100) with step 10");
    for (int i = 0; i < 10; ++i) {
      StdOut.print(queue.sample());
      if (i != 9) StdOut.print(", ");
    }
    StdOut.println();
    StdOut.println("Drain 5 elements:");
    for (int i = 0; i < 5; ++i) {
      StdOut.print(queue.dequeue());
      if (i != 4) StdOut.print(", ");
    }
    StdOut.println();
    Iterator<Integer> first = queue.iterator();
    Iterator<Integer> second = queue.iterator();
    StdOut.print("First: ");
    while (first.hasNext()) {
      StdOut.print(first.next());
      StdOut.print(", ");
    }
    StdOut.println();
    StdOut.print("Second: ");
    while (second.hasNext()) {
      StdOut.print(second.next());
      StdOut.print(", ");
    }
    StdOut.println();
  }
}
