import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.In;

public class Solver {
  private final List<Board> way;

  private static class Node implements Comparable<Node> {
    private final Node previous;
    private final Board board;
    private final int step;
    private final int weight;

    public Node(Node inPrevious, Board inBoard, int inStep) {
      previous = inPrevious;
      board = inBoard;
      step = inStep;

      weight = board.manhattan() + step;
    }

    public Board getBoard() {
      return board;
    }

    public Node getPreviousNode() {
      return previous;
    }

    public int getStep() {
      return step;
    }

    @Override
    public int compareTo(Node other) {
      return weight - other.weight;
    }

    public Iterable<Board> next() {
      List<Board> list = new LinkedList<Board>();
      for (Board neighbor : board.neighbors()) {
        if (previous == null || !neighbor.equals(previous.board)) {
          list.add(neighbor);
        }
      }
      return list;
    }
  }


  public Solver(Board initial) {
    if (initial == null)
      throw new IllegalArgumentException("Board must not be null!");

    MinPQ<Node> originalPQ = new MinPQ<>();
    originalPQ.insert(new Node(null, initial, 0));
    MinPQ<Node> twinPQ = new MinPQ<>();
    twinPQ.insert(new Node(null, initial.twin(), 0));
    LinkedList<Board> foundWay = null;
    while (foundWay == null && !originalPQ.isEmpty()) {
      Node original = processQueue(originalPQ);
      if (original != null) {
        foundWay = new LinkedList<Board>();
        while (original != null) {
          foundWay.addFirst(original.getBoard());
          original = original.getPreviousNode();
        }
      }
      Node twin = processQueue(twinPQ);
      if (twin != null) break;
    }
    way = foundWay;
  }

  private Node processQueue(MinPQ<Node> queue) {
    if (queue.isEmpty()) return null;
    Node best = queue.delMin();
    if (best.getBoard().isGoal()) {
      return best;
    } else {
      for (Board board : best.next()) {
        queue.insert(new Node(best, board, best.getStep() + 1));
      }
    }
    return null;
  }

  public boolean isSolvable() {
    return way != null;
  }

  public int moves() {
    return way == null ? -1 : way.size() - 1;
  }

  public Iterable<Board> solution() {
    if (way == null) return null;
    return new ArrayList<Board>(way);
  }

  public static void main(String[] args) {
    In in = new In(args[0]);
    int n = in.readInt();
    int[][] blocks = new int[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            blocks[i][j] = in.readInt();
    Board initial = new Board(blocks);

    // solve the puzzle
    Solver solver = new Solver(initial);

    // print solution to standard output
    if (!solver.isSolvable())
        StdOut.println("No solution possible");
    else {
        StdOut.println("Minimum number of moves = " + solver.moves());
        for (Board board : solver.solution())
            StdOut.println(board);
    }
  }
}
