#include <iostream>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  int F[n], towers = 0;
  F[0] = 0;
  for(int i = 0; i < n; ++i) {
    int b;
    cin >> b;
    if(b) {
      ++towers;
      F[towers] = k;
      for(int i = towers; i > 0; --i) {
        if(F[i - 1] < k) F[i] = -k + 1;
        else ++F[i];
      }
      F[0]++;
    } else {
      for(int i = 0; i <= towers; ++i) {
        ++F[i];
      }
    }
    // for(int k = 0; k <= towers; ++k) {
    //   cout << " - " << F[k] << endl;
    // }
    // cout << "-----" << endl;
  }
  for(int i = 0; i <= towers; ++i) {
    // cout << " - " << F[i] << endl;
    if(F[i] < 1) {
      cout << i << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}
