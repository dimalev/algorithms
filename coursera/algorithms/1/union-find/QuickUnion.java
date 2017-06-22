/**
 * Simple implementation of Unite Find with quick connected test.
 */
public class QuickUnion implements UF {
  private final int[] prev;
  private final int N;

  public QuickUnion(int N) {
    this.N = N;
    prev = new int[N];
    for(int i = 0; i < N; ++i) {
      prev[i] = i;
    }
  }

  @Override
  public boolean connected(int p, int q) {
    return root(p) == root(q);
  }

  @Override
  public void union(int p, int q) {
    prev[root(q)] = prev[root(p)];
  }

  protected int root(int p) {
    while(prev[p] != p) {
      p = prev[p];
    }
    return p;
  }
}
