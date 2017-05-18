#include "message.h"
#include "crates.h"
#include <stdio.h>
#include <algorithm>

using ll = long long;

constexpr ll MOD = 1e9 + 7;

// Nodes send messages in a chain pattern: 0->1->2->3->..., each node waiting to
// receive the previous message before beginning the next one.
// For a hundred nodes and NumberOfWaves == 1, this program will execute
// 400-500ms.
int main() {
  ll nodes = NumberOfNodes();
  ll me = MyNodeId();

  ll N = GetNumStacks();

  ll per_node = std::max(2ll, N / nodes);
  if(N / per_node + std::min(N % per_node, 1ll) < nodes) {
    nodes = N / per_node + std::min(N % per_node, 1ll);
  }
  ll start = per_node * me;
  ll end = std::min(start + per_node, N);

  if(me >= nodes) return 0; // this node does not have job :(

  // Round One - count crates available
  ll total = 0;
  for(ll runner = start; runner < end; ++runner) {
    total += GetStackHeight(runner + 1);
  }

  // Round Two - find C
  ll C = 0, K = 0;
  if(me == 0) {
    ll super_total = total, waiting = nodes - 1;
    while(waiting > 0) {
      ll sender = Receive(-1);
      super_total += GetLL(sender);
      --waiting;
    }
    C = super_total / N;
    K = super_total % N;
    for(int i = 1; i < nodes; ++i) {
      PutLL(i, C);
      PutLL(i, K);
      Send(i);
    }
    printf("C=%d, K=%d\n", C, K);
  } else {
    PutLL(0, total);
    Send(0);
    Receive(0);
    C = GetLL(0);
    K = GetLL(0);
  }

  // Round Three - in series count  leftover
  ll leftover = 0;
  ll converge = 0;
  if(me == 0) {
    converge = total -
        (std::min(K, end) - std::min(K, start)) * (C + 1) -
        (std::max(K, end) - std::max(K, start)) * C;
    PutLL(me + 1, converge);
    Send(me + 1);
  } else {
    Receive(me - 1);
    leftover = GetLL(me - 1);
    converge = total + leftover -
        (std::min(K, end) - std::min(K, start)) * (C + 1) -
        (std::max(K, end) - std::max(K, start)) * C;
    if(me < nodes - 1) {
      PutLL(me + 1, converge);
      Send(me + 1);
    }
  }

  // Round Four - we count moves we have to do on our piece
  ll diff = GetStackHeight(start + 1) + leftover - (start < K ? (C + 1) : C);
  ll steps = abs(diff);
  for(ll runner = start + 1; runner < end; ++runner) {
    diff = GetStackHeight(runner + 1) + diff - (runner < K ? (C + 1) : C);
    steps = (steps + abs(diff)) % MOD;
  }

  if(me == 0) {
    ll super_steps = steps, waiting = nodes - 1;
    while(waiting > 0) {
      ll sender = Receive(-1);
      super_steps = (super_steps + GetLL(sender)) % MOD;
      --waiting;
    }
    printf("%d\n", super_steps);
  } else {
    PutLL(0, steps);
    Send(0);
  }
  return 0;
}
