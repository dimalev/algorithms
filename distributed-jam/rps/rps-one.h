// Sample input 2, in CPP.

#include <cassert>

long long GetN() {
  return 28LL;
}

char GetFavoriteMove(long long id) {
  switch ((int)(id % 3)) {
    case 0: return 'R';
    case 1: return 'S';
    case 2: return 'P';
  }
}
