#include <iostream>

bool contains(const int &parent, const int &child) {
  return child == (parent & child);
}

bool intersect(const int &one, const int &two) {
  return (one & two) != 0;
}

class setter {
public:
  bool viable = false;
  int value;
  int order;
};

class xorrer {
public:
  bool viable = false;
  int value;
  int order;
};

class tree_node {
public:
  void add_child(tree_node* new_child) {
    bool children_yield = false;
    for(tree_node *child : children) {
      if(contains(child->mask, new_child->mask)) {
        child->add_child(new_child);
        children_yield = true;
      }
    }
    if(children_yield) return;
    auto child_it = children.begin();
    while(child_it != children.end()) {
      if(contains(new_child->mask, (*child_it)->mask)) {
        (*child_it)->parents.remove(this);
        (*child_it)->parents.insert(new_child);
        new_child->children.insert((*child_it));
        child_it = children.erase(child_it);
      } else {
        if(intersect(new_child->mask, (*child_it)->mask))
          (*child_it)->remount_children(new_child);
        ++child_it;
      }
    }
    new_child->parents.insert(this);
    children.insert(new_child);
  }

  void remount_children(tree_node *parent) {
    auto child_it = children.begin();
    while(child_it != children.end()) {
      if(contains(new_child->mask, (*child_it)->mask)) {
        (*child_it)->parents.remove(this);
        (*child_it)->parents.insert(new_child);
        new_child->children.insert((*child_it));
        child_it = children.erase(child_it);
      } else {
        if(intersect(new_child->mask, (*child_it)->mask))
          (*child_it)->remount_children(new_child);
        ++child_it;
      }
    }
  }

  void remove_xors(const int &mask) {
    auto child_it = children.begin();
    while(child_it != children.end()) {
      if(contains(mask, (*child_it)->mask)) {
        if((*child_it)->sett.viable) ++child_it;
        else {
          (*child_it)->parents.erase(this);
          child_it = children.remove(child_it);
        }
      } else if(intersect(mask, (*child_it)->mask)) {
      } else ++child_it;
    }
  }

  std::set<tree_node*> children;
  std::set<tree_node*> parents;

  int mask;
  setter sett;
  xorrer xorr;
};
