import java.io.*;
import java.util.*;

public class Solution {

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int size = input.nextInt();
    input.nextLine();
    int px = -1, py = -1, mx = -1, my = -1;
    for(int i = 0; i < size; ++i) {
      String line = input.nextLine();
      System.out.println(line);
      int ppos = line.indexOf('p');
      int mpos = line.indexOf('m');
      if(ppos >= 0) {
        px = ppos;
        py = i;
      }
      if(mpos >= 0) {
        mx = mpos;
        my = i;
      }
    }
    System.out.println(px + "," + py + " " + mx + "," + my);
    for(int i = 0; i < py - my; ++i) System.out.println("DOWN");
    for(int i = 0; i < my - py; ++i) System.out.println("UP");
    for(int i = 0; i < px - mx; ++i) System.out.println("RIGHT");
    for(int i = 0; i < mx - px; ++i) System.out.println("LEFT");
  }
}
