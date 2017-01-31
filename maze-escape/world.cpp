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

// class Direction {
//   enum Name {
//     UP, RIGHT, BOTTOM, LEFT
//   };
// };

// class Possition {
// };

// class Move {
// };

// class Player {
// };

// class Maze {
// };

// int maze[30][30];

// int W, H, x, y, exit_x, exit_y;

// enum Direction {
//   UP, RIGHT, BOTTOM, LEFT
// };

// Direction heraclius_direction;

// std::array<std::string, 4> directions_names{"UP", "RIGHT", "BOTTOM", "LEFT"};

// Direction direction_from_string(const std::string &name) {
//   auto dir_it = std::find(directions_names.begin(), directions_names.end(), name);
//   return static_cast<Direction>(dir_it - directions_names.begin());
// }

// #define D_C(dx, dy) std::array<int, 2>{dx, dy}
// #define D_R std::array<std::array<int, 2>, 8>

// std::array<std::array<std::array<int, 2>, 8>, 4> directions_clockwise{
//   D_R { D_C(-1, 0), D_C(-1, +1), D_C(0, +1), D_C(+1, +1), D_C(+1, 0), D_C(+1, -1), D_C(0, -1), D_C(-1, -1) },
//   D_R { D_C(0, +1), D_C(+1, +1), D_C(+1, 0), D_C(+1, -1), D_C(0, -1), D_C(-1, -1), D_C(-1, 0), D_C(-1, +1) },
//   D_R { D_C(+1, 0), D_C(+1, -1), D_C(0, -1), D_C(-1, -1), D_C(-1, 0), D_C(-1, +1), D_C(0, +1), D_C(+1, +1) },
//   D_R { D_C(0, -1), D_C(-1, -1), D_C(-1, 0), D_C(-1, +1), D_C(0, +1), D_C(+1, +1), D_C(+1, 0), D_C(+1, -1) }
// };

// void send(const std::string &line) {
//   const char *raw = line.c_str();
//   write(give[1], raw, std::strlen(raw));
//   write(give[1], "\n", 1);
// }

// std::string receive() {
//   char buf[256];
//   int n = read(take[0], buf, 256);
//   buf[n] = 0;
//   if(n == 0) file_end = 0;
//   return std::string{buf};
// }

// void read_maze(const char *file_name) {
//   std::cout << "O: Reading maze..\n";
//   std::ifstream input;
//   input.open(file_name);
//   std::string initial_direction;
//   input >> W >> H >> initial_direction;
//   heraclius_direction = direction_from_string(initial_direction);
//   for(int i = 0; i < W; ++i) {
//     std::string line;
//     input >> line;
//     for(int j = 0; j < H; ++j) {
//       switch(line[j]) {
//       case 'b': x = i; y = j; break;
//       case 'e': exit_x = i; exit_y = j; break;
//       case '#': maze[i][j] = 1; break;
//       case '-': break;
//       default:
//         std::cerr << "O: Malformatted maze."
//                   << " Unknown cell " << line[j] << " at " << i << ", " << j << "\n";
//         exit(EXIT_FAILURE);
//       }
//     }
//   }
// }

// char char_from_maze(int maze_v) {
//   return maze_v == 1 ? '#' : '-';
// }

// std::string get_visible_maze() {
//   char buf[11];
//   const std::array<std::array<int, 2>, 8> &clockwise = directions_clockwise[heraclius_direction];
//   buf[0] = char_from_maze(maze[x + clockwise[7][0]][y + clockwise[7][1]]);
//   buf[1] = char_from_maze(maze[x + clockwise[0][0]][y + clockwise[0][1]]);
//   buf[2] = char_from_maze(maze[x + clockwise[1][0]][y + clockwise[1][1]]);
//   buf[3] = '\n';
//   buf[4] = char_from_maze(maze[x + clockwise[6][0]][y + clockwise[6][1]]);
//   buf[5] = char_from_maze(maze[x][y]);
//   buf[6] = char_from_maze(maze[x + clockwise[2][0]][y + clockwise[2][1]]);
//   buf[7] = '\n';
//   buf[8] = char_from_maze(maze[x + clockwise[5][0]][y + clockwise[5][1]]);
//   buf[9] = char_from_maze(maze[x + clockwise[4][0]][y + clockwise[4][1]]);
//   buf[10] = char_from_maze(maze[x + clockwise[3][0]][y + clockwise[3][1]]);
//   buf[11] = 0;
//   return std::string(buf);
// }

// void print_visible_maze() {
//   std::string visible_maze = get_visible_maze();
//   std::cout << "O: Sending maze:\n---\n" << visible_maze << "\n---\n";
//   send(visible_maze);
// }

// Direction read_direction() {
//   std::string dir_mod = receive();
//   if(dir_mod.length() == 0) return Direction::UP;
//   dir_mod = dir_mod.substr(0, dir_mod.find('\n'));
//   std::cout << "O: Heraclius turns " << dir_mod << "\n";
//   return direction_from_string(dir_mod);
// }

// void move(const Direction &new_dir) {
//   heraclius_direction = static_cast<Direction>((heraclius_direction + new_dir) % 4);
//   std::cout << "O: New Heraclius direction " << directions_names[heraclius_direction] << "\n";
//   x += directions_clockwise[heraclius_direction][0][0];
//   y += directions_clockwise[heraclius_direction][0][1];
//   std::cout << "O: New heraclius position: " << x << ", " << y << "\n";

//   if(maze[x][y] == 1) {
//     std::cerr << "O: Heraclius stepped through the wall!\n";
//     exit(EXIT_FAILURE);
//   }
// }

// bool check_exited_maze() {
//   return x == exit_x && y == exit_y;
// }

// void maze_loop() {
//   int heraclius_status;
//   pid_t wpid;
//   while(!file_end) {
//     print_visible_maze();
//     Direction new_dir = read_direction();
//     if(file_end) break;
//     move(new_dir);
//     if(check_exited_maze()) {
//       std::cout << "O: Heraclius exited maze!\n";
//       break;
//     }
//   }
//   while((wpid = waitpid(heraclius_pid, &heraclius_status, 0)) != -1) {
//     if(WIFEXITED(heraclius_status)) {
//       std::cout << "O: Heraclius process exited\n";
//       return;
//     }
//   }

//   perror("waitpid");
//   exit(EXIT_FAILURE);
// }

// int main(int argc, char **argv) {
//   if(argc != 2) {
//     std::cout << "Usage:\n"
//               << argv[0] << " MAZE.TXT\n";
//     exit(1);
//   }

//   read_maze(argv[2]);

//   maze_loop();

//   return 0;
// }
// 
