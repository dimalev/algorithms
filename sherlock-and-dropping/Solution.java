import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class Solution {
  static Scanner in;

  static boolean isCW(Point pivot, Point from, Point to) {
    Point normalFrom = from.minus(pivot);
    Point normalTo = to.minus(pivot);
    return normalFrom.getY() * normalTo.getX() > normalFrom.getX() * normalTo.getY();
  }

  static boolean isCCW(Point pivot, Point from, Point to) {
    Point normalFrom = from.minus(pivot);
    Point normalTo = to.minus(pivot);
    return normalFrom.getY() * normalTo.getX() < normalFrom.getX() * normalTo.getY();
  }

  static class Point {
    private long x;
    private long y;
    private Segment owner = null;

    public Point() { x = 0; y = 0; }
    public Point(long x, long y) { setX(x); setY(y); }

    public long getX() { return x; }
    public void setX(long x) { this.x = x; }

    public long getY() { return y; }
    public void setY(long y) { this.y = y; }

    public Segment getOwner() { return owner; }
    public void setOwner(Segment owner) { this.owner = owner; }

    public Point minus(Point right) {
      return new Point(getX() - right.getX(), getY() - right.getY());
    }

    public boolean equals(Point other) {
      return other.getX() == getX() && other.getY() == getY();
    }
  }

  static int pointXComparator(Point left, Point right) {
    if(left.getX() == right.getX()) return 0;
    return left.getX() < right.getX() ? -1 : 1;
  }

  static Segment readSegment() {
    int x1 = in.nextInt(), y1 = in.nextInt(),
      x2 = in.nextInt(), y2 = in.nextInt();
    return new Segment(new Point(x1, y1), new Point(x2, y2));
  }

  static class Segment implements Comparable<Segment> {
    private Point left;
    private Point right;

    private long finalX;

    Segment(Point one, Point two) {
      if(one.getX() < two.getX()) {
        left = one; right = two;
      } else {
        left = two; right = one;
      }

      finalX = getBottom().getX();
    }

    public Point getBottom() { return left.getY() < right.getY() ? left : right; }
    public Point getTop() { return left.getY() < right.getY() ? left : right; }

    public Point getLeft() { return left; }
    public Point getRight() { return right; }

    public long getFinalX() { return finalX; }
    public void setFinalX(long finalX) { this.finalX = finalX; }

    @Override
    public boolean equals(Object otherObj) {
      Segment other = (Segment)otherObj;
      if(other == null) return false;
      return other.left.equals(left) && other.right.equals(right);
    }

    @Override
    public int compareTo(Segment other) {
      if(equals(other)) return 0;
      if(left.getX() < other.left.getX())
        return isCW(left, right, other.left) ? -1 : 1;
      return isCCW(other.left, other.right, left) ? -1 : 1;
    }
  }

  public static void main(String[] argv) {
    try(in = new Scanner(System.in)) {

      if(argv.length > 0) {
        if("units".equals(argv[0])) {
          runUnits();
          System.exit(0);
        }
      }

      Solution one = new Solution();
      one.solve();
    }
  }

  public Solution() {
  }

  public void solve() {
    int linesCount = in.nextInt(),
      ballsCount = in.nextInt();

    TreeSet<Segment> lines;
    TreeSet<Point> lineEnds(Solution::pointXComparator);
    for(int i = 0; i < linesCount; ++i) {
      Segment another = readSegment();
      lines.put(another);
      Point bottom = another.getBottom();
      bottom.setOwner(another);
      lineEnds.put(bottom);
    }

    Map<Point, Segment> falls = getFalls(lines, lineEnds);
  }

  static interface TestCase {
    String getName();
    void run();
  }

  static class TestSegmentCompare implements TestCase {
    @Override
    public String getName() { return "segment_compare"; }

    @Override
    public void run() {
      int T = in.nextInt();
      while(T-- > 0) {
        Segment s1 = readSegment();
        Segment s2 = readSegment();
        System.out.println(s1.compareTo(s2));
      }
    }
  }

  static TestCase[] units = new TestCase[]{ new TestSegmentCompare() };

  static void runUnits() {
    for(TestCase test : units) {
      String header = in.next();
      if(test.getName().equals(header)) {
        System.out.println(test.getName());
        test.run();
      } else {
        System.out.format("Wrong header: <%s> expected <%s>%n", header, test.getName());
      }
    }
  }
}
