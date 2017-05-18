#include <message.h>
#include <limits>
#include <stdio.h>
#include "oops-three.h"

#define MASTER_NODE 7

int main() {
  long long N = GetN();
  long long nodes = NumberOfNodes();
  long long my_id = MyNodeId();
  long long best_so_far = 0LL;
  long long minimum = std::numeric_limits<long long>::max();
  long long maximum = std::numeric_limits<long long>::min();
  for (long long j = 0; j <= N / nodes + 1; ++j) {
    if (j * nodes + my_id < N) {
      long long candidate = GetNumber(j * nodes + my_id);
      if (candidate > maximum) maximum = candidate;
      if (candidate < minimum) minimum = candidate;
    }
  }
  PutLL(MASTER_NODE, maximum);
  PutLL(MASTER_NODE, minimum);
  Send(MASTER_NODE);

  if (my_id == MASTER_NODE) {
    long long global_maximum = std::numeric_limits<long long>::min();
    long long global_minimum = std::numeric_limits<long long>::max();
    for (int node = 0; node < nodes; ++node) {
      Receive(node);
      long long received_maximum = GetLL(node);
      long long received_minimum = GetLL(node);
      if (received_maximum > global_maximum) global_maximum = received_maximum;
      if (received_minimum < global_minimum) global_minimum = received_minimum;
    }
    printf("%lld\n", (global_maximum - global_minimum));
  }
  return 0;
}
//14849307
