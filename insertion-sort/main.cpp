#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <cassert>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

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
class node {
  int keys[3];
  node* children[4], *parent;
  int key_count, size;
  bool is_leaf;
 public:
  node() : key_count{0}, parent{nullptr}, is_leaf{true}, size{0} {
    std::fill_n(children, 3, nullptr);
  }

  node(node* parent) : key_count{0}, parent{parent}, is_leaf{true}, size{0} {
    std::fill_n(children, 3, nullptr);
  }

  node(std::tuple<node*, int, node*> parts) : parent{nullptr} {
    key_count = 1;
    std::tie(children[0], keys[0], children[1]) = parts;
    children[0]->parent = children[1]->parent = this;
    children[2] = nullptr;
    is_leaf = false;
    size = children[0]->size + children[1]->size + 1;
  }

  int getKeyCount() const { return key_count; }

  node* getParent() const { return parent; }

  node* push(int v) {
    ++size;
    if(is_leaf) {
      keys[key_count++] = v;
      std::sort(keys, keys + key_count);
      return this;
    }
    fr(i,0,key_count) {
      if(v < keys[i])
        return children[i]->push(v);
    }
    return children[key_count]->push(v);
  }

  std::tuple<node*, int, node*> split() {
    assert(key_count == 3);
    if(is_leaf) {
      node *left = new node();
      node *right = new node();
      left->push(keys[0]);
      right->push(keys[2]);
      return std::make_tuple(left, keys[1], right);
    }
    node *left = new node(std::make_tuple(children[0], keys[0], children[1]));
    node *right = new node(std::make_tuple(children[2], keys[2], children[3]));
    return std::make_tuple(left, keys[1], right);
  }

  void replace(node *child, std::tuple<node*, int, node*> subtree) {
    assert(!is_leaf);
    assert(key_count < 3);
    int p = 0;
    while(children[p] != child) ++p;
    fl(i, key_count, p) {
      keys[i] = keys[i - 1];
      children[i + 1] = children[i];
    }

    std::tie(children[p], keys[p], children[p + 1]) = subtree;
    children[p]->parent = children[p + 1]->parent = this;
    ++key_count;
  }

  int bigger(int v) {
    if(is_leaf) {
      fr(i, 0, key_count) {
        if(v >= keys[key_count - i - 1])
          return i;
      }
      return key_count;
    } else {
      int res = 0;
      fr(i, 0, key_count) {
        if(v < keys[key_count - 1 - i]) {
          res += children[key_count -i]->size;
        } else if(v == keys[key_count - 1 - i]) {
          res += children[key_count - i]->bigger(v);
          return res + i;
        } else {
          return res + i + children[key_count - i]->bigger(v);
        }
      }
      return res + key_count + children[0]->bigger(v);
    }
  }
};

class tree {
  node *root;
 public:
  tree() : root{nullptr} {}

  void add(int v) {
    if(root == nullptr) {
      root = new node();
    }
    node *leaf = root->push(v);
    while(leaf->getKeyCount() > 2) {
      std::tuple<node*, int, node*> parts = leaf->split();
      if(leaf->getParent() == nullptr) {
        delete leaf;
        leaf = root = new node(parts);
      } else {
        node *parent = leaf->getParent();
        // std::cout << "leaf: ";
        // *leaf << std::cout;
        // std::cout << "\nparent: ";
        // *parent << std::cout;
        // std::cout << "\n";
        parent->replace(leaf, leaf->split());
        delete leaf;
        leaf = parent;
      }
    }
  }

  int bigger(int v) {
    if(root == nullptr) return 0;
    return root->bigger(v);
  }
};

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

void solve() {
  int N;
  std::cin >> N;
  tree t;
  long res = 0;
  fr(i,0,N) {
    int k;
    std::cin >> k;
    res += t.bigger(k);
    t.add(k);
  }
  std::cout << res << std::endl;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  fr(t,0,T) solve();
  return 0;
}
