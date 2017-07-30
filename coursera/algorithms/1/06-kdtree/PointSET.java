import java.util.TreeSet;
import java.util.ArrayList;

import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Point2D;

public class PointSET {
  private final TreeSet<Point2D> points = new TreeSet<>();

  public PointSET() {
  }

  public boolean isEmpty() {
    return points.isEmpty();
  }

  public int size() {
    return points.size();
  }

  public void insert(Point2D p) {
    if (p == null)
      throw new IllegalArgumentException("No nulls accepted!");
    points.add(new Point2D(p.x(), p.y()));
  }

  public boolean contains(Point2D p) {
    if (p == null)
      throw new IllegalArgumentException("No nulls accepted!");
    return points.contains(p);
  }

  public void draw() {
    for (Point2D point : points)
      point.draw();
  }

  public Iterable<Point2D> range(RectHV rect) {
    if (rect == null)
      throw new IllegalArgumentException("No nulls accepted!");
    ArrayList<Point2D> result = new ArrayList<>();
    for (Point2D point : points)
      if (rect.contains(point))
        result.add(new Point2D(point.x(), point.y()));
    return result;
  }

  public Point2D nearest(Point2D p) {
    if (p == null)
      throw new IllegalArgumentException("No nulls accepted!");
    double d = Double.MAX_VALUE;
    Point2D output = null;
    for (Point2D point : points) {
      double newD = point.distanceTo(p);
      if (newD < d) {
        d = newD;
        output = point;
      }
    }
    return output;
  }

  public static void main(String[] args) {
    checkThrowing();
    PointSET test = new PointSET();
    assert test.isEmpty() : "initially set is empty";
    test.insert(new Point2D(0, 0));
    assert !test.isEmpty() : "after first insertion set is empty no more";
    test.insert(new Point2D(100, 0));
    test.insert(new Point2D(23, 94));
    test.insert(new Point2D(83, 12));
    test.insert(new Point2D(55, 55));
    assert !test.isEmpty() : "still not empty";
    boolean yesRes = test.contains(new Point2D(23, 94));
    assert yesRes : "Must contain the point";
    boolean noRes = test.contains(new Point2D(83, 55));
    assert !noRes : "Must not contain the point";
    Iterable<Point2D> output = test.range(new RectHV(12, 80, 112, 110));
    boolean onlyOne = true;
    for (Point2D thePoint : output) {
      if (!onlyOne)
        assert false : "there must be one point";
      onlyOne = false;
      assert thePoint.x() == 23 : "point x == 23";
      assert thePoint.y() == 94 : "point y == 94";
    }
    Point2D nearestPoint = test.nearest(new Point2D(89, 40));
    assert nearestPoint.x() == 83 : "must be x == 83";
    assert nearestPoint.y() == 12 : "must be y == 12";
  }

  private static void checkThrowing() {
    // throw null pointer exception if any argument is null
    PointSET nullTest = new PointSET();
    boolean thrown = false;
    try {
      nullTest.insert(null);
    } catch (IllegalArgumentException npe) {
      thrown = true;
    }
    if (!thrown) {
      System.err.println("insert did not throw illegal argument exception!");
    }
    thrown = false;
    try {
      nullTest.contains(null);
    } catch (IllegalArgumentException npe) {
      thrown = true;
    }
    if (!thrown) {
      System.err.println("contains did not throw illegal argument exception!");
    }
    thrown = false;
    try {
      nullTest.range(null);
    } catch (IllegalArgumentException npe) {
      thrown = true;
    }
    if (!thrown) {
      System.err.println("range did not throw illegal argument exception!");
    }
    thrown = false;
    try {
      nullTest.nearest(null);
    } catch (IllegalArgumentException npe) {
      thrown = true;
    }
    if (!thrown) {
      System.err.println("nearest did not throw illegal argument exception!");
    }
  }
}
