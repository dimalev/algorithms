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
  Tag *open, *close;
  std::vector<Node*> children;
  Node* parent = nullptr;
};

class Pointer {
public:
  std::string from(Node *node) {
    Node *head = node;
    int tl = tags.size();
    for(int i = 0; i < tl; ++i) {
      std::string tag = tags[i];
#ifdef ALGO_DEBUG
      std::cerr << "seek tag: " << tag << std::endl;
#endif
      Node *match = nullptr;
      for(Node* child : head->children) {
        if(child->open->name == tag) {
          match = child;
          break;
        }
      }
      if(match == nullptr) return "Not Found!";
      head = match;
    }
    auto attrit = head->open->attrs.find(attr);
    if(attrit != head->open->attrs.end()) return attrit->second;
    return "Not Found!";
  }

  std::vector<std::string> tags;
  std::string attr;
};

Pointer operator>>(const std::istream& in, Pointer &result) {
  std::string line;
  std::getline(std::cin, line);
#ifdef ALGO_DEBUG
  std::cerr << "got pointer: " << line << std::endl;
#endif
  std::size_t last_period_pos = 0;
  while(true) {
    std::size_t period_pos = line.find('.', last_period_pos);
    if(period_pos == std::string::npos) break;
    std::string tagName = line.substr(last_period_pos, period_pos - last_period_pos);
#ifdef ALGO_DEBUG
    std::cerr << "new tag name: " << tagName << std::endl;
#endif
    result.tags.push_back(tagName);
    last_period_pos = period_pos + 1;
  }
  std::size_t tyld_pos = line.find('~', last_period_pos);
  std::string lastTag = line.substr(last_period_pos, tyld_pos - last_period_pos);
#ifdef ALGO_DEBUG
    std::cerr << "last tag name: " << lastTag << std::endl;
#endif
  result.tags.push_back(lastTag);
  result.attr = line.substr(tyld_pos + 1);
#ifdef ALGO_DEBUG
    std::cerr << "attribute: " << result.attr << std::endl;
#endif
  return result;
}

void skipSpaces(std::istream& in) {
  char c;
  while(!in.eof()) {
    in.get(c);
    if(!std::isspace(c)) {
      in.putback(c);
      return;
    }
#ifdef ALGO_DEBUG
    std::cerr << "- skip char: " << c << std::endl;
#endif
  }
}

bool readTag(std::istream &in, Tag *tag) {
  skipSpaces(in);
  char mandatory;
  in.get(mandatory);
#ifdef ALGO_DEBUG
  std::cerr << "open tag: " << mandatory << "." << std::endl;
  if(mandatory != '<') return false;
#endif
  char isclose;
  in.get(isclose);
#ifdef ALGO_DEBUG
  std::cerr << "is close: " << isclose << "." << std::endl;
#endif
  if(isclose == '/') {
    tag->type = Tag::Type::close;
  } else {
    tag->type = Tag::Type::open;
    in.putback(isclose);
  }
  char tagC;
  in.get(tagC);
  while(tagC != '>' && !std::isspace(tagC)) {
    tag->name += tagC;
    in.get(tagC);
  }
  if(tagC == '>') in.putback(tagC);
#ifdef ALGO_DEBUG
  std::cerr << "tag name: " << tag->name << "." << std::endl;
#endif
  skipSpaces(in);
  if(tag->type == Tag::Type::open) {
    while(true) {
      skipSpaces(in);
      in.get(mandatory);
#ifdef ALGO_DEBUG
      std::cerr << "check if tag end: " << mandatory << "." << std::endl;
#endif
      if(mandatory == '>') break;
      else in.putback(mandatory);
      std::string attrName, attrValue;
      char c;
      in.get(c);
      while(c != '=' && !std::isspace(c)) {
        attrName += c;
        in.get(c);
      }
#ifdef ALGO_DEBUG
      std::cerr << "got attribute name: " << attrName << "." << std::endl;
#endif
      skipSpaces(in);
      if(c != '=') {
        skipSpaces(in);
        in.get(mandatory);
      } else mandatory = c;
#ifdef ALGO_DEBUG
      std::cerr << "mandatory equal: " << mandatory << "." << std::endl;
#endif
      skipSpaces(in);
      in.get(mandatory);
#ifdef ALGO_DEBUG
      std::cerr << "mandatory double quote: " << mandatory << "." << std::endl;
#endif
      in.get(c);
      while(c != '"' && !std::isspace(c)) {
        attrValue += c;
        in.get(c);
      }
#ifdef ALGO_DEBUG
      std::cerr << "value: " << attrValue << "." << std::endl;
#endif
      tag->attrs[attrName] = attrValue;
    }
  } else {
    in >> mandatory;
#ifdef ALGO_DEBUG
    std::cerr << "should close tag: " << mandatory << "." << std::endl;
#endif
  }
  return true;
}

bool readHrml(std::istream& in, Node *data) {
  Node *current = data;
#ifdef ALGO_DEBUG
  std::cerr << "before reading tag" << std::endl;
#endif
  current->open = new Tag{};
  if(!readTag(in, current->open)) return false;
  while(current != nullptr) {
    Tag *nextTag = new Tag{};
    readTag(in, nextTag);
    if(nextTag->type == Tag::Type::close) {
      current->close = nextTag;
      current = current->parent;
    } else {
      Node* nextNode = new Node{};
      current->children.push_back(nextNode);
      nextNode->open = nextTag;
      nextNode->parent = current;
      current = nextNode;
    }
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::stringstream hrml;
  std::string line;
  std::getline(std::cin, line);
  for(int i = 0; i < n; ++i) {
    std::getline(std::cin, line);
    hrml << line;
  }
#ifdef ALGO_DEBUG
  std::cerr << "read done" << std::endl;
#endif
  Node *data = new Node{};
  while(hrml.rdbuf()->in_avail()) {
    Node *nextChild = new Node{};
    if(!readHrml(hrml, nextChild)) break;;
    data->children.push_back(nextChild);
  }
#ifdef ALGO_DEBUG
  std::cerr << "parse done" << std::endl;
#endif
  for(int i = 0; i < m; ++i) {
    Pointer p;
    std::cin >> p;
#ifdef ALGO_DEBUG
    std::cerr << "next pointer" << std::endl;
#endif
    std::cout << p.from(data) << std::endl;
  }
  return 0;
}
