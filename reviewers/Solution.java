import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.IOException;
import java.io.Reader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.InputStream;
import java.util.Map;
import java.util.HashMap;

public class Solution {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    OutputWriter out = new OutputWriter(outputStream);
    TravelSolution solver = new TravelSolution();
    solver.solve(1, in, out);
    out.close();
  }

  static class TravelSolution {
    void solve(int testId, InputReader in, OutputWriter out) {
      int n = in.readInt(), m = in.readInt();
      String[] passions = new String[n];
      for(int i = 0; i < n; ++i) {
        passions[i] = in.nextLine().toLowerCase();
      }
      Map<Integer, int[]> reviewers = new HashMap<Integer, int[]>();
      int[] bestScore = new int[n];
      int[] bestId = new int[n];
      for(int i = 0; i < m; ++i) {
        int id = in.readInt(), time = in.readInt();
        String body = in.nextLine().toLowerCase();
        int[] reviewer = reviewers.get(id);
        if(reviewer == null) {
          reviewer = new int[n];
          reviewers.put(id, reviewer);
        }
        int score = ((time < 1465948800 || time > 1468540799) ? 10 : 20) +
          (body.length() < 100 ? 10 : 20);
        for(int j = 0; j < n; ++j) {
          if(body.indexOf(passions[j]) < 0) continue;
          reviewer[j] += score;
          if(reviewer[j] > bestScore[j]) {
            bestScore[j] = reviewer[j];
            bestId[j] = id;
          } else if(reviewer[j] == bestScore[j] && id < bestId[j]) bestId[j] = id;
        }
      }
      for(int i = 0; i < n; ++i) {
        out.printLine(bestScore[i] > 0 ? bestId[i] : -1);
      }
    }
  }

  static class InputReader {
    private BufferedReader reader;
    private StringTokenizer tokenizer;

    public InputReader(Reader reader) {
      this.reader = new BufferedReader(reader);
    }

    public InputReader(InputStream stream) {
      this(new InputStreamReader(stream));
    }

    public String nextLine() {
      try {
        return reader.readLine();
      } catch (IOException e) {
        throw new RuntimeException(e);
      }
    }

    public String readWord() {
      while (tokenizer == null || !tokenizer.hasMoreTokens()) {
        tokenizer = new StringTokenizer(nextLine());
      }
      return tokenizer.nextToken();
    }

    public int readInt() {
      return Integer.parseInt(readWord());
    }

    public int[] readIntArray(int size) {
      int[] result = new int[size];
      for (int i = 0; i < size; i++) {
        result[i] = readInt();
      }
      return result;
    }
  }

  static class OutputWriter {
    private PrintWriter writer;

    public OutputWriter(Writer writer) {
      this.writer = new PrintWriter(writer);
    }

    public OutputWriter(OutputStream stream) {
      this(new OutputStreamWriter(stream));
    }

    public void print(Object... args) {
      for (Object arg : args) {
        writer.print(arg);
      }
    }

    public void printLine(Object... args) {
      print(args);
      writer.println();
    }

    void close() {
      writer.close();
    }
  }
}
