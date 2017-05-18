#include "message.h"
#include "weird_editor.h"
#include <stdio.h>
#include <algorithm>

using ll = long long;

ll min_per_node = 5;
constexpr ll MOD = 1e9 + 7;

int main() {
  ll nodes = NumberOfNodes();
  ll me = MyNodeId();

  ll L = GetNumberLength();
  ll per_node = std::max(min_per_node, L / nodes + std::min(1LL, L % nodes));
  nodes = L / per_node + std::min(1LL, L % per_node);
  if(me >= nodes) return 0;
  ll start = per_node * me;
  ll end = std::min(start + per_node, L);
  // printf("%d(%d): %d-%d\n", me, nodes, start, end);

  // Round one - leftmost occurence
  ll rightmost[10];
  std::fill_n(rightmost, 10, -1);
  for(ll i = start; i < end; ++i) {
    ll d = GetDigit(i);
    if(d > 0) rightmost[d] = i;
  }

  ll limit[10];
  limit[9] = 0;
  if(me == 0) {
    ll to_wait = nodes - 1;
    while(to_wait > 0) {
      ll received = Receive(-1);
      for(ll i = 1; i < 10; ++i) {
        ll pos = GetLL(received);
        if(rightmost[i] < pos)
          rightmost[i] = pos;
      }
      --to_wait;
    }

    // printf("%d: %d %d %d %d %d %d %d %d %d\n", me, rightmost[1], rightmost[2],
    //        rightmost[3], rightmost[4], rightmost[5], rightmost[6],
    //        rightmost[7], rightmost[8], rightmost[9]);

    // Round two - where to start count?
    ll start = std::max(0LL, rightmost[9]);
    for(ll i = 8; i > 0; --i) {
      if(rightmost[i] >= start) {
        limit[i] = start;
        start = rightmost[i];
      } else {
        limit[i] = -1;
      }
    }

  // printf("%d: %d %d %d %d %d %d %d %d %d\n", me, limit[1], limit[2],
  //        limit[3], limit[4], limit[5], limit[6],
  //        limit[7], limit[8], limit[9]);

    for(ll i = 1; i < nodes; ++i) {
      for(ll j = 1; j < 9; ++j) {
        PutLL(i, limit[j]);
      }
      Send(i);
    }
  } else {
    for(ll i = 1; i < 10; ++i) {
      PutLL(0, rightmost[i]);
    }
    Send(0);
    Receive(0);
    for(ll i = 1; i < 9; ++i) {
      limit[i] = GetLL(0);
    }
  }

  // Round three - count occurences
  ll occur[10];
  std::fill_n(occur, 10, 0);
  for(ll i = start; i < end; ++i) {
    ll d = GetDigit(i);
    if(d != 0 && limit[d] != -1 && i >= limit[d])
      ++occur[d];
  }

  // collect
  ll end_pos[10];
  end_pos[0] = L;
  if(me == 0) {
    ll to_wait = nodes - 1;
    while(to_wait > 0) {
      ll received = Receive(-1);
      for(ll i = 1; i < 10; ++i) {
        ll count = GetLL(received);
        occur[i] += count;
      }
      --to_wait;
    }
    end_pos[9] = occur[9];
    for(ll i = 8; i > 0; --i) {
      end_pos[i] = end_pos[i + 1] + occur[i];
    }
    // printf("%d: %d %d %d %d %d %d %d %d %d\n", me, end_pos[1], end_pos[2],
    //        end_pos[3], end_pos[4], end_pos[5], end_pos[6],
    //        end_pos[7], end_pos[8], end_pos[9]);
    for(int i = 1; i < nodes; ++i) {
      for(int j = 1; j < 10; ++j) {
        PutLL(i, end_pos[j]);
      }
      Send(i);
    }
  } else {
    for(ll i = 1; i < 10; ++i) {
      PutLL(0, occur[i]);
    }
    Send(0);
    Receive(0);
    for(int j = 1; j < 10; ++j) {
      end_pos[j] = GetLL(0);
    }
  }
  ll d = 9LL;
  ll mult = 1LL;
  ll val = 0LL;
  for(ll i = start; i < end; ++i) {
    while(i >= end_pos[d]) --d;
    // if(me == 0) printf("%d", d);
    val = (val * 10 + d) % MOD;
    mult = mult * 10 % MOD;
  }
  // if(me == 0) printf("\n");
  if(me == 0) {
    if(nodes > 1) {
      PutLL(1, val);
      Send(1);
      Receive(nodes - 1);
      val = GetLL(nodes - 1);
    }
    printf("%d\n", val);
  } else if(me < nodes - 1) {
    Receive(me - 1);
    ll big_val = GetLL(me - 1);
    big_val = (big_val * mult) % MOD;
    val = (big_val + val) % MOD;
    PutLL(me + 1, val);
    Send(me + 1);
  } else {
    Receive(me - 1);
    ll big_val = GetLL(me - 1);
    big_val = (big_val * mult) % MOD;
    val = (big_val + val) % MOD;
    PutLL(0, val);
    Send(0);
  }
  return 0;
}
