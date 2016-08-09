#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <sstream>
#include <string>

class Tag {
public:
  enum class Type { open, close };
  Type type;
  std::string name;
  std::map<std::string, std::string> attrs;
};

class Node {
public:
  // Node(): parent{nullptr} {}
  Tag open, close;
  std::vector<Node> children;
  Node* parent = nullptr;
};

class Pointer {
public:
  std::string from(Node node) {
    Node *head = &node;
    for(std::string tag : tags) {
      Node *match = nullptr;
      for(Node& child : head->children) {
        if(child.open.name == tag) {
          match = &child;
          break;
        }
      }
      if(match == nullptr) return "Not Found";
      head = match;
    }
    auto attrit = head->open.attrs.find(attr);
    if(attrit != head->open.attrs.end()) return attrit->second;
    return "Not Found";
  }

  std::vector<std::string> tags;
  std::string attr;
};

Pointer operator>>(const std::istream& in, Pointer &result) {
  std::string line;
  std::cin >> line;
  std::size_t last_period_pos = 0;
  while(true) {
    std::size_t period_pos = line.find('.', last_period_pos);
    if(period_pos == std::string::npos) break;
    result.tags.push_back(line.substr(last_period_pos + 1, period_pos));
    last_period_pos = period_pos;
  }
  std::size_t tyld_pos = line.find('~', last_period_pos);
  result.tags.push_back(line.substr(last_period_pos + 1, tyld_pos));
  result.attr = line.substr(tyld_pos + 1);
  return result;
}

void skipSpaces(const std::istream& in) {
  char c;
  while(!in.eof()) {
    in.get(c);
    if(!std::isspace(c)) {
      in.putback(c);
    }
  }
}

Tag operator>>(const std::istream& in, Tag &tag) {
  skipSpaces(in);
  char mandatory;
  in >> mandatory;
#ifdef ALGO_DEBUG
  std::cerr << "open tag: " << mandatory << "." << std::endl;
#endif
  char isclose;
  in >> isclose;
#ifdef ALGO_DEBUG
  std::cerr << "is close: " << isclose << "." << std::endl;
#endif
  if(isclose == '/') {
    tag.type = Tag::Type::close;
  } else {
    tag.type = Tag::Type::open;
    in.putback(isclose);
  }
  in >> tag.name;
#ifdef ALGO_DEBUG
  std::cerr << "tag name: " << tag.name << "." << std::endl;
#endif
  skipSpaces(in);
  if(tag.type == Tag::Type::open) {
    while(true) {
      skipSpaces(in);
      in >> mandatory;
#ifdef ALGO_DEBUG
      std::cerr << "check if tag end: " << mandatory << "." << std::endl;
#endif
      if(mandatory == '>') break;
      else in.putback(mandatory);
      std::string attrName, attrValue;
      in >> attrName;
#ifdef ALGO_DEBUG
      std::cerr << "got attribute name: " << attrName << "." << std::endl;
#endif
      skipSpaces(in);
      in >> mandatory;
#ifdef ALGO_DEBUG
      std::cerr << "try equal: " << mandatory << "." << std::endl;
#endif
      skipSpaces(in);
      in >> attrValue;
#ifdef ALGO_DEBUG
      std::cerr << "got value before stripping: " << attrValue << "." << std::endl;
#endif
      attrValue = attrValue.substr(1, attrValue.length() - 2);
#ifdef ALGO_DEBUG
      std::cerr << "value after stripping: " << attrValue << "." << std::endl;
#endif
      tag.attrs[attrName] = attrValue;
    }
  } else {
    in >> mandatory;
#ifdef ALGO_DEBUG
    std::cerr << "should close tag: " << mandatory << "." << std::endl;
#endif
  }
  return tag;
}

Node operator>>(const std::istream& in, Node &data) {
  Node *current = &data;
  in >> current->open;
  while(current != nullptr) {
    Tag nextTag;
    in >> nextTag;
    if(nextTag.type == Tag::Type::close) {
      current->close = nextTag;
      current = current->parent;
    } else {
      Node* nextNode = new Node{};
      current.children.push_back(nextNode);
      nextNode->open = nextTag;
      current = nextNode;
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::stringstream hrml;
  for(int i = 0; i < n; ++i) {
    std::string line;
    std::cin >> line;
    hrml << line;
  }
  Node data;
  hrml >> data;
  for(int i = 0; i < m; ++i) {
    Pointer p;
    std::cin >> p;
    std::cout << p.from(data) << std::endl;
  }
  return 0;
}
