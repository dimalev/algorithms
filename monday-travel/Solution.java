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
import java.util.List;
import java.util.LinkedList;

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
    int n;
    String[] cities = new String[21];
    int time[] = new int[21];
    int E[][] = new int[21][21];
    boolean[] visited = new boolean[21];
    List<Integer> best = null;
    List<Integer> current = new LinkedList<Integer>();

    void seek(int from, int days, int hours, int d) {
      if(time[from] >= hours) {
        int more = time[from] - hours;
        days -= 1 + more / 16;
        hours = 16 - more % 16;
      } else hours -= time[from];
      // System.out.println(from + ": " + days + " " + hours);
      if(days < 0 || (days == 0 && hours < 16) ) return;
      visited[from] = true;
      current.add(from);
      if(current.size() > 1) {
        if(best == null || best.size() < current.size()) {
          best = new LinkedList<Integer>();
          best.addAll(current);
        }
      }
      for(int i = 1; i <= n; ++i) {
        if(visited[i] || E[from][i] == 0) continue;
        if(E[from][i] > hours) {
          if(E[from][i] < 16) seek(i, days - 1, 16 - E[from][i], d + 1);
          else seek(i, days - 2, 16, d + 1);
        } else {
          if(E[from][i] < hours) seek(i, days, hours - E[from][i], d + 1);
          else seek(i, days - 1, 16, d + 1);
        }
      }
      current.remove(d);
      visited[from] = false;
    }

    int getId(String city) {
      for(int i = 0; i <= n; ++i)
        if(cities[i].equals(city)) return i;
      return -1;
    }

    void solve(int testId, InputReader in, OutputWriter out) {
      n = in.readInt();
      cities[0] = "Bevagna";
      time[0] = 0;
      for(int i = 1; i <= n; ++i) {
        cities[i] = in.readWord();
        time[i] = Integer.parseInt(in.readWord());
      }
      int m = in.readInt();
      for(int i = 0; i < m; ++i) {
        int c1 = getId(in.readWord());
        int c2 = getId(in.readWord());
        int dur = Integer.parseInt(in.readWord());
        if(dur > 16) continue;
        E[c1][c2] = dur;
        E[c2][c1] = dur;
      }
      seek(0, 6, 16, 0);
      if(best == null) out.printLine("NONE");
      else {
        for(int i = 1; i < best.size(); ++i)
          out.printLine(cities[best.get(i)]);
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
