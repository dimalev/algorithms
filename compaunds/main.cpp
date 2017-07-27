#include <iostream>
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

class link {
  link *children[26], *root;
  bool is_terminal = false;
 public:
  link() : root{this} {
    std::fill_n(children, 26, nullptr);
  }
  link(link *_root) : root{_root} {
    std::fill_n(children, 26, nullptr);
  }
  ~link() {
    fr(i,0,26)
        if(children[i] != nullptr) delete children[i];
  }
  bool isTerminal() const { return is_terminal; }
  void isTerminal(bool v) { is_terminal = v; }
  link* emplace_child(char c) {
    assert(c >= 'a' && c <= 'z');
    if(children[c - 'a'] == nullptr) {
      children[c - 'a'] = new link(root);
    }
    return children[c - 'a'];
  }
  void add(const char *word) {
    if(word[0] == '\0') {
      isTerminal(true);
      return;
    }
    emplace_child(word[0])->add(word + 1);
  }

  bool find(const char *word, const int &depth) {
    if(depth < 0) return false;
    if(word[0] == '\0') {
      if(depth == 0 && isTerminal()) return true;
      return false;
    }
    if(isTerminal()) {
      if(root->find(word, depth - 1)) return true;
    }
    if(children[word[0] - 'a'] == nullptr) return false;
    return children[word[0] - 'a']->find(word + 1, depth);
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
  int V, N;
  link root;
  std::cin >> V;
  std::cin.ignore();
  fr(i,0,V) {
    char name[255];
    std::cin.getline(name, 255);
    root.add(name);
  }
  std::cin >> N;
  std::cin.ignore();
  fr(i,0,N) {
    char word[255];
    std::cin.getline(word, 255);
    if(root.find(word, 1)) std::cout << word << std::endl;
  }
  return 0;
}
