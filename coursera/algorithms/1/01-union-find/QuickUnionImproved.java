/**
 * Simple implementation of Unite Find with quick connected test.
 */
public class QuickUnionImproved implements UF {
  private final int[] prev;
  private final int[] size;
  private final int N;

  public QuickUnionImproved(int N) {
    this.N = N;
    prev = new int[N];
    size = new int[N];
    for (int i = 0; i < N; ++i) {
      prev[i] = i;
      size[i] = 1;
    }
  }

  @Override
  public boolean connected(int p, int q) {
    return root(p) == root(q);
  }

  @Override
  public void union(int p, int q) {
    int pr = root(p);
    int qr = root(q);
    if(pr == qr) return;
    if (size[pr] < size[qr]) {
      prev[pr] = qr;
      size[qr] += size[pr];
    } else {
      prev[qr] = pr;
      size[pr] += size[qr];
    }
  }

  protected int root(int p) {
    while (prev[p] != p) {
      //      prev[p] = prev[prev[p]];
      p = prev[p];
    }
    return p;
  }
}
