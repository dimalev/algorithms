#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
  int n;
  cin >> n;
  int histo[101];
  for(int i = 0; i < 101; ++i) histo[i] = 0;
  for(int i = 0; i < n; ++i) {
    int k;
    cin >> k;
    histo[k]++;
  }
  int max = 0;
  for(int i = 0; i < n; ++i)
    if(histo[i] > 0 && histo[i] > max) max = histo[i];
  if(n == max) cout << 0 << endl;
  else cout << n - max << endl;
  return 0;
}
