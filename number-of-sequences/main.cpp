#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long mod = 1000000007;

class Prime {
public:
  int value;
  int count = 0;
  int boundCount = 0;
};

Prime prime[10000];
int prime_count = 0;

int main() {
  int n;
  cin >> n;
  for(int i = 1; i <= n; ++i) {
    int v;
    cin >> v;
    if(i > 1) {
      bool is_prime = true;
      int copy = i;
      if(v == -1) {
        for(int j = 0; j < prime_count; ++j) {
          if(i % prime[j].value == 0) {
            is_prime = false;
            int count = 0;
            while(copy % prime[j].value == 0) {
              ++count;
              copy /= prime[j].value;
            }
            if(count > prime[j].count) prime[j].count = count;
            if(copy == 1) break;
          }
        }
      } else {
        for(int j = 0; j < prime_count; ++j) {
          if(i % prime[j].value == 0) {
            is_prime = false;
            int count = 0;
            while(copy % prime[j].value == 0) {
              ++count;
              copy /= prime[j].value;
            }
            if(count > prime[j].count) prime[j].count = count;
            if(count > prime[j].boundCount) prime[j].boundCount = count;
            if(copy == 1) break;
          }
        }
      }
      if(is_prime) {
        prime[prime_count].value = i;
        prime[prime_count].count = 1;
        if(v != -1) {
          prime[prime_count].boundCount = 1;
        }
        prime_count++;
      }
    }
  }
  long long result = 1;
  for(long long i = 0; i < prime_count; ++i) {
    //cout << prime[i].value << " " << prime[i].boundCount << " -> " << prime[i].count << endl;
    for(int cc = prime[i].boundCount; cc < prime[i].count; ++cc)
      result = (result * ((long long)prime[i].value)) % mod;
  }
  cout << result << endl;
  return 0;
}
