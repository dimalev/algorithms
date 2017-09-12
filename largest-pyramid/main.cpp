#include <iostream>
#include <cassert>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

int M[350][350], HS[350][350][175], VS[350][350][175];
long long HC[350][350][175], VC[350][350][175];

void solve(int t) {
  int n,m;
  long long k;
  std::cin >> n >> m >> k;
  int ms = std::min(n, m) / 2 + std::min(n, m) % 2;
  int min = -1;
  fr(r,0,n) {
    fr(c,0,m) {
      std::cin >> M[r][c];
      if(M[r][c] == 1 && min == -1) {
        min = 0;
      } else if(M[r][c] == 0 && k > 0 && min == -1) {
        min = 0;
      }
      fr(s,0,ms) {
        if(M[r][c] > s + 1) {
          VS[r][c][s] = HS[r][c][s] = 0;
          VC[r][c][s] = HC[r][c][s] = 0ll;
        } else {
          int phs = 0, pvs = 0;
          long long phc = 0ll, pvc = 0ll;
          if(r > 0) {
            pvs = VS[r - 1][c][s];
            pvc = VC[r - 1][c][s];
          }
          if(c > 0) {
            phs = HS[r][c - 1][s];
            phc = HC[r][c - 1][s];
          }
          VS[r][c][s] = pvs + 1;
          VC[r][c][s] = pvc + s + 1 - M[r][c];
          HS[r][c][s] = phs + 1;
          HC[r][c][s] = phc + s + 1 - M[r][c];
        }
      }
    }
  }
  if(min != 0) {
    std::cout << "0\n";
    return;
  }
  fr(r,0,n) {
    fr(c,0,m) {
      int mx = std::min(ms, std::min(n - r, m - c) / 2 + std::min(n - r, m - c) % 2) - 1;
      fl(s,mx,min) {
        bool can = true;
        long long sum = 0ll;
        fr(d,0,s+1) {
          int l = 2 * (s - d + 1) - 1;
          assert(c + d + l - 1 < m);
          assert(r + d + l - 1 < n);
          if(HS[r + d][c + d + l - 1][d] < l) {
            can = false;
            break;
          }
          if(HS[r + d + l - 1][c + d + l - 1][d] < l) {
            can = false;
            break;
          }
          if(VS[r + d + l - 1][c + d][d] < l) {
            can = false;
            break;
          }
          if(VS[r + d + l - 1][c + d + l - 1][d] < l) {
            can = false;
            break;
          }
          long long cost = 0ll;
          if(l == 1) {
            cost = (d + 1) - M[r + d][c + d];
          } else {
            cost = HC[r + d][c + d + l - 1][d] - HC[r + d][c + d][d] +
              HC[r + d + l - 1][c + d + l - 1][d] - HC[r + d + l - 1][c + d][d] +
              VC[r + d + l - 1][c + d][d] - VC[r + d][c + d][d] +
              VC[r + d + l - 1][c + d + l - 1][d] - VC[r + d][c + d + l - 1][d] -
              ((d + 1) - M[r + d + l - 1][c + d + l - 1]) + ((d + 1) - M[r + d][c + d]);
          }
          sum += cost;
          if(sum > k) {
            can = false;
            break;
          }
        }
        if(can) {
          min = s;
          break;
        }
      }
    }
  }
  std::cout << (min + 1) << std::endl;
}

// 0123456 01234
// 1111111 11111
// 1222221 12221
// 1233321 12321
// 1234321


#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  fr(t,0,T) solve(t);
  return 0;
}
