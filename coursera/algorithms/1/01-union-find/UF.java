/**
 * Union-find data type interface.
 */
public interface UF {
    /**
     * Unite two nodes.
     */
    void union(int p, int q);

    /**
     * Check if two nodes are connected.
     */
    boolean connected(int p, int q);
}
