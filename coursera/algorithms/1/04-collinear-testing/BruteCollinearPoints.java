import java.util.Arrays;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;

public class BruteCollinearPoints {
  private final LineSegment[] segments;

  public BruteCollinearPoints(Point[] points) {
    if (points == null) throw new IllegalArgumentException();
    int count = points.length;
    LineSegment[] tempSegments = new LineSegment[count];
    for (int i = 0; i < count; ++i) {
      if (points[i] == null) throw new IllegalArgumentException();
    }
    for (int i = 0; i < count; ++i) {
      for (int j = i + 1; j < count; ++j) {
        if (points[i].compareTo(points[j]) == 0)
          throw new IllegalArgumentException();
      }
    }

    int lines = 0;

    for (int i = 0; i < count - 3; ++i)
      for (int j = i + 1; j < count - 2; ++j)
        for (int k = j + 1; k < count - 1; ++k)
          for (int t = k + 1; t < count; ++t) {
            Point[] heroes = new Point[]{points[i], points[j],
                                         points[k], points[t]};
            Arrays.sort(heroes);
            if (heroes[0].slopeTo(heroes[1]) == heroes[1].slopeTo(heroes[2]) &&
                heroes[1].slopeTo(heroes[2]) == heroes[2].slopeTo(heroes[3])) {
              tempSegments[lines] = new LineSegment(heroes[0], heroes[3]);
              ++lines;
            }
          }
    segments = Arrays.copyOf(tempSegments, lines);
  }

  public int numberOfSegments() {
    return segments.length;
  }

  public LineSegment[] segments() {
    return Arrays.copyOf(segments, segments.length);
  }

  public static void main(String... args) {
    // read the n points from a file
    In in = new In(args[0]);
    int n = in.readInt();
    Point[] points = new Point[n];
    for (int i = 0; i < n; i++) {
        int x = in.readInt();
        int y = in.readInt();
        points[i] = new Point(x, y);
    }

    // draw the points
    StdDraw.enableDoubleBuffering();
    StdDraw.setXscale(0, 32768);
    StdDraw.setYscale(0, 32768);
    for (Point p : points) {
        p.draw();
    }
    StdDraw.show();

    // print and draw the line segments
    BruteCollinearPoints collinear = new BruteCollinearPoints(points);
    for (LineSegment segment : collinear.segments()) {
        StdOut.println(segment);
        segment.draw();
    }
    StdDraw.show();
  }
}
