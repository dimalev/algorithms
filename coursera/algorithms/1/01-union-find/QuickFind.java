/**
 * Simple implementation of Unite Find with quick connected test.
 */
public class QuickFind implements UF {
    private final int[] color;
    private final int N;

    public QuickFind(int N) {
        this.N = N;
        color = new int[N];
        for (int i = 0; i < N; ++i) {
            color[i] = i;
        }
    }

    @Override
    public boolean connected(int p, int q) {
        return color[p] == color[q];
    }

    @Override
    public void union(int p, int q) {
        int c = color[p];
        if (color[q] != c) {
            for (int i = 0; i < N; ++i) {
                if (color[i] == c) color[i] = color[q];
            }
        }
    }
}
