#include <iostream>
#include <vector>
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

constexpr long long mod = 1e9 + 7;

class node {
 public:
  explicit node(int left, int right, long value)
      : left_{left},
        right_{right},
        is_terminal_{true},
        is_temp_{false},
        value_{value} {}

  explicit node(int left, int right)
      : node(left, right, 0) {}

  int left() const { return left_; }
  int right() const { return right_; }

  long at(int pos) const {
    assert(pos >= left_);
    assert(pos <= right_);
    if(is_terminal_) return value_;
    if(is_temp_) {
      left_node_->inc(left_, right_, value_);
      right_node_->inc(left_, right_, value_);
      is_temp_ = false;
      value_ = 0ll;
    }
    if(left_node_->right() >= pos) return left_node_->at(pos);
    return right_node_->at(pos);
  }

  void split() {
    assert(is_terminal_);
    assert(left_ != right_);
    int mid = (left_ + right_) / 2;
    TRACE_LINE("split " << left_ << ":" << right_ << " at " << mid);
    left_node_ = new node(left_, mid, value_);
    right_node_ = new node(mid + 1, right_, value_);
    value_ = 0ll;
    is_terminal_ = false;
  }

  void inc(int from, int to, long long new_value) {
    if(is_terminal_) {
      if(from <= left_ && to >= right_) {
        value_ = (value_ + new_value) % mod;
        return;
      } else {
        split();
      }
    }
    if(from <= left_ && to >= right_) {
      is_temp_ = true;
      value_ = (value_ + new_value) % mod;
    } else {
      if(is_temp_) {
        left_node_->inc(left_, right_, value_);
        right_node_->inc(left_, right_, value_);
        value_ = 0ll;
        is_temp_ = false;
      }
      if(left_node_->right() >= from) left_node_->inc(from, to, new_value);
      if(right_node_->left() <= to) right_node_->inc(from, to, new_value);
    }
  }

 private:
  int left_, right_;
  bool is_terminal_;
  mutable bool is_temp_;
  mutable long long value_;
  node *left_node_, *right_node_;
};

// class segtree {
//  public:
//   explicit segtree(int min, int max, long long value)
//       : root_(min, max, value) {}

//  private:
//   std::unique_ptr<node> root_;
// };

struct command {
  int type, left, right;
};

void solve(int t) {
  TRACE_LINE("-------------------- " << t);
  int n, m;
  std::cin >> n >> m;
  node increments(0, n - 1, 0), repeats(0, m - 1, 1);
  command commands[m];
  fr(i,0,m) {
    int type, left, right;
    std::cin >> type >> left >> right;
    --left; --right;
    commands[i].type = type;
    commands[i].left = left;
    commands[i].right = right;
  }
  fl(i,m-1,-1) {
    const command& next = commands[i];
    TRACE_LINE(i << " x" << repeats.at(i));
    if(next.type == 1) {
      increments.inc(next.left, next.right, repeats.at(i));
    } else {
      repeats.inc(next.left, next.right, repeats.at(i));
    }
  }
  fr(i,0,n) {
    if(i > 0) std::cout << " ";
    std::cout << increments.at(i);
  }
  std::cout << std::endl;
}

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
  int T;
  std::cin >> T;
  fr(t,0,T) solve(t);
  return 0;
}
