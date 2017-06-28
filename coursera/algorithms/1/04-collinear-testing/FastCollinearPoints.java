import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.Stopwatch;

public class FastCollinearPoints {

  private final LineSegment[] segments;

  public FastCollinearPoints(Point[] inPoints) {
    if (inPoints == null) throw new IllegalArgumentException();
    int count = inPoints.length;
    for (int i = 0; i < count; ++i) {
      if (inPoints[i] == null) throw new IllegalArgumentException();
    }

    Point[] points = Arrays.copyOf(inPoints, inPoints.length);
    Arrays.sort(points);
    for (int i = 0; i < count - 1; ++i) {
      if (points[i].compareTo(points[i + 1]) == 0)
        throw new IllegalArgumentException();
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
        Point min = pivot.compareTo(points[j]) > 0 ? points[j] : pivot;
        Point max = pivot.compareTo(points[j]) < 0 ? points[j] : pivot;
        while (k < count - 1 &&
              pivot.slopeTo(points[j]) == pivot.slopeTo(points[k + 1])) {
          ++k;
          if (max.compareTo(points[k]) < 0) max = points[k];
          if (min.compareTo(points[k]) > 0) min = points[k];
        }
        if (k - j + 1 >= 3) {
          double newSlope = min.slopeTo(max);
          boolean isRepeat = false;
          for (int r = 0; !isRepeat  && r < lines; ++r) {
            if (starts.get(r).slopeTo(ends.get(r)) == newSlope &&
                (starts.get(r).slopeTo(min) == newSlope ||
                 min.slopeTo(starts.get(r)) == newSlope ||
                 min.compareTo(starts.get(r)) == 0)) {
              if (min.compareTo(starts.get(r)) < 0) starts.set(r, min);
              if (max.compareTo(ends.get(r)) > 0) ends.set(r, max);
              isRepeat = true;
            }
          }
          if (!isRepeat) {
            starts.add(min);
            ends.add(max);
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
    FastCollinearPoints collinear = new FastCollinearPoints(points);
    double time = watch.elapsedTime();
    for (LineSegment segment : collinear.segments()) {
        StdOut.println(segment);
        segment.draw();
    }
    StdOut.printf("time: %.3f%n", time);
    StdDraw.show();
  }
}
