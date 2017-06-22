import java.util.Scanner;
import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;

public class Benchmark {
    public static class Test {
        public int N;
        public int[][] data;
    }

    public static Test fromFile(File inf, File outf) throws IOException {
        Test test = new Test();
        try(Scanner ins = new Scanner(inf);
                Scanner outs = new Scanner(outf)) {
            int N = ins.nextInt();
            int M = ins.nextInt();
            test.N = N;
            test.data = new int[M][];
            for(int i = 0; i < M; ++i) {
                int type = ins.nextInt();
                int p = ins.nextInt();
                int q = ins.nextInt();
                if(type == 0) {
                    test.data[i] = new int[]{type, p, q};
                } else if(type == 1) {
                    int res = outs.nextInt();
                    test.data[i] = new int[]{type, p, q, res};
                }
            }
        }
        return test;
    }

    public static void main(String... argv) {
        Test test = null;
        try {
            test = fromFile(
                Paths.get("tests", "input-0.txt").toFile(),
                Paths.get("tests", "output-0.txt").toFile()
            );
        } catch(IOException ioex) {
            System.err.println("Unable to initialize tests");
            return;
        }
        System.out.println("Runtime: " + time(new QuickFind(test.N), test));
    }

    public static long time(UF algo, Test test) {
        long start = System.currentTimeMillis();
        int l = test.data.length;
        for(int i = 0; i < l; ++i) {
            switch(test.data[i][0]) {
            case 0:
                algo.union(test.data[i][1], test.data[i][2]);
                break;
            case 1:
                boolean res = algo.connected(test.data[i][1], test.data[i][2]);
                if(res != (test.data[i][3] == 1)) {
                    throw new Error("Algorithm Failed!");
                }
                break;
            }
        }
        long end = System.currentTimeMillis();
        return end - start;
    }
}
