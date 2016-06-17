import java.io.*;
import java.util.*;

public class Solution {

  static class Vector {
    int target;
    int distance;

    public Vector(int target, int distance) {
      this.target = target;
      this.distance = distance;
    }
  }

  static class Node {
    int id;
    int kid = -1;
    int current = 0;
    int lastLength = 0;

    long distance;
    boolean mustTraverse = false;
    long inOut = Long.MAX_VALUE; // we enter this node, we exit this node
    long inOnly = Long.MAX_VALUE; // we enter this node, exit does not matter
    long outOnly = Long.MAX_VALUE; // we start anywhere, we exit through this node
    long any = Long.MAX_VALUE; // we start anywhere, we end anywhere, maybe omitting this node
    long anyInclusive = Long.MAX_VALUE; // we start anywhere, we end anywhere, visiting this node

    List<Vector> outbound = new LinkedList<Vector>();

    public Node(int id) { this.id = id; }

    public String toString() {
      return "[" + (id + 1) + ": " +
        "io=" + inOut + ", " +
        "i=" + inOnly + ", " +
        "o=" + outOnly + ", " +
        "a=" + any + ", " +
        "d=" + distance + "]";
    }
  }

  static int N, K;
  static List<Integer> Ks = new LinkedList<Integer>();
  static Node[] nodes;

  static void updateDists(int parent, int target) {
    List<Node> toGoThrough = new LinkedList<Node>();
    for(Vector child : nodes[target].outbound) {
      if(child.target == parent) continue;
      updateDists(target, child.target);
      if(nodes[child.target].mustTraverse) {
        nodes[child.target].distance = child.distance;
        toGoThrough.add(nodes[child.target]);
      }
    }
    if(toGoThrough.size() == 0) {
      if(nodes[target].kid >= 0) {
        nodes[target].mustTraverse = true;
        nodes[target].inOut = 0L;
        nodes[target].inOnly = 0L;
        nodes[target].outOnly = 0L;
        nodes[target].any = 0L;
        nodes[target].anyInclusive = 0L;
      }
    } else if(toGoThrough.size() == 1) {
      nodes[target].mustTraverse = true;
      nodes[target].inOut = toGoThrough.get(0).inOut + 2 * toGoThrough.get(0).distance;
      nodes[target].inOnly = toGoThrough.get(0).inOnly + toGoThrough.get(0).distance;
      nodes[target].outOnly = toGoThrough.get(0).outOnly + toGoThrough.get(0).distance;
      nodes[target].anyInclusive = Math.min(Math.min(Math.min(nodes[target].inOnly, nodes[target].outOnly),
                                                     nodes[target].inOut),
                                            toGoThrough.get(0).anyInclusive + 2 * toGoThrough.get(0).distance);
      if(nodes[target].kid >= 0)
        nodes[target].any = nodes[target].anyInclusive;
      else nodes[target].any = toGoThrough.get(0).any;
    } else {
      nodes[target].mustTraverse = true;
      int pathes = toGoThrough.size();
      long whenSomeIsAnyInclusive = Long.MAX_VALUE;
      for(int i = -1; i < pathes; ++i) {
        long ll = 0;
        for(int k = 0; k < pathes; ++k) {
          if(k == i)
            ll += toGoThrough.get(k).anyInclusive + 2 * toGoThrough.get(k).distance;
          else ll += toGoThrough.get(k).inOut + 2 * toGoThrough.get(k).distance;
        }
        whenSomeIsAnyInclusive = Math.min(whenSomeIsAnyInclusive, ll);
      }
      nodes[target].any = whenSomeIsAnyInclusive;
      for(int i = 0; i < pathes; ++i) {
        for(int j = 0; j < pathes; ++j) {
          if(i == j) continue;
          long ll = 0;
          for(int k = 0; k < pathes; ++k) {
            if(k == i)
              ll += toGoThrough.get(k).inOnly + toGoThrough.get(k).distance;
            else if(k == j)
              ll += toGoThrough.get(k).outOnly + toGoThrough.get(k).distance;
            else ll += toGoThrough.get(k).inOut + 2 * toGoThrough.get(k).distance;
          }
          nodes[target].any = Math.min(nodes[target].any, ll);
        }
      }
      nodes[target].inOut = 0L;
      for(int k = 0; k < pathes; ++k)
        nodes[target].inOut += toGoThrough.get(k).inOut + 2 * toGoThrough.get(k).distance;
      for(int i = 0; i < pathes; ++i) {
        Long inOnly = 0L;
        Long outOnly = 0L;
        for(int k = 0; k < pathes; ++k) {
          if(k == i) {
            inOnly += toGoThrough.get(k).inOnly + toGoThrough.get(k).distance;
            outOnly += toGoThrough.get(k).outOnly + toGoThrough.get(k).distance;
          } else {
            outOnly += toGoThrough.get(k).inOut + 2 * toGoThrough.get(k).distance;
            inOnly += toGoThrough.get(k).inOut + 2 * toGoThrough.get(k).distance;
          }
        }
        nodes[target].inOnly = Math.min(nodes[target].inOnly, inOnly);
        nodes[target].outOnly = Math.min(nodes[target].outOnly, outOnly);
      }
      nodes[target].any = nodes[target].anyInclusive =
        Math.min(Math.min(nodes[target].any, nodes[target].inOnly),
                 Math.min(nodes[target].outOnly, nodes[target].inOut));
    }
  }

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    N = input.nextInt();
    K = input.nextInt();
    nodes = new Node[N];
    for(int i = 0; i < K; ++i) {
      Ks.add(input.nextInt() - 1);
    }
    Node biggest = null;
    for(int j = 0; j < N - 1; ++j) {
      int from = input.nextInt() - 1;
      int to = input.nextInt() - 1;
      int distance = input.nextInt();

      if(null == nodes[from]) {
        nodes[from] = new Node(from);
        if(Ks.contains(from)) nodes[from].kid = Ks.indexOf(from);
      }
      if(null == nodes[to]) {
        nodes[to] = new Node(to);
        if(Ks.contains(to)) nodes[to].kid = Ks.indexOf(to);
      }

      nodes[from].outbound.add(new Vector(to, distance));
      nodes[to].outbound.add(new Vector(from, distance));
      if(nodes[from].outbound.size() > nodes[to].outbound.size()) {
        if(null == biggest || biggest.outbound.size() < nodes[from].outbound.size())
          biggest = nodes[from];
      } else {
        if(null == biggest || biggest.outbound.size() < nodes[to].outbound.size())
          biggest = nodes[to];
      }
    }
    updateDists(-1, biggest.id);
    System.out.println(nodes[biggest.id].any);
  }
}
