#include <iostream>
#include <vector>
#include <memory>
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
 public:
  explicit node(int left, int right, long value)
      : left_{left},
        right_{right},
        is_terminal_{true},
        value_{value} {}

  explicit node(int left, int right)
      : node(left, right, 0) {}

  int left() const { return left_; }
  int right() const { return right_; }

  node* left_node() const {
    if(is_terminal_) return nullptr;
    return left_node_.get();
  }

  node* right_node() const {
    if(is_terminal_) return nullptr;
    return right_node_.get();
  }

  long at(int pos) const {
    assert(pos >= left_);
    assert(pos <= right_);
    if(is_terminal_) return value_;
    if(left_node_->right() >= pos) return left_node_->at(pos);
    return right_node_->at(pos);
  }

  bool is_terminal() const { return is_terminal_; }

  void split() {
    if(!is_terminal_) return;
    if(left_ == right_) return;
    int mid = (left_ + right_) / 2;
    TRACE_LINE("split " << left_ << ":" << right_ << " at " << mid);
    left_node_.reset(new node(left_, mid, value_));
    right_node_.reset(new node(mid + 1, right_, value_));
    is_terminal_ = false;
  }

  long get_value() const {
    assert(is_terminal_);
    return value_;
  }

  void mul(int from, int to, long long new_value) {
    if(is_terminal_) {
      if(from <= left_ && to >= right_) {
        value_ *= new_value;
        return;
      } else {
        split();
      }
    }
    if(left_node_->right() >= from) left_node_->mul(from, to, new_value);
    if(right_node_->left() <= to) right_node_->mul(from, to, new_value);
  }

  void inc(int from, int to, long long new_value) {
    if(is_terminal_) {
      if(from <= left_ && to >= right_) {
        value_ += new_value;
        return;
      } else {
        split();
      }
    }
    if(left_node_->right() >= from) left_node_->inc(from, to, new_value);
    if(right_node_->left() <= to) right_node_->inc(from, to, new_value);
  }

 private:
  int left_, right_;
  bool is_terminal_;
  long long value_;
  std::unique_ptr<node> left_node_, right_node_;
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
  int n, m;
  std::cin >> n >> m;
  node increments(0, n - 1, 0), repeats(0, m - 1, 1);
  std::vector<command> commands;
  commands.reserve(m);
  fr(i,0,m) {
    int type, left, right;
    std::cin >> type >> left >> right;
    --left; --right;
    commands.push_back({type, left, right});
  }
  fl(i,m-1,-1) {
    command next = commands[i];
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
