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
    public int n;
    public int owners[] = new int[100];
    public boolean available[] = new boolean[100];
    public boolean blocked[] = new boolean[100];
    public int[][] P2E = new int[100][101];

    boolean canTake(int player, int event) {
      if(!available[event]) return false;
      if(owners[event] == 0) {
        return true;
      }
      int other = owners[event] - 1;
      int original = P2E[other][0];
      while(--P2E[other][0] > 0) {
        if(canTake(other, P2E[other][P2E[other][0]])) {
          P2E[other][0] = original;
          return true;
        }
      }
      P2E[other][0] = original;
      return false;
    }

    void take(int player, int event) {
      if(owners[event] == 0) {
        owners[event] = player + 1;
        return;
      }
      int other = owners[event] - 1;
      owners[event] = player + 1;
      while(--P2E[other][0] > 0) {
        if(canTake(other, P2E[other][P2E[other][0]])) {
          take(other, P2E[other][P2E[other][0]]);
          return;
        }
      }
    }

    void solve(int testId, InputReader in, OutputWriter out) {
      n = in.readInt();
      String[] passions = new String[1000];
      int[][] passioners = new int[1000][1001];
      int total_passions = 0;
      Arrays.fill(available, false);
      for(int i = 0; i < n; ++i) {
        int t = in.readInt(), pc = in.readInt();
        available[t - 1] = true;
        for(int j = 0; j < pc; ++j) {
          String passion = in.readWord();
          int k;
          for(k = 0; k < total_passions && !passions[k].equals(passion); ++k);
          if(k == total_passions) {
            passions[total_passions] = passion;
            passioners[total_passions] = new int[1001];
            ++total_passions;
          }
          passioners[k][++passioners[k][0]] = i;
        }
      }
      for(int i = 0; i < n; ++i) {
        int m = in.readInt();
        for(int j = 0; j < m; ++j) {
          String passion = in.readWord();
          int k;
          for(k = 0; k < total_passions && !passions[k].equals(passion); ++k);
          if(k == total_passions) continue;
          for(int p = 1; p <= passioners[k][0]; ++p) {
            int passioner = passioners[k][p];
            if(P2E[passioner][0] == 0 || P2E[passioner][P2E[passioner][0]] < i) {
              P2E[passioner][++P2E[passioner][0]] = i;
            }
          }
        }
      }
      int total = 0;
      Arrays.fill(owners, 0);
      for(int i = 0; i < n; ++i) {
        while(P2E[i][0] > 0) {
          if(canTake(i, P2E[i][P2E[i][0]])) {
            take(i, P2E[i][P2E[i][0]]);
            ++total;
            break;
          } else --P2E[i][0];
        }
      }
      out.printLine(total);
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
