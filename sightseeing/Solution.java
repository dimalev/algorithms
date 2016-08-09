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
    int T = in.readInt();
    for(int t = 0; t < T; ++t)
      solver.solve(t, in, out);
    out.close();
  }

  static class TravelSolution {
    void solve(int testId, InputReader in, OutputWriter out) {
      int n = in.readInt();
      int[][] E = new int[1000][];
      String[] V = new String[1000];
      int totalV = 0;
      for(int i = 0; i < n; ++i) {
        String line = in.nextLine();
        StringTokenizer tokenizer = new StringTokenizer(line, ",");
        int currV, prevV = -1;
        while(tokenizer.hasMoreTokens()) {
          String v = tokenizer.nextToken();
          for(currV = 0; currV < totalV && !V[currV].equals(v); ++currV);
          if(currV == totalV) {
            V[currV] = v;
            E[currV] = new int[1001];
            ++totalV;
          }
          if(prevV >= 0) {
            E[prevV][++E[prevV][0]] = currV;
          }
          prevV = currV;
        }
      }
      int[] S = new int[totalV];
      int[] I = new int[totalV];
      boolean[] B = new boolean[totalV];
      boolean[] C = new boolean[totalV];
      Arrays.fill(B, false);
      Arrays.fill(C, false);
      for(int i = 0; i < totalV; ++i) {
        if(B[i]) continue;
        // System.out.print(i + ":");
        // for(int j = 1; j <= E[i][0]; ++j) System.out.print(" " + E[i][j]);
        // System.out.println();
        S[0] = i; I[0] = 0; B[i] = true; C[i] = true;
        int k = 0;
        while(k >= 0) {
          if(I[k] >= E[S[k]][0]) {
            // System.out.println("leaving " + S[k]);
            C[S[k]] = false;
            --k;
            continue;
          }
          int nextS = E[S[k]][++I[k]];
          if(C[nextS]) {
            // System.out.println(nextS + " is visited");
            out.printLine("ORDER VIOLATION");
            return;
          }
          if(!B[nextS]) {
            // System.out.print(nextS + ":");
            // for(int j = 1; j <= E[nextS][0]; ++j) System.out.print(" " + E[nextS][j]);
            // System.out.println();
            B[nextS] = true;
            C[nextS] = true;
            ++k;
            S[k] = nextS;
            I[k] = 0;
          }
        }
      }
      out.printLine("ORDER EXISTS");
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
        tokenizer = new StringTokenizer(nextLine(), ",");
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
