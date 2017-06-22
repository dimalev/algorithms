import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.nio.file.Paths;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class GenRandomTest {
  public static void main(String... argv) {
    if(argv.length < 4) {
      System.out.println("java GenRandomTest " +
                         "%number-of-verticies " +
                         "%number-of-groups " +
                         "%number-of-verticies-per-group " +
                         "%true-false-to-shuffle");
      return;
    }

    int N = Integer.parseInt(argv[0]);
    int G = Integer.parseInt(argv[1]);
    int C = Integer.parseInt(argv[2]);
    boolean shuffle = argv[3].equals("true");

    System.out.println("groups: " + G);

    try(PrintWriter inf = new PrintWriter(Paths.get("input.txt").toFile());
        PrintWriter outf = new PrintWriter(Paths.get("output.txt").toFile())) {
      inf.println(N);
      inf.println((C - 1) * (G + 1));
      List<List<Integer>> connections = new ArrayList<>();
      for(int i = 0; i < G; ++i) {
        connections.add(new ArrayList<Integer>());
        for(int j = 0; j < C; ++j) {
          connections.get(i).add(i * C + j);
        }
        if(shuffle) {
          Collections.shuffle(connections.get(i));
        }
      }
      for(int i = 1; i < C; ++i) {
        for(int j = 0; j < G; ++j) {
          inf.println(String.format("0 %d %d", connections.get(j).get(i - 1),
                                    connections.get(j).get(i)));
        }
        if(i % 2 == 0) {
          inf.println(String.format("1 %d %d", connections.get(i % G).get(i / 2),
                                    connections.get((i + 1) % G).get(i - 1)));
          outf.println(0);
        } else {
          inf.println(String.format("1 %d %d", connections.get(i % G).get(i / 2),
                                    connections.get(i % G).get(i)));
          outf.println(1);
        }
      }
    } catch(FileNotFoundException fnfex) {
      System.out.println("File not found");
      fnfex.printStackTrace();
    }
  }
}
