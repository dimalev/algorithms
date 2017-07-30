import java.util.ArrayList;

import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.StdDraw;

public class KdTree {
  private static class Node {
    private final Point2D root;
    private final boolean isVertical;
    private final RectHV bounds;

    private Node left, right;

    public Node(Point2D inRoot, boolean inIsVertical, RectHV inBounds) {
      root = inRoot;
      isVertical = inIsVertical;
      bounds = inBounds;
    }

    public boolean addChild(Point2D childRoot) {
      if(childRoot.equals(root)) return false;
      if (isVertical) {
        if (childRoot.x() < root.x()) {
          if (left == null) {
            RectHV newBounds = new RectHV(
                bounds.xmin(),
                bounds.ymin(),
                root.x(),
                bounds.ymax()
            );
            left = new Node(childRoot, false, newBounds);
            return true;
          } else {
            return left.addChild(childRoot);
          }
        } else {
          if (right == null) {
            RectHV newBounds = new RectHV(
                root.x(),
                bounds.ymin(),
                bounds.xmax(),
                bounds.ymax()
            );
            right = new Node(childRoot, false, newBounds);
            return true;
          } else {
            return right.addChild(childRoot);
          }
        }
      } else {
        if (childRoot.y() < root.y()) {
          if (left == null) {
            RectHV newBounds = new RectHV(
                bounds.xmin(),
                bounds.ymin(),
                bounds.xmax(),
                root.y()
            );
            left = new Node(childRoot, true, newBounds);
            return true;
          } else {
            return left.addChild(childRoot);
          }
        } else {
          if (right == null) {
            RectHV newBounds = new RectHV(
                bounds.xmin(),
                root.y(),
                bounds.xmax(),
                bounds.ymax()
            );
            right = new Node(childRoot, true, newBounds);
            return true;
          } else {
            return right.addChild(childRoot);
          }
        }
      }
    }

    public void draw() {
      if (left != null) left.draw();
      if (right != null) right.draw();
      if (isVertical) {
        StdDraw.setPenColor(StdDraw.RED);
        StdDraw.line(root.x(), bounds.ymin(), root.x(), bounds.ymax());
      } else {
        StdDraw.setPenColor(StdDraw.BLUE);
        StdDraw.line(bounds.xmin(), root.y(), bounds.xmax(), root.y());
      }
      root.draw();
    }

    public boolean contains(Point2D p) {
      if (root.equals(p)) return true;
      if (left != null && left.getBounds().contains(p) && left.contains(p))
        return true;
      return right != null && right.getBounds().contains(p)
        && right.contains(p);
    }

    public void range(RectHV rect, ArrayList<Point2D> result) {
      if (rect.contains(root))
        result.add(root);
      if (left != null && left.getBounds().intersects(rect))
        left.range(rect, result);
      if (right != null && right.getBounds().intersects(rect))
        right.range(rect, result);
    }

    public Point2D nearest(Point2D p, double minD, Point2D minP) {
      double rootD = p.distanceTo(root);
      if (rootD < minD) {
        minD = rootD;
        minP = root;
      }
      if (left == null && right == null) return minP;
      if (left == null) {
        if(right != null && right.getBounds().distanceTo(p) < minD) {
          Point2D newMin = right.nearest(p, minD, minP);
          if (newMin != minP) {
            minP = newMin;
          }
        }
        return minP;
      }
      if (right == null) {
        if(left != null && left.getBounds().distanceTo(p) < minD) {
          Point2D newMin = left.nearest(p, minD, minP);
          if (newMin != minP) {
            minP = newMin;
          }
        }
        return minP;
      }
      double d2l = left.getBounds().distanceTo(p);
      double d2r = right.getBounds().distanceTo(p);
      if (d2l < d2r) {
        if (d2l < minD) {
          Point2D newMin = left.nearest(p, minD, minP);
          if (newMin != minP) {
            minP = newMin;
            minD = newMin.distanceTo(p);
          }
        }
        if (d2r < minD) {
          Point2D newMin = right.nearest(p, minD, minP);
          if (newMin != minP) {
            minP = newMin;
          }
        }
      } else {
        if (d2r < minD) {
          Point2D newMin = right.nearest(p, minD, minP);
          if (newMin != minP) {
            minP = newMin;
            minD = newMin.distanceTo(p);
          }
        }
        if (d2l < minD) {
          Point2D newMin = left.nearest(p, minD, minP);
          if (newMin != minP) {
            minP = newMin;
          }
        }
      }
      return minP;
    }

    public RectHV getBounds() { return bounds; }
  }

  private Node root;
  private int size = 0;

  public KdTree() {
  }

  public boolean isEmpty() {
    return root == null;
  }

  public int size() {
    return size;
  }

  public void insert(Point2D p) {
    if (p == null)
      throw new IllegalArgumentException("No nulls accepted!");
    if (root == null) {
      root = new Node(p, true, new RectHV(0, 0, 1, 1));
      size = 1;
    }
    else {
      if(root.addChild(p)) ++size;
    }
  }

  public boolean contains(Point2D p) {
    if (p == null)
      throw new IllegalArgumentException("No nulls accepted!");
    if (root == null) return false;
    return root.contains(p);
  }

  public void draw() {
    if (root != null) root.draw();
  }

  public Iterable<Point2D> range(RectHV rect) {
    if (rect == null)
      throw new IllegalArgumentException("No nulls accepted!");
    ArrayList<Point2D> result = new ArrayList<>();
    if (root != null) root.range(rect, result);
    return result;
  }

  public Point2D nearest(Point2D p) {
    if (p == null)
      throw new IllegalArgumentException("No nulls accepted!");
    if (root != null)
      return root.nearest(p, Double.MAX_VALUE, null);
    return null;
  }

  public static void main(String[] args) {
    checkThrowing();
    KdTree test = new KdTree();
    assert test.isEmpty() : "initially set is empty";
    test.insert(new Point2D(0, 0));
    assert !test.isEmpty() : "after first insertion set is empty no more";
    test.insert(new Point2D(0.100, 0));
    test.insert(new Point2D(0.023, 0.094));
    test.insert(new Point2D(0.083, 0.012));
    test.insert(new Point2D(0.055, 0.055));
    assert !test.isEmpty() : "still not empty";
    assert test.size() == 5 : "there must be 5 distinct points";
    test.insert(new Point2D(0.083, 0.012));
    assert test.size() == 5 : "there must be still 5 distinct points";
    boolean yesRes = test.contains(new Point2D(0.023, 0.094));
    assert yesRes : "Must contain the point";
    boolean noRes = test.contains(new Point2D(0.083, 0.055));
    assert !noRes : "Must not contain the point";
    Iterable<Point2D> output =
      test.range(new RectHV(0.012, 0.080, 0.112, 0.110));
    boolean onlyOne = true;
    for (Point2D thePoint : output) {
      if (!onlyOne)
        assert false : "there must be one point";
      onlyOne = false;
      assert thePoint.x() == 0.023 : "point x == 23";
      assert thePoint.y() == 0.094 : "point y == 94";
    }
    Point2D nearestPoint = test.nearest(new Point2D(0.089, 0.040));
    assert nearestPoint.x() == 0.083 : "must be x == 83";
    assert nearestPoint.y() == 0.012 : "must be y == 12";
  }

  private static void checkThrowing() {
    // throw null pointer exception if any argument is null
    KdTree nullTest = new KdTree();
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
