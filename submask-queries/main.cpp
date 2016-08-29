#include <iostream>
#include <set>

class sub_array {
public:
  static bool contains(const int &super, const int &sub) { return sub == (sub & super); }

  void add(sub_array *new_child) {
    std::set<sub_array*>::iterator child_it = children.begin();
    bool children_yield = false;
    while(child_it != children.end()) {
      if(contains((*child_it)->mask, new_child->mask)) {
        (*child_it)->add(new_child);
        children_yield = true;
      }
      ++child_it;
    }
    if(children_yield) return;
    while(child_it != children.end()) {
      if(contains(new_child->mask, (*child_it)->mask)) {
        new_child->add(*child_it);
        (*child_it)->parents.erase(this);
        child_it = children.erase(child_it);
      } else ++child_it;
    }
    children.insert(new_child);
    new_child->parents.insert(this);
  }

  sub_array* find(const int &in_mask) {
    if(in_mask == mask) return this;
    std::set<sub_array*>::iterator child_it = children.begin();
    while(child_it != children.end()) {
      if(!contains((*child_it)->mask, in_mask)) continue;
      sub_array *out = (*child_it)->find(in_mask);
      if(out != nullptr) return out;
    }
    return nullptr;
  }

  void update_order(const int &new_order) {
    kill_children();
    order = new_order;
  }

  void kill_children() {
    std::set<sub_array*>::iterator child_it = children.begin();
    while(child_it != children.end()) {
      kill_child(*child_it);
      child_it = this->children.erase(child_it);
    }
  }

  void kill_child(sub_array *bad_child) {
    bad_child->kill_children();
    for(sub_array* parent : bad_child->parents)
      if(parent != this) parent->children.erase(bad_child);
    delete bad_child;
  }

  void remove(const int &in_mask) {
    std::set<sub_array*>::iterator child_it = children.begin();
    while(child_it != children.end()) {
      if(contains(in_mask, (*child_it)->mask)) {
        kill_child(*child_it);
        child_it = this->children.erase(child_it);
      } else {
        if(contains((*child_it)->mask, in_mask))
          (*child_it)->remove(in_mask);
        ++child_it;
      }
    }
  }

  void find_set(const int &in_mask, int &min_order, int &set_value) {
    int order, value;
    min_order = this->order;
    set_value = this->set_value;
    for(sub_array* child : children) {
      if(contains(child->mask, in_mask)) {
        child->find_set(in_mask, order, value);
        if(order > min_order) {
          min_order = order;
          set_value = value;
        }
      }
    }
  }

  bool collect_xor(const int &in_mask, const int &min_order, int &xor_output) {
    bool xor_available = false;
    if(viable && order > min_order) {
      xor_output = xor_value;
      xor_available = true;
    }
    for(sub_array *child : children) {
      int new_xor;
      if(contains(child->mask, in_mask)) {
        if(child->collect_xor(in_mask, min_order, new_xor)) {
          if(xor_available) xor_output ^= new_xor;
          else {
            xor_output = new_xor;
            xor_available = true;
          }
        }
      }
    }
    return xor_available;
  }

  int mask;
  int set_value = 0;
  int xor_value;
  int order = -1;
  bool viable = false;
  std::set<sub_array*> children;
  std::set<sub_array*> parents;
};

int read_mask(int &len) {
  char mask_s[17];
  std::cin >> mask_s;
  int mask = 0;
  for(int i = 0; i < len; ++i) {
    mask = (mask << 1) + (mask_s[i] - '0');
  }
  return mask;
}

int main() {
  int n, q;
  std::cin >> n >> q;
  sub_array setters, xorrers;
  xorrers.mask = setters.mask = (1 << n) - 1;
  setters.viable = true;
  for(int i = 0; i < q; ++i) {
    int type, value, mask;
    std::cin >> type;
    if(type == 1) {
      std::cin >> value;
      mask = read_mask(n);
#ifdef ALGO_DEBUG
      std::cerr << "Adding new value " << value << " with mask " << mask << std::endl;
#endif
      sub_array *new_setter = setters.find(mask);
      if(new_setter == nullptr) {
#ifdef ALGO_DEBUG
        std::cerr << "No mask array found. creating new one" << std::endl;
#endif
        new_setter = new sub_array{};
        new_setter->viable = true;
        new_setter->mask = mask;
        new_setter->set_value = value;
        new_setter->order = i;
        setters.add(new_setter);
      } else {
#ifdef ALGO_DEBUG
        std::cerr << "reusing existing setter subarray" << std::endl;
#endif
        new_setter->set_value = value;
        new_setter->update_order(i);
      }
      xorrers.remove(mask);
    } else if(type == 2) {
      std::cin >> value;
      mask = read_mask(n);
#ifdef ALGO_DEBUG
      std::cerr << "Adding new xor " << value << " with mask " << mask << std::endl;
#endif
      sub_array *new_xorrer = xorrers.find(mask);
      if(new_xorrer == nullptr) {
#ifdef ALGO_DEBUG
        std::cerr << "No mask xor found. creating new one" << std::endl;
#endif
        new_xorrer = new sub_array{};
        new_xorrer->viable = true;
        new_xorrer->mask = mask;
        new_xorrer->xor_value = value;
        new_xorrer->order = i;
        xorrers.add(new_xorrer);
      } else {
#ifdef ALGO_DEBUG
        std::cerr << "reusing existing xor subarray" << std::endl;
#endif
        new_xorrer->xor_value = value;
        new_xorrer->order = i;
      }
    } else if(type == 3) {
      mask = read_mask(n);
#ifdef ALGO_DEBUG
      std::cerr << "Search value for mask " << mask << std::endl;
#endif
      int set_order, set_value, xor_value;
      setters.find_set(mask, set_order, set_value);
#ifdef ALGO_DEBUG
      std::cerr << "Setter value " << set_value << " with order " << set_order << std::endl;
#endif
      if(xorrers.collect_xor(mask, set_order, xor_value)) {
#ifdef ALGO_DEBUG
        std::cerr << "Found xorrers " << xor_value << std::endl;
#endif
        set_value ^= xor_value;
      }
      std::cout << set_value << std::endl;
    }
  }
  return 0;
}
