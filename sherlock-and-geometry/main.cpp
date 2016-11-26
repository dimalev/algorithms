#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

inline int sqr(int x) { return x * x; }

int cross(int *pivot, int *from, int *to) {
  return (from[0] - pivot[0]) * (to[1] - pivot[1]) - (from[1] - pivot[1]) * (to[0] - pivot[0]);
}

int dot(int *pivot, int *from, int *to) {
  return (from[0] - pivot[0]) * (to[0] - pivot[0]) + (from[1] - pivot[1]) * (to[1] - pivot[1]);
}

double length(int *from, int *to) {
  return sqrt(sqr(to[0] - from[0]) + sqr(to[1] - from[1]));
}

bool circle_intersects_segment(int *center, int r, int *one, int *two) {
  //cout << setprecision(2);
  //cout << "line: " << one[0] << " " << one[1] << " && " << two[0] << " " << two[1] << "\n";
  double ABl = length(one, two);
  //cout << "|AB| = " << ABl << "\n";
  double H = cross(one, center, two) / ABl;
  //cout << "|CC'| = " << H << "\n";
  if(abs(H) > r) return false;
  double AC = dot(one, center, two) / ABl;
  //cout << "|AC'| = " << AC << "\n";
  double L = sqrt(sqr(r) - sqr(H));
  //cout << "|L| = " << L << "\n"; 
  if(AC + L < 0 && AC - L < 0) return false;
  if(AC + L > ABl && AC - L > ABl) return false;
  return true;
}

void solve() {
  int cx, cy, r;
  cin >> cx >> cy >>r;
  int r2 = sqr(r);
  bool is_intersect = false, is_inside = false, is_outside = false;
  int center[2] = { cx, cy };
  int points[3][2];
  for(int i = 0; i < 3; ++i) {
    int x, y;
    cin >> x >> y;
    int l2 = sqr(x - cx) + sqr(y - cy);
    if(l2 == r2) is_intersect = true;
    else if(l2 < r2) is_inside = true;
    else is_outside = true;
    points[i][0] = x;
    points[i][1] = y;
  }
  if(is_intersect) {
    cout << "YES\n";
  } else if(is_inside) {
    if(is_outside) cout << "YES\n";
    else cout << "NO\n";
  } else {
    if(circle_intersects_segment(center, r, points[0], points[1]) ||
      circle_intersects_segment(center, r, points[0], points[2]) ||
      circle_intersects_segment(center, r, points[2], points[1])) {
      cout << "YES\n";
    } else cout << "NO\n";
  }
}

int main() {
    int T;
  cin >> T;
  while(T--) solve();
    return 0;
}
