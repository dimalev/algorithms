import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
  private final int size;
  private final boolean[] blocks;
  private final WeightedQuickUnionUF top;
  private final WeightedQuickUnionUF both;
  private int openSites = 0;

  public Percolation(int n) {
    if (n <= 0)
      throw new IllegalArgumentException();
    size = n;
    blocks = new boolean[size * size];
    top = new WeightedQuickUnionUF(size * size + 1);
    both = new WeightedQuickUnionUF(size * size + 2);
    for (int i = 0; i < size * size; ++i) {
      blocks[i] = true;
    }
  }

  public void open(int row, int col) {
    if (get(row, col)) {
      set(row, col, false);
      ++openSites;
      if (row > 1 && isOpen(row - 1, col)) {
        top.union(index(row, col), index(row - 1, col));
        both.union(index(row, col), index(row - 1, col));
      } else if (row == 1) {
        top.union(index(row, col), size * size);
        both.union(index(row, col), size * size);
      }
      if (row < size && isOpen(row + 1, col)) {
        top.union(index(row, col), index(row + 1, col));
        both.union(index(row, col), index(row + 1, col));
      } if (row == size) {
        both.union(index(row, col), size * size + 1);
      }
      if (col > 1 && isOpen(row, col - 1)) {
        top.union(index(row, col), index(row, col - 1));
        both.union(index(row, col), index(row, col - 1));
      }
      if (col < size && isOpen(row, col + 1)) {
        top.union(index(row, col), index(row, col + 1));
        both.union(index(row, col), index(row, col + 1));
      }
    }
  }
  public boolean isOpen(int row, int col) {
    return !get(row, col);
  }

  public boolean isFull(int row, int col) {
    if (row < 1 || row > size)
      throw new IllegalArgumentException();
    if (col < 1 || col > size)
      throw new IllegalArgumentException();
    return top.connected(index(row, col), size * size);
  }

  public int numberOfOpenSites() {
    return openSites;
  }

  public boolean percolates() {
    return both.connected(size * size, size * size + 1);
  }

  private boolean get(int row, int col) {
    if (row < 1 || row > size)
      throw new IllegalArgumentException();
    if (col < 1 || col > size)
      throw new IllegalArgumentException();
    return blocks[index(row, col)];
  }

  private void set(int row, int col, boolean isBlocked) {
    if (row < 1 || row > size)
      throw new IllegalArgumentException();
    if (col < 1 || col > size)
      throw new IllegalArgumentException();
    blocks[index(row, col)] = isBlocked;
  }

  private int index(int row, int col) {
    return (row - 1) * size + col - 1;
  }
}
