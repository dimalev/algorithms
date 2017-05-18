#include "message.h"
#include "todd_and_steven.h"
#include <stdio.h>
#include <algorithm>

using ll = long long;

constexpr ll min_per_node = 3L;
constexpr ll MOD = 1e9 + 7;

ll T, S;

ll GetExtendedToddValue(ll id) {
  if(id >= T) return 5 * 1e9;
  return GetToddValue(id);
}

ll GetExtendedStevenValue(ll id) {
  if(id >= S) return 5 * 1e9;
  return GetStevenValue(id);
}

int main() {
  ll nodes = NumberOfNodes();
  ll me = MyNodeId();

  T = GetToddLength();
  S = GetStevenLength();
  ll count = T + S;
  ll per_node = std::max(min_per_node, count / nodes + std::min(1LL, count % nodes));
  nodes = count / per_node + std::min(1LL, count % per_node);
  if(me >= nodes) return 0;
  ll start = me * per_node;
  ll end = std::min(start + per_node, count);

  ll left = 0, right = std::min(start, T);
  ll todd;
  ll steven;
  ll it = 0;
  while(left <= right) {
    todd = (left + right) / 2;
    steven = start - todd;
    ll odd = GetExtendedToddValue(todd);
    ll even = GetExtendedStevenValue(steven);
    if(odd > even) {
      if(todd > 0) {
        ll odd_prev = GetExtendedToddValue(todd - 1);
        if(odd_prev < even) break;
        else {
          right = todd;
          // if(right > todd) right = todd;
          // else right = todd - 1;
        }
      } else break;
    } else if(odd < even) {
      if(steven > 0) {
        ll even_prev = GetExtendedStevenValue(steven - 1);
        if(even_prev < odd) break;
        else  {
          if(left < todd) left = todd;
          else left = todd + 1;
        }
      } else break;
    }
  }

  ll sum = 0LL;
  ll next_s = GetExtendedStevenValue(steven);
  ll next_t = GetExtendedToddValue(todd);
  for(ll i = start; i < end; ++i) {
    // printf("%d t=%d s=%d\n", i, todd, steven);
    if(next_t < next_s) {
      sum = (sum + (i ^ next_t)) % MOD;
      ++todd;
      next_t = GetExtendedToddValue(todd);
    } else {
      sum = (sum + (i ^ next_s)) % MOD;
      ++steven;
      next_s = GetExtendedStevenValue(steven);
    }
  }

  if(me == 0) {
    ll to_wait = nodes - 1;
    while(to_wait > 0) {
      ll received = Receive(-1);
      ll next_sum = GetLL(received);
      sum = (sum + next_sum) % MOD;
      --to_wait;
    }
    printf("%d\n", sum);
  } else {
    PutLL(0, sum);
    Send(0);
  }
  return 0;
}
