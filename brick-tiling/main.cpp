#include <iostream>
#include <map>

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

int masks[] = {
  0b0110000100001000000000000,
  0b0100001000011000000000000,
  0b0011000100001000000000000,
  0b0001000010001100000000000,
  0b0000000111001000000000000,
  0b0000000001001110000000000,
  0b0000000000001110000100000,
  0b0000000000001000011100000,
  0b0000000000001000010000110,
  0b0000000000001100001000010,
  0b0000000000001000010001100,
  0b0000000000011000100001000,
  0b0000000000001001110000000,
  0b0000000000111001000000000,
  0b0000010000111000000000000,
  0b0000011100001000000000000
};

std::map<int, std::map<int, ll>> migrations;

void generateMigrations(int top) {
  
}

std::map<int, ll> getMigrations(int top, int bottom) {
  st::map<int, ll> res;
  if(migrations.find(top) == migrations.end()) {
    generateMigrations(top);
  }
  for(auto pair : migrations[top]) {
    int res_bottom = pair.first;
    if(res_bottom && bottom != 0) continue;
    ll count = pair.second;
    res.add(res_bottom, count);
  }
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
  
  return 0;
}
