#include "message.h"
#include "task.h"
#include <stdio.h>

using ll = long long;

int main() {
  ll nodes = NumberOfNodes();
  ll me = MyNodeId();
  if(me == 0) {
    sprinf("OK\n");
  }
  return 0;
}
