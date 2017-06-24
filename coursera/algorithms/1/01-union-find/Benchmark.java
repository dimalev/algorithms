import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stopwatch;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Benchmark {
    public static class Test {
        public int N;
        public int[][] data;
    }

    public static Test fromFile(In inf, In outf) {
        Test test = new Test();
        int N = inf.readInt();
        int M = inf.readInt();
        test.N = N;
        test.data = new int[M][];
        for (int i = 0; i < M; ++i) {
            int type = inf.readInt();
            int p = inf.readInt();
            int q = inf.readInt();
            if (type == 0) {
                test.data[i] = new int[]{type, p, q};
            } else if (type == 1) {
                int res = outf.readInt();
                test.data[i] = new int[]{type, p, q, res};
            }
        }
        return test;
    }

    public static void main(String... argv) {
        System.out.println("Reading test 1...");
        Test test = fromFile(
          new In("tests/input-1.txt"),
          new In("tests/output-1.txt")
        );
        System.out.println("Reading test 2...");
        Test testBig = fromFile(
          new In("tests/input-2.txt"),
          new In("tests/output-2.txt")
        );
        System.out.println();
        System.out.println("\tQF\tQU\tQUi\tWQUUF");

        System.out.print("1e" + Math.round(Math.log10(test.N)));
        System.out.print("\t" + time(new QuickFind(test.N), test));
        System.out.print("\t" + time(new QuickUnion(test.N), test));
        System.out.print("\t" + time(new QuickUnionImproved(test.N), test));
        System.out.println("\t" + time(new Adapter(test.N), test));

        System.out.print("1e" + Math.round(Math.log10(testBig.N)) + "\tx");
        System.out.print("\t" + time(new QuickUnion(testBig.N), testBig));
        System.out.print("\t" + time(new QuickUnionImproved(testBig.N), testBig));
        System.out.println("\t" + time(new Adapter(testBig.N), testBig));
    }

    public static double time(UF algo, Test test) {
        int l = test.data.length;
        Stopwatch watch = new Stopwatch();
        for (int i = 0; i < l; ++i) {
            switch(test.data[i][0]) {
            case 0:
                algo.union(test.data[i][1], test.data[i][2]);
                break;
            case 1:
                boolean res = algo.connected(test.data[i][1], test.data[i][2]);
                if (res != (test.data[i][3] == 1)) {
                    throw new Error("Algorithm Failed! " + i);
                }
                break;
            }
        }
        return watch.elapsedTime();
    }

  static class Adapter implements UF {
    private final WeightedQuickUnionUF algo;

    public Adapter(int size) {
      algo = new WeightedQuickUnionUF(size);
    }

    public void union(int p, int q) {
      algo.union(p, q);
    }

    public boolean connected(int p, int q) {
      return algo.connected(p, q);
    }
  }
}
