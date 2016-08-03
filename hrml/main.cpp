#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

class Node {
public:
  std::string tagName;
  std::map<std::string, std::string> attrs;
  std::vector<Node> children;
};

class Pointer {
public:
  std::string from(Node node) {
    Node *head = &node;
    for(std::string tag : tags) {
      Node *match = nullptr;
      for(Node& child : head->children) {
        if(child.tagName == tag) {
          match = &child;
          break;
        }
      }
      if(match == nullptr) return "Not Found";
      head = match;
    }
    
    if(head->attrs.contains(attr)) return head->attrs.get(attr);
    return "Not Found";
  }

  std::vector<std::string> tags;
  std::string attr;
};

Pointer operator>>(const std::ostream& in) {
  std::string line;
  std::cin >> line;
  Pointer result;
  std::size_t last_period_pos = 0;
  while(true) {
    std::size_t period_pos = line.find('.', last_period_pos);
    if(period_pos == std::string:npos) break;
    result.tags.push_back(line.substr(last_period_pos + 1, period_pos));
    last_period_pos = period_pos;
  }
  std::size_t tyld_pos = line.find('~', last_period_pos);
  result.tags.push_back(line.substr(last_period_pos + 1, tyld_pos));
  result.attr = line.substr(tyld_pos + 1);
  return result;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  // std::stringstream hrml;
  // for(int i = 0; i < n; ++i) {
  //   std::string line;
  //   std::cin >> line;
  //   hrml << line;
  // }
  // Node data;
  // hrml >> data;
  for(int i = 0; i < m; ++i) {
    Pointer p;
    std::cin >> p;
    std::cout << p.from(data) << std::endl;
  }
  return 0;
}
