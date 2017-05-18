#include "message.h"
#include "pancakes.h"
#include <stdio.h>
#include <algorithm>

using ll = long long;

ll min_per_node = 5;

int main() {
  ll nodes = NumberOfNodes();
  ll me = MyNodeId();

  ll stack = GetStackSize();
  ll diners = GetNumDiners();

  ll per_node = std::max(min_per_node, stack / nodes + std::min(stack % nodes, 1ll));
  nodes = stack / per_node + std::min(stack % per_node, 1ll);
  if(me >= nodes) return 0;
  ll start = me * per_node;
  ll end = std::min(start + per_node, stack);

  ll rounds = 0;
  if(start == 0) ++start;
  ll last_pancake = GetStackItem(start - 1);
  for(ll i = start; i < end; ++i) {
    ll next_pancake = GetStackItem(i);
    if(next_pancake < last_pancake) ++rounds;
    last_pancake = next_pancake;
  }

  if(me == 0) {
    ll waiting = nodes - 1;
    while(waiting > 0) {
      int received = Receive(-1);
      rounds += GetLL(received);
      --waiting;
    }
    printf("%d\n", rounds + 1);
  } else {
    PutLL(0, rounds);
    Send(0);
  }
  return 0;
}
