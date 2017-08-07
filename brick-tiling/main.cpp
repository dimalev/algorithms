#include <iostream>
#include <map>
#include <bitset>
#include <string>
#include <sstream>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

using ll = long long;

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

using grid4 = unsigned int;
using grid2 = unsigned int;

constexpr ll MOD = 1e9 + 7;

grid4 masks[] = {
  // up to 5 cells to right
  0b10000000111000000000000000000000,
  0b11100000001000000000000000000000,
  0b00100000111000000000000000000000,
  0b11100000100000000000000000000000,
  // up to 6 cells to right
  0b11000000100000001000000000000000,
  0b11000000010000000100000000000000,
  0b10000000100000001100000000000000,
  0b01000000010000001100000000000000
};

std::map<grid2, std::map<grid2, ll>> migrations;

std::string grid2ToString(grid2 grid) {
  std::stringstream out;
  out << std::bitset<8>(grid >> 8) << "\n"
      << std::bitset<8>(grid & 0b11111111);
  return out.str();
}

std::string grid4ToString(grid4 grid) {
  return grid2ToString(grid >> 16) + "\n" +
    grid2ToString(grid & 0b1111111111111111);
}

void fill(grid2 mask, grid4 state, int pos) {
  if(pos == 16) {
    // TRACE_LINE("accepting:\n" << grid4ToString(state) << "\n");
    migrations[mask][state & 0b1111111111111111] = (migrations[mask][state & 0b1111111111111111] + 1) % MOD;
    return;
  }
  //std::cout << "pos = " << pos << "\n" << grid4ToString(state) << "\n\n";
  grid4 head = (1 << (31 - pos));
  if((state & head) == head) fill(mask, state, pos + 1);
  if(pos % 8 < 6) {
    fr(i,0,8) {
      grid4 brick = (masks[i] >> pos);
      if((state & brick) == 0 && // new brick does not intersect obstacles
         (((state | brick) & head) == head)) {// and covers given cell
        // std::cout << "pos = " << pos << "\n" << grid4ToString(state | brick) << "\n\n";
        // std::cout << "brick:\n" << grid4ToString(brick) << "\n\n";
        fill(mask, state | brick, pos + 1);
      }
    }
  } else if(pos % 8 < 7) {
    fr(i,4,8) {
      grid4 brick = (masks[i] >> pos);
      if((state & brick) == 0 && // new brick does not intersect obstacles
         (((state | brick) & head) == head)) {// and covers given cell
        // std::cout << "pos = " << pos << "\n" << grid4ToString(state | brick) << "\n\n";
        fill(mask, state | brick, pos + 1);
      }
    }
  }
}

std::map<grid2, ll> getMigrations(grid2 top) {
  // st::map<grid2, ll> res;
  if(migrations.find(top) == migrations.end()) {
    fill(top, top << 16, 0);
  }
  // for(auto pair : migrations[top]) {
  //   int res_bottom = pair.first;
  //   if((res_bottom & bottom) != 0) continue;
  //   ll count = pair.second;
  //   res.add(res_bottom, count);
  // }
  return migrations[top];
}

void solve() {
  int n, m;
  std::cin >> n >> m;
  char buffer[9];
  int rows[20];
  fr(r,0,n) {
    std::cin >> buffer;
    TRACE_LINE(buffer);
    int line = 0;
    fr(c,0,m) {
      line = (line << 1) + (buffer[c] == '.' ? 0 : 1);
    }
    fr(c,m,8) line = (line << 1) + 1;
    rows[r] = line;
  }
  if(n % 2 == 1) {
    rows[n] = (1 << 8) - 1;
    ++n;
  }
  std::map<grid2, ll> vars;
  vars[0] = 1; // empty configuration
  TRACE_LINE("n = " << n );
  fr(r2,0,n/2) {
    grid2 top = (rows[r2 * 2] << 8) + rows[r2 * 2 + 1];
    TRACE_LINE("processing:\n" << grid2ToString(top) << "\n");
    std::map<grid2, ll> next_vars;
    for(auto pair : vars) {
      grid2 conf = pair.first;
      if((conf & top) != 0) continue;
      TRACE_LINE("conf:\n" << grid2ToString(conf) << "\n");
      ll count = pair.second;
      std::map<grid2, ll> bottoms = getMigrations(conf | top);
      for(auto pair2 : bottoms) {
        next_vars[pair2.first] =
          (next_vars[pair2.first] + (count * pair2.second) % MOD) % MOD;
      }
    }
    vars = next_vars;
  }
  std::cout << vars[0] << std::endl;
}

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
  // fill(0b0000111100001111, 0b00001111000011111111111111111111, 0);
  // return 0;
  int T;
  std::cin >> T;
  fr(t,0,T) solve();
  return 0;
}
