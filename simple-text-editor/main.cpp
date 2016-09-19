#include <iostream>
#include <vector>
#include <cstring>

class action {
public:
  action(char *str, size_t len) {
    is_add = true;
    this->length = len;
    this->str = (char*)malloc(len);
    std::memcpy(this->str, str, len);
  }

  explicit action(size_t len) {
    is_remove = true;
    this->length = len;
  }

  bool is_add = false;
  bool is_remove = false;
  char *str = nullptr;
  size_t length;
};

const int MAX_CHARS = 1000000;

char line[MAX_CHARS], buffer[MAX_CHARS];
int length;
std::vector<action> history;

int main() {
  int N;
  std::cin >> N;
  for(int i = 0; i < N; ++i) {
    int command;
    std::cin >> command;
    if(command == 1) {
      std::cin >> buffer;
      size_t len = std::strlen(buffer);
      history.push_back(action{len});
      memcpy(line + length, buffer, len);
      length += len;
    } else if(command == 2) {
      size_t count;
      std::cin >> count;
      length -= count;
      memcpy(buffer, line + length, count);
      history.push_back(action{buffer, count});
    } else if(command == 3) {
      int pos;
      std::cin >> pos;
      std::cout << line[pos - 1] << std::endl;
    } else if(command == 4) {
      action last_command = history.back();
      history.pop_back();
      if(last_command.is_add) {
        memcpy(line + length, last_command.str, last_command.length);
        free(last_command.str);
        length += last_command.length;
      } else if(last_command.is_remove) {
        length -= last_command.length;
      }
    }
  }
}
