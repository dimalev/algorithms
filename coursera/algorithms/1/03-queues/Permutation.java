import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;

public class Permutation {
  public static void main(String[] args) {
    int k = Integer.parseInt(args[0]);
    if (k == 0) return;
    RandomizedQueue<String> memory = new RandomizedQueue<>();
    while (!StdIn.isEmpty()) {
      String newString = StdIn.readString();
      memory.enqueue(newString);
    }
    for (String word : memory) {
      StdOut.println(word);
      if (--k == 0) break;
    }
  }
}
