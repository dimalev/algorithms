import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
  private final double[] tests;
  public PercolationStats(int n, int traits) {
    if (n <= 0) throw new IllegalArgumentException();
    if (traits <= 0) throw new IllegalArgumentException();
    tests = new double[traits];
    int[] indeces = new int[n * n];
    for (int i = 0; i < n * n; ++i) {
      indeces[i] = i;
    }
    for (int i = 0; i < traits; ++i) {
      Percolation tester = new Percolation(n);
      StdRandom.shuffle(indeces);
      int j = 0;
      for (; j < n * n && !tester.percolates(); ++j) {
        tester.open(indeces[j] / n + 1, indeces[j] % n + 1);
      }
      tests[i] = (double) j / (double) (n * n);
    }
  }

  public double mean() {
    return StdStats.mean(tests);
  }

  public double stddev() {
    return StdStats.stddev(tests);
  }
  public double confidenceLo() {
    return mean() - 1.96 * stddev() / Math.sqrt(tests.length);
  }
  public double confidenceHi() {
    return mean() + 1.96 * stddev() / Math.sqrt(tests.length);
  }

  public static void main(String[] args) {
    int n = Integer.parseInt(args[0]);
    int traits = Integer.parseInt(args[1]);
    PercolationStats stats = new PercolationStats(n, traits);
    System.out.println("mean                    = " + stats.mean());
    System.out.println("stddev                  = " + stats.stddev());
    System.out.println("95% confidence interval = [" + stats.confidenceLo() +
                       ", " + stats.confidenceHi() + "]");
  }
}
