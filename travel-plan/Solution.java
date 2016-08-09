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
import java.util.Set;
import java.util.TreeSet;
import java.util.List;
import java.util.ArrayList;

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
    float degree2radians(float deg) { return deg * 3.14159265359f / 180f; }

    float d(Venture point1, Venture point2) {
      float R = 6371;
      float point1_lat_in_radians  = degree2radians( point1.lt );
      float point2_lat_in_radians  = degree2radians( point2.lt );
      float point1_long_in_radians  = degree2radians( point1.ln );
      float point2_long_in_radians  = degree2radians( point2.ln );

      return (float)(Math.acos( Math.sin( point1_lat_in_radians ) * Math.sin( point2_lat_in_radians ) +
                              Math.cos( point1_lat_in_radians ) * Math.cos( point2_lat_in_radians ) *
                              Math.cos( point2_long_in_radians - point1_long_in_radians) ) ) * R;
    }

    void solve(int testId, InputReader in, OutputWriter out) {
      int n = in.readInt();
      Set<String> passions = new TreeSet<String>();
      for(int i = 0; i < n; ++i) {
        int m = in.readInt();
        for(int j = 0; j < m; ++j) {
          passions.add(in.readWord());
        }
      }

      n = in.readInt();
      List<Venture> ventures = new ArrayList<Venture>(n);
      for(int i = 0; i < n; ++i) {
        Venture v = new Venture();
        v.name = in.readWord();
        v.lt = Float.parseFloat(in.readWord());
        v.ln = Float.parseFloat(in.readWord());
        int m = in.readInt();
        for(int j = 0; j < m; ++j) {
          String passion = in.readWord();
          if(!passions.contains(passion)) continue;
          v.passions.add(passion);
        }
        ventures.add(v);
      }

      Venture v1 = null, v2 = null;
      int maxPassions = 0;
      for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
          if(ventures.get(i).passions.size() + ventures.get(j).passions.size() < maxPassions) continue;
          Set<String> common = new TreeSet<String>();
          common.addAll(ventures.get(i).passions);
          common.addAll(ventures.get(j).passions);
          if(common.size() > maxPassions) {
            maxPassions = common.size();
            v1 = ventures.get(i);
            v2 = ventures.get(j);
          } else if(common.size() == maxPassions) {
            if(v1 == null || (d(v1,v2) > d(ventures.get(i), ventures.get(j)))) {
              maxPassions = common.size();
              v1 = ventures.get(i);
              v2 = ventures.get(j);
            }
          }
        }
      }

      if(v1.name.compareTo(v2.name) > 0) out.print(v2.name, " ", v1.name);
      else out.print(v1.name, " ", v2.name);
    }
  }

  static class Venture {
    public Set<String> passions = new TreeSet<String>();
    public String name;
    public float lt, ln;
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
