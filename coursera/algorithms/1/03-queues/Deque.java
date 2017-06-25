import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
  private Node<Item> head = null;
  private Node<Item> tail = null;
  private int size = 0;

  private static class Node<Item> {
    private final Item item;
    private Node<Item> next;
    private Node<Item> prev;

    public Node(Item inItem) {
      item = inItem;
    }

    public Item item() {
      return item;
    }
    public Node<Item> getNext() {
      return next;
    }
    public void setNext(Node<Item> newNext) {
      next = newNext;
    }

    public Node<Item> getPrev() {
      return prev;
    }
    public void setPrev(Node<Item> newPrev) {
      prev = newPrev;
    }
  }

  public Deque() {
    // simple constructor
  }

  public boolean isEmpty() {
    return size == 0;
  }

  public int size() {
    return size;
  }

  public void addFirst(Item item) {
    if (item == null) throw new IllegalArgumentException();
    Node<Item> newHead = new Node<>(item);
    newHead.setPrev(head);
    if (head == null) {
      tail = newHead;
    } else {
      head.setNext(newHead);
    }
    head = newHead;
    ++size;
  }

  public void addLast(Item item) {
    if (item == null) throw new IllegalArgumentException();
    Node<Item> newTail = new Node<>(item);
    newTail.setNext(tail);
    if (tail == null) {
      head = newTail;
    } else {
      tail.setPrev(newTail);
    }
    tail = newTail;
    ++size;
  }

  public Item removeFirst() {
    if (head == null) throw new NoSuchElementException();
    Item item = head.item();
    Node<Item> newHead = head.getPrev();
    if (newHead == null) {
      tail = null;
    } else {
      head.setPrev(null);
      newHead.setNext(null);
    }
    head = newHead;
    --size;
    return item;
  }

  public Item removeLast() {
    if (tail == null) throw new NoSuchElementException();
    Item item = tail.item();
    Node<Item> newTail = tail.getNext();
    if (newTail == null) {
      head = null;
    } else {
      tail.setNext(null);
      newTail.setPrev(null);
    }
    tail = newTail;
    --size;
    return item;
  }

  public Iterator<Item> iterator() {
    return new DequeIterator<Item>(head);
  }

  private static class DequeIterator<Item> implements Iterator<Item> {
    private Node<Item> current;

    public DequeIterator(Node<Item> start) {
      current = start;
    }

    @Override
    public boolean hasNext() {
      return current != null;
    }

    @Override
    public Item next() {
      if (current == null) throw new NoSuchElementException();
      Item item = current.item();
      current = current.getPrev();
      return item;
    }

    @Override
    public void remove() {
      throw new UnsupportedOperationException();
    }
  }

  public static void main(String[] args) {
    Deque<Integer> deque = new Deque<Integer>();
    if (!deque.isEmpty()) throw new Error("Fresh deck must be empty!");
    deque.addFirst(12);
    deque.addFirst(10);
    deque.addLast(14);
    deque.addLast(16);
    if (deque.isEmpty()) throw new Error("Deck with four elements is not empty!");
    if (deque.size() != 4) throw new Error("Size must be 4");
    if (!deque.removeFirst().equals(10)) throw new Error("Element must be 10!");
    if (!deque.removeFirst().equals(12)) throw new Error("Element must be 12!");
    if (!deque.removeFirst().equals(14)) throw new Error("Element must be 14!");
    if (!deque.removeFirst().equals(16)) throw new Error("Element must be 16!");
    if (!deque.isEmpty()) throw new Error("Empty deck must be empty!");
    boolean isExThrown = false;
    try {
      deque.removeFirst();
    } catch (NoSuchElementException nsex) {
      isExThrown = true;
    }
    if (!isExThrown) throw new Error("Empty deque must thow excetpion!");
    deque.addLast(14);
    deque.addFirst(12);
    deque.addLast(16);
    deque.addFirst(10);
    isExThrown = false;
    try {
      deque.addLast(null);
    } catch (IllegalArgumentException iaex) {
      isExThrown = true;
    }
    if (!isExThrown) throw new Error("Inserting null must throw!");
    Iterator<Integer> it = deque.iterator();
    isExThrown = false;
    try {
      it.remove();
    } catch (UnsupportedOperationException uoex) {
      isExThrown = true;
    }
    if (!isExThrown) throw new Error("Remove must be unsupported");
    if (!it.hasNext()) throw new Error("Must have elements!");
    if (!it.next().equals(10)) throw new Error("Must be 10!");
    if (!it.hasNext()) throw new Error("Must have elements!");
    if (!it.next().equals(12)) throw new Error("Must be 10!");
    if (!it.hasNext()) throw new Error("Must have elements!");
    if (!it.next().equals(14)) throw new Error("Must be 10!");
    if (!it.hasNext()) throw new Error("Must have elements!");
    if (!it.next().equals(16)) throw new Error("Must be 10!");
    if (it.hasNext()) throw new Error("Must be empty!");
  }
}
