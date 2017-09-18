#include <iostream>
#include <cassert>
#include <limits>

#define fr(v,s,e) for(long long v = s; v < e; ++v)
#define fl(v,s,e) for(long long v = s; v > e; --v)

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


long long H[9][350][350], V[9][350][350], S[350][350];

long long maxHor(long long r, long long c, long long v) {
  long long res = 0ll, m = 0ll;
  while(v > 0) {
    if(v % 2 == 1) {
      res = std::max(res, H[m][r][c]);
      c += (1 << m);
    }
    v >>= 1;
    ++m;
  }
  return res;
}

long long maxVer(long long r, long long c, long long v) {
  long long res = 0ll, m = 0ll;
  while(v > 0) {
    if(v % 2 == 1) {
      // TRACE_LINE(m << " " << r << " " << c << " " << V[m][r][c]);
      res = std::max(res, V[m][r][c]);
      r += (1 << m);
    }
    v >>= 1;
    ++m;
  }
  return res;
}

void solve(long long t) {
  TRACE_LINE("\n\nTest " << t << " ====================");
  long long n,m;
  long long k;
  std::cin >> n >> m >> k;
  long long min = std::numeric_limits<long long>::max();
  fr(r,0,n) {
    fr(c,0,m) {
      long long v;
      std::cin >> v;
      V[0][r][c] = H[0][r][c] = v;
      if(v == 1000) TRACE_LINE(r << ", " << c);
    }
  }
  // precompute summs
  S[0][0] = H[0][0][0];
  fr(r,1,n) S[r][0] = H[0][r][0] + S[r - 1][0];
  fr(c,1,m) S[0][c] = H[0][0][c] + S[0][c - 1];
  // precompute hash table
  fr(r,1,n) {
    fr(c,1,m) {
      S[r][c] = H[0][r][c] + S[r - 1][c] + S[r][c - 1] - S[r - 1][c - 1];
    }
  }
  fr(h,1,9) {
    long long s = 1 << (h - 1);
    fr(r,0,n) {
      fr(c,0,m-2*s+1) {
        H[h][r][c] = std::max(H[h-1][r][c], H[h-1][r][c+s]);
      }
    }
    fr(r,0,n-2*s+1) {
      fr(c,0,m) {
        V[h][r][c] = std::max(V[h-1][r][c], V[h-1][r+s][c]);
      }
    }
  }
  // fr(r,0,n) {
  //   TRACE(r << ":");
  //   fr(h,1,9) {
  //     if(r + (1 << h) <= n) {
  //       TRACE("\t" << V[h][r][40]);
  //     }
  //   }
  //   TRACE_LINE("");
  // }
  // TRACE_LINE(maxVer(40, 40, 308));
  // fr(h,1,3) {
  //   long long s = 1 << h;
  //   TRACE_LINE(h << " --------");
  //   fr(r,0,n) {
  //     fr(c,0,m-s+1) {
  //       TRACE(H[h][r][c] << "\t");
  //     }
  //     TRACE_LINE("");
  //   }
  // }
  long long res = 0;
  fr(r,0,n) {
    fr(c,0,m) {
      long long maxh = std::min(std::min(r + 1, n - r), std::min(c + 1, m - c));
      long long maxNum = 0ll, need = 0ll;
      fr(h,0,maxh) {
        need += (2 * h + 1) * (2 * h + 1);
        long long maxH = std::max(maxHor(r - h,c - h, 2 * h + 1),
                            maxHor(r + h,c - h, 2 * h + 1));
        long long maxV = std::max(maxVer(r - h,c - h, 2 * h + 1),
                            maxVer(r - h,c + h, 2 * h + 1));
        // if(r == 174 && c == 174) {
        //   TRACE_LINE(r << "," << c << ": (" << h << ") " << maxH << " " << maxV);
        // }
        long long totalMax = std::max(maxH, maxV);
        maxNum = std::max(maxNum, h + totalMax);
        if(maxNum > std::min(n,m)/2) break;
        if(h + 1 > res && totalMax <= 1 && maxNum <= h + 1) {
          long long have = S[r + h][c + h];
          if(r - h > 0) have -= S[r - h - 1][c + h];
          if(c - h > 0) have -= S[r + h][c - h - 1];
          if((r - h > 0) && (c - h > 0))
            have += S[r - h - 1][c - h - 1];
          if(have + k >= need) {
            res = h + 1;
            // TRACE_LINE(r << "," << c << ";" << h << ", " << maxNum << " => "
            //            << have << " + " << k << " ? " << need);
          }
        }
      }
    }
  }
  std::cout << res << std::endl;
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
  long long T;
  std::cin >> T;
  fr(t,0,T) solve(t);
  return 0;
}
