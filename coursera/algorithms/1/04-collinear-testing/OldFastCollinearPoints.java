import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.Stopwatch;

public class OldFastCollinearPoints {

  private final LineSegment[] segments;

  public OldFastCollinearPoints(Point[] points) {
    if (points == null) throw new IllegalArgumentException();
    int count = points.length;
    for (int i = 0; i < count; ++i) {
      if (points[i] == null) throw new IllegalArgumentException();
    }
    for (int i = 0; i < count; ++i) {
      for (int j = i + 1; j < count; ++j) {
        if (points[i].compareTo(points[j]) == 0)
          throw new IllegalArgumentException();
      }
    }

    List<Point> starts = new ArrayList<>();
    List<Point> ends = new ArrayList<>();
    int lines = 0;
    for (int i = 0; i < count - 3; ++i) {
      Arrays.sort(points, i, count);
      Point pivot = points[i];
      Arrays.sort(points, i + 1, count, points[i].slopeOrder());
      int j = i + 1;
      while (j < count - 1) {
        int k = j;
        while (k < count - 1 &&
              pivot.slopeTo(points[j]) == pivot.slopeTo(points[k + 1])) {
          ++k;
        }
        if (k - j + 1 >= 3) {
          Arrays.sort(points, j, k + 1);
          boolean isRepeat = false;
          for (int r = 0; !isRepeat  && r < lines; ++r) {
            if (ends.get(r).compareTo(points[k]) == 0 &&
                starts.get(r).slopeTo(ends.get(r)) ==
                points[i].slopeTo(points[k])) {
              isRepeat = true;
            }
          }
          if (!isRepeat) {
            starts.add(points[i]);
            ends.add(points[k]);
            ++lines;
          }
        }
        j = k + 1;
      }
    }
    segments = new LineSegment[lines];
    for (int i = 0; i < lines; ++i) {
      segments[i] = new LineSegment(starts.get(i), ends.get(i));
    }
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
    Stopwatch watch = new Stopwatch();
    OldFastCollinearPoints collinear = new OldFastCollinearPoints(points);
    double time = watch.elapsedTime();
    for (LineSegment segment : collinear.segments()) {
        StdOut.println(segment);
        segment.draw();
    }
    StdOut.printf("time: %.3f%n", time);
    StdDraw.show();
  }
}
