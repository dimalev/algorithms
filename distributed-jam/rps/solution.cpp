#include "message.h"
#include "rps-one.h"
#include <stdio.h>

using ll = long long;

constexpr ll min_per_wave = 010;
constexpr ll max_per_mini_wave = 1 << 10;
constexpr ll max_per_wave = 1 << 22;

class player {
 public:
  char c;
  ll id;
  player() : c{'\0'}, id{-1} {}
  player(char c, ll id) : c{c}, id{id} {}
  player(const player& other) : c{other.c}, id{other.id} {}
  player(const player&& other) : c{other.c}, id{other.id} {}

  void init(char c, ll id) {
    this->c = c;
    this->id = id;
  }

  player& operator=(const player& other) {
    this->c = other.c;
    this->id = other.id;
    return *this;
  }

  bool wins(const player &other) {
    switch(c) {
      case 'S': return other.c != 'R';
      case 'P': return other.c != 'S';
      case 'R': return other.c != 'P';
    }
  }

  void Send(int target) {
    PutChar(target, c);
    PutLL(target, id);
  }

  void Get(int target) {
    c = GetChar(target);
    id = GetLL(target);
  }
};

player find_winner(ll left_id, ll right_id) {
  if(right_id - left_id == 2) {
    player left{GetFavoriteMove(left_id), left_id};
    player right{GetFavoriteMove(right_id - 1), right_id - 1};
    if(left.wins(right)) return left;
    return right;
  }
  ll middle_id = (left_id + right_id) / 2;
  player left = find_winner(left_id, middle_id);
  player right = find_winner(middle_id, right_id);
  if(left.wins(right)) return left;
  return right;
}

inline ll min(ll one, ll two) { return one > two ? two : one; }

int main() {
  ll first = 0; long long last = 1 << GetN();
  ll per_wave_raw = last / NumberOfNodes();
  ll per_wave = min_per_wave;
  while(per_wave < per_wave_raw) per_wave <<= 1;
  ll start = per_wave * MyNodeId();
  ll end = min(last, start + per_wave);
  if(start >= last) return 0;
  player winner = find_winner(start, end);
  winner.Send(0);
  Send(0);

  if (MyNodeId() == 0) {
    ll to_wait = last / per_wave, got = 0;
    player G[100];
    while(got < to_wait) {
      int recieved = Receive(-1);
      G[recieved].Get(recieved);
      ++got;
    }
    ll count = to_wait;
    while(count > 1) {
      for(ll i = 0; i < count / 2; ++i) {
        G[i] = (G[2 * i].wins(G[2 * i + 1]) ? G[2 * i] : G[2 * i + 1]);
      }
      count /= 2;
    }
    printf("%d\n", G[0].id);
  }
  return 0;
}
