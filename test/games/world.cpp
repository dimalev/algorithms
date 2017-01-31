#include <string>
#include <iostream>
#include <fstream>

class World {
public:
  bool is_finished = false;
  bool is_successful = false;
  bool is_failed = false;
  std::string failed_reason;

  void init(std::string init_data) { }
  std::string prompt() { return "hello"; }
  void process(std::string input) {
    is_finished = true;
    is_successful = true;
  }

};

#ifndef PREVENT_WORLD_MAIN

std::string read_input() {
  return "hello";
}

std::string read_file(char* file_name) {
  std::ifstream inf;
  inf.open(file_name);
  char buf[4096];
  inf.read(buf, 4096);
  return std::string{buf};
}

void print_use(std::string executable);

int main(int argc, char** argv) {
  if(argc != 2) {
    print_use(argv[0]);
    return 1;
  }

  std::string init_data = read_file(argv[1]);

  World world;

  world.init(init_data);

  while(!world.is_finished) {
    std::cout << world.prompt();
    std::string step = read_input();
    world.process(step);
  }

  if(world.is_failed) {
    std::cerr << "World failed: " << world.failed_reason << std::endl;
    return 1;
  }

  return 0;
}

void print_use(std::string executable) {
  std::cout << "Usage:\n\n"
            << "\t" << executable << " INIT_FILE_NAME\n\n"
            << "Where INIT_FILE_NAME is the name of the file to init World.\n";
}

#endif
