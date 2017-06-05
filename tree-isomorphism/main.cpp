#include <iostream>
#include <vector>

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

class tree {
  int id, fingerprint;
  std::vector<tree*> siblins;
  int last_fingerprint = -1;
  std::vector<tree*> last_allowed;
 public:
  explicit tree(int id) : id{id}, fingerprint{1 << id} {
  }

  void add_siblin(tree *siblin) {
    siblins.push_back(siblin);
  }

  inline bool is_allowed(int fingers) const {
    return (fingers & fingerprint) != 0;
  }

  std::vector<tree*> get_allowed(int allowed) {
    if(last_fingerprint == allowed) return last_allowed;
    last_fingerprint = allowed;
    last_allowed.clear();
    for(int i = 0; i < siblins.size(); ++i) {
      if((siblins[i]->fingerprint & allowed) != 0)
        last_allowed.push_back(siblins[i]);
    }
    return last_allowed;
  }

  int get_id() const {
    return id;
  }

  bool isomorfic(tree *other, int fingers, int other_fingers, int parent,
                 int other_parent) {
    std::vector<tree*> allowed = get_allowed(fingers);
    std::vector<tree*> other_allowed = other->get_allowed(other_fingers);
    if(allowed.size() != other_allowed.size()) return false;
    if(allowed.size() == 0) return true;
    bool checks[allowed.size()];
    for(int i = 0; i < allowed.size(); ++i) {
      checks[i] = allowed[i]->id == parent;
    }
    for(int i = 0; i < allowed.size(); ++i) {
      if(other_allowed[i]->id == other_parent) continue;
      bool found = false;
      for(int j = 0; !found && j < allowed.size(); ++j) {
        if(!checks[j]) {
          if(allowed[j]->isomorfic(other_allowed[i], fingers, other_fingers,
                                   id, other->id)) {
            checks[j] = true;
            found = true;
          }
        }
      }
      if(!found) return false;
    }
    return true;
  }

  int vote(int fingers) {
    if(fingers == 0) return 0;
    if((fingers & fingerprint) == 0) return fingers;
    // TRACE_LINE("voting " << fingerprint << " for " << fingers);
    fingers = (~fingerprint) & fingers;
    for(tree *siblin : siblins)
      fingers = siblin->vote(fingers);
    return fingers;
  }
};

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
  int N;
  std::cin >> N;
  std::vector<tree*> trees;
  for(int i = 0; i < N; ++i) trees.push_back(new tree(i));
  for(int i = 0; i < N - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u; --v;
    trees[u]->add_siblin(trees[v]);
    trees[v]->add_siblin(trees[u]);
  }
  std::vector<std::pair<tree*, int>> uniques[N + 1];
  int T = 1 << N, res = 0;
  for(int i = 1; i < T; ++i) {
  // int i = 6;
    bool is_connected = true;
    int root = -1;
    for(int j = 0; j < N; ++j) {
      if(trees[j]->is_allowed(i)) {
        root = j;
        if(trees[j]->vote(i) == 0) {
          break;
        } else {
          is_connected = false;
          break;
        }
      }
    }
    if(!is_connected) continue;
    int size = 0, i2 = i;
    while(i2 > 0) {
      if(i2 % 2 == 1) size++;
      i2 >>= 1;
    }
    bool is_unique = true;
    // TRACE_LINE(i << " has size " << size);
    for(auto unique : uniques[size]) {
      for(int k = 0; k < N; ++k) {
        if(trees[k]->is_allowed(i)) {
          if(unique.first->isomorfic(trees[k], unique.second, i, -1, -1)) {
            is_unique = false;
            break;
          }
        }
      }
      if(!is_unique) break;
    }
    if(!is_unique) continue;
    uniques[size].push_back(std::make_pair(trees[root], i));
    // TRACE_LINE("unique: " << i);
    ++res;
  }
  std::cout << res << std::endl;
  return 0;
}
