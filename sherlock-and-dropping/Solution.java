import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import java.util.TreeMap;
import java.util.ArrayList;
import java.util.Map;

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
    private long finalX;

    public Point() { x = 0; y = 0; }
    public Point(long x, long y) { setX(x); setY(y); setFinalX(x); }

    public long getX() { return x; }
    public void setX(long x) { this.x = x; }

    public long getY() { return y; }
    public void setY(long y) { this.y = y; }

    public long getFinalX() { return finalX; }
    public void setFinalX(long finalX) { this.finalX = finalX; }

    public Segment getOwner() { return owner; }
    public void setOwner(Segment owner) { this.owner = owner; }

    public Point minus(Point right) {
      return new Point(getX() - right.getX(), getY() - right.getY());
    }

    public boolean equals(Point other) {
      return other.getX() == getX() && other.getY() == getY();
    }
  }

  static int pointXAscComparator(Point left, Point right) {
    if(left.getX() == right.getX()) {
      if(left.getY() == right.getY()) return 0;
      return left.getY() > right.getY() ? -1 : 1;
    }
    return left.getX() < right.getX() ? -1 : 1;
  }

  static int pointYAscComparator(Point left, Point right) {
    if(left.getY() == right.getY()) {
      if(left.getX() == right.getX()) return 0;
      return left.getX() < right.getX() ? -1 : 1;
    }
    return left.getY() < right.getY() ? -1 : 1;
  }

  static Point readPoint() {
    int x = in.nextInt(), y = in.nextInt();
    return new Point(x, y);
  }

  static Segment readSegment() {
    return new Segment(readPoint(), readPoint());
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

      left.setOwner(this); right.setOwner(this);
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
    in = new Scanner(System.in);

    if(argv.length > 0) {
      if("units".equals(argv[0])) {
        runUnits();
        System.exit(0);
      }
    }

    Solution one = new Solution();
    one.solve();

    in.close();
  }

  public Solution() {
  }

  protected void getFalls(TreeSet<Segment> lines, TreeSet<Point> balls, Map<Point, Segment> inRes) {
    TreeSet<Point> ends = new TreeSet<Point>(Solution::pointXAscComparator);
    TreeSet<Segment> currentSegments = new TreeSet<Segment>();
    while(lines.size() > 0 || ends.size() > 0) {
      // select event
      boolean is_new = false;
      Segment target = null;
      if(lines.size() == 0) target = ends.pollFirst().getOwner();
      else if(ends.size() == 0 || lines.first().getLeft().getX() < ends.first().getOwner().getRight().getX()) {
        target = lines.pollFirst();
        is_new = true;
      } else {
        target = ends.pollFirst().getOwner();
      }
      Point ruler = is_new ? target.getLeft() : target.getRight();
      // process all balls up to event occurense
      while(balls.size() > 0 && balls.first().getX() <= ruler.getX()) {
        Point ball = balls.pollFirst();
        Segment fallOn = currentSegments.higher(new Segment(ball, ball));
        if(fallOn != null) {
          System.out.format("register fall (%d %d) on (%d %d; %d %d)%n",
                            ball.getX(), ball.getY(),
                            fallOn.getLeft().getX(), fallOn.getLeft().getY(),
                            fallOn.getRight().getX(), fallOn.getRight().getY());
          if(inRes != null) inRes.put(ball, fallOn);
          ball.setFinalX(fallOn.getFinalX());
        }
      }
      // execute event
      if(is_new) {
        currentSegments.add(target);
        System.out.format("add %d %d %d %d%n", target.getLeft().getX(), target.getLeft().getY(),
                           target.getRight().getX(), target.getRight().getY());
        ends.add(target.getRight());
      }
      else {
        currentSegments.remove(target);
        System.out.format("remove %d %d %d %d%n", target.getLeft().getX(), target.getLeft().getY(),
                           target.getRight().getX(), target.getRight().getY());
      }
    }
  }

  public void solve() {
    int linesCount = in.nextInt(),
      ballsCount = in.nextInt();

    ArrayList<Segment> lines = new ArrayList<Segment>();
    TreeSet<Point> lineEnds = new TreeSet<Point>(Solution::pointXAscComparator);
    for(int i = 0; i < linesCount; ++i) {
      Segment another = readSegment();
      lines.add(another);
      Point bottom = another.getBottom();
      lineEnds.add(bottom);
    }

    TreeMap<Point, Segment> falls = new TreeMap<Point, Segment>(Solution::pointYAscComparator);
    getFalls(new TreeSet<Segment>(lines), lineEnds, falls);

    for(Map.Entry<Point, Segment> fall : falls.entrySet())
      fall.getKey().getOwner().setFinalX(fall.getValue().getFinalX());

    System.out.println("-- Processing balls");

    ArrayList<Point> balls = new ArrayList<Point>();
    for(int i = 0; i < ballsCount; ++i)
      balls.add(readPoint());

    TreeSet<Point> sortedBalls = new TreeSet<Point>(Solution::pointXAscComparator);
    sortedBalls.addAll(balls);
    getFalls(new TreeSet<Segment>(lines), sortedBalls, null);

    for(Point ball : balls)
      System.out.println(ball.getFinalX());
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
