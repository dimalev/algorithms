#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string>

int give[2], take[2], pid;

void send(const std::string &line) {
  const char *raw = line.c_str();
  write(give[1], raw, std::strlen(raw));
  write(give[1], "\n", 1);
}

std::string receive() {
  char buf[256];
  int n = read(take[0], buf, 256);
  buf[n] = 0;
  return std::string{buf};
}

int main(int argc, char **argv) {
  if(argc != 3) {
    std::cout << "Usage:\n"
         << "./overlord HERACLIUS.BIN MAZE.TXT\n";
  }

  pipe(give);
  pipe(take);

  std::cout << "O: spawning child..\n";
  char* hargv[] = {argv[1], 0};

  switch(pid = fork()) {
  case 0:
    dup2(give[0], STDIN_FILENO); // we take from give
    dup2(take[1], STDOUT_FILENO); // we give to take
    close(give[1]); close(take[0]);
    execvp(argv[1], hargv);
  case -1:
    perror("Could not spawn child process");
    exit(1);
  default:
    close(give[0]); close(take[1]);
  }

  std::cout << "O: sending info..\n";
  send("122");

  std::cout << "O: waiting for output..\n";
  std::cout << "[" << receive() << "]\n";

  return 0;
}
