import java.util.Arrays;

import edu.princeton.cs.algs4.StdOut;

public class Board {
  private final int size;
  private final int max;
  private final int[][] blocks;
  private int hamming = -1;
  private int manhattan = -1;

  public Board(int[][] inBlocks) {
    size = inBlocks.length;
    max = size * size;
    blocks = new int[size][];
    for (int i = 0; i < size; ++i) {
      blocks[i] = Arrays.copyOf(inBlocks[i], size);
    }
  }

  public int dimension() {
    return size;
  }

  public int hamming() {
    if (hamming == -1) {
      int distance = 0;
      for (int i = 0; i < max; ++i) {
        int block = blocks[i / size][i % size] - 1;
        if (block == -1) continue;
        if (block != i)
          ++distance;
      }
      hamming = distance;
    }
    return hamming;
  }

  public int manhattan() {
    if (manhattan == -1) {
      int distance = 0;
      for (int i = 0; i < max; ++i) {
        int block = blocks[i / size][i % size] - 1;
        if (block == -1) continue;
        if (block != i) {
          int r = block / size;
          int c = block % size;
          distance += Math.abs((i / size) - r) + Math.abs((i % size) - c);
        }
      }
      manhattan = distance;
    }
    return manhattan;
  }

  public boolean isGoal() {
    for (int i = 0; i < max - 1; ++i) {
      if ((max + blocks[i / size][i % size] - 1) % max != i)
        return false;
    }
    return true;
  }

  public Board twin() {
    int r1 = size / 2;
    int c1 = r1;
    int r2 = r1;
    int c2 = c1;
    if (blocks[r1][c1] == 0) {
      --r1;
      --c2;
    } else {
      if (blocks[r2][c2 - 1] == 0) --r2;
      else --c2;
    }
    return swapBoard(r1, c1, r2, c2);
  }

  public boolean equals(Object y) {
    if (y == null) return false;
    if (this.getClass() != y.getClass())
      return false;
    Board other = (Board) y;
    if (size != other.dimension())
      return false;
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j)
        if (blocks[i][j] != other.blocks[i][j])
          return false;
    return true;
  }

  public Iterable<Board> neighbors() {
    int r = size, c = size;
    for (int i = 0; i < max; ++i) {
      if (blocks[i / size][i % size] == 0) {
        r = i / size;
        c = i % size;
        break;
      }
    }
    assert r < size : "Row must be in bounds";
    assert c < size : "Column must be in bounds";
    int count = 4;
    if (r == 0 || r == size - 1) --count;
    if (c == 0 || c == size - 1) --count;
    Board[] result = new Board[count];
    int id = 0;
    if (r > 0) {
      result[id] = swapBoard(r, c, r - 1, c);
      ++id;
    }
    if (r < size - 1) {
      result[id] = swapBoard(r, c, r + 1, c);
      ++id;
    }
    if (c > 0) {
      result[id] = swapBoard(r, c, r, c - 1);
      ++id;
    }
    if (c < size - 1) {
      result[id] = swapBoard(r, c, r, c + 1);
      ++id;
    }
    return Arrays.asList(result);
  }

  public String toString() {
    StringBuffer buffer = new StringBuffer();
    buffer.append(dimension());
    buffer.append("\n");
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        buffer.append("\t");
        buffer.append(blocks[i][j]);
      }
      if (i < size - 1) buffer.append("\n");
    }
    return buffer.toString();
  }

  public static void main(String[] args) {
    Board eye2 = new Board(fromString("1 2; 3 0"));
    assert eye2.isGoal() : "eye2 must be goal!";
    Board eye3 = new Board(fromString("1 2 3; 4 5 6; 7 8 0"));
    assert eye2.isGoal() : "eye3 must be goal!";

    StdOut.println("== twin for eye2 ==");
    StdOut.println(eye2.twin().toString());
    StdOut.println();

    StdOut.println("== twin for eye3 ==");
    StdOut.println(eye3.twin().toString());
    StdOut.println();

    StdOut.println("== eye2 neighbors ==");
    for (Board neighbor : eye2.neighbors()) {
      StdOut.println(neighbor);
      StdOut.println("=====");
    }
    StdOut.println();

    StdOut.println("== eye3 neighbors with sub neighbors ==");
    for (Board neighbor : eye3.neighbors()) {
      StdOut.println(neighbor);
      StdOut.println("\\/ \\/ \\/");
      for (Board subNeighbor : neighbor.neighbors()) {
        StdOut.println(subNeighbor);
        StdOut.println("=====");
      }
      StdOut.println("/\\ /\\ /\\");
      StdOut.println();
    }

    Board outOfOrder = new Board(fromString("8 1 3; 4 0 2; 7 6 5"));
    StdOut.println(outOfOrder.toString());
    StdOut.println();
    StdOut.printf("Manhattan: %d%n", outOfOrder.manhattan());
    assert outOfOrder.manhattan() == 10 : "Manhattan must be 10";
    StdOut.printf("Hamming: %d%n", outOfOrder.hamming());
    assert outOfOrder.hamming() == 5 : "Hamming must be 5";

    Board left = new Board(fromString("5 6 2; 4 3 1; 8 0 7"));
    Board right = new Board(fromString("5 6 2; 4 3 1; 8 0 7"));
    assert left.equals(right) : "Equal boards";

    Board middle = new Board(fromString("5 3 2; 4 6 1; 8 0 7"));
    assert !left.equals(middle) : "Not equal boards";
  }

  private static int[][] fromString(String config) {
    String[] lines = config.split("; ");
    int size = lines.length;
    int[][] result = new int[size][];
    for (int i = 0; i < size; ++i) {
      result[i] = new int[size];
      String[] cols = lines[i].split(" ");
      for (int j = 0; j < size; ++j) {
        result[i][j] = Integer.parseInt(cols[j]);
      }
    }
    return result;
  }

  private Board swapBoard(int r1, int c1, int r2, int c2) {
    assert r1 != r2 || c1 != c2;
    int[][] newBlocks = new int[size][];
    for (int i = 0; i < size; ++i) {
      newBlocks[i] = Arrays.copyOf(blocks[i], size);
    }
    int swap = newBlocks[r1][c1];
    newBlocks[r1][c1] = newBlocks[r2][c2];
    newBlocks[r2][c2] = swap;
    return new Board(newBlocks);
  }
}
