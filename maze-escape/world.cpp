#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

#ifdef UNITS
#include "../test/units.cpp"
#endif

struct Vector {
  union {
    int y;
    int r;
  };
  union {
    int x;
    int c;
  };
};

enum Direction {
  UP, RIGHT, DOWN, LEFT, NONE
};

std::string direction_names[] = {"UP", "RIGHT", "DOWN", "LEFT", "NONE"};

std::string StringFromDirection(const Direction& inDirection) {
  return direction_names[inDirection];
}

Direction DirectionFromString(const std::string& inStr) {
  for(int i = 0; i < 5; ++i) {
    if(direction_names[i] == inStr) return static_cast<Direction>(i);
  }
  return Direction::NONE;
}

Direction DirectionFromVector(const Vector& inVector) {
  if(inVector.x == 0 && inVector.y == -1) return Direction::UP;
  if(inVector.x == +1 && inVector.y == 0) return Direction::RIGHT;
  if(inVector.x == 0 && inVector.y == +1) return Direction::DOWN;
  if(inVector.x == -1 && inVector.y == 0) return Direction::LEFT;
  return Direction::NONE;
}

Vector VectorFromDirection(const Direction& inDirection) {
  if(inDirection == Direction::UP) return {-1, 0};
  if(inDirection == Direction::RIGHT) return {0, +1};
  if(inDirection == Direction::DOWN) return {+1, 0};
  if(inDirection == Direction::LEFT) return {0, -1};
  return {0, 0};
}

Direction operator+(const Direction& left, const Direction& right) {
  return static_cast<Direction>((static_cast<int>(left) + static_cast<int>(right)) % 4);
}

Direction operator-(const Direction& left, const Direction& right) {
  return static_cast<Direction>((4 + static_cast<int>(left) - static_cast<int>(right)) % 4);
}

Vector operator+(const Vector& left, const Vector& right) {
  return { left.r + right.r, left.c + right.c };
}

Vector operator-(const Vector& left, const Vector& right) {
  return { left.r - right.r, left.c - right.c };
}

bool operator==(const Vector& left, const Vector& right) {
  return left.r == right.r && left.c == right.c;
}

Vector operator*(const Vector& left, const int& mult) {
  return { left.r * mult, left.c * mult };
}

class Maze {
public:
  enum Cell { FLOOR, EXIT, WALL };
  const int rows, cols;
  std::unique_ptr<Cell[]> cells;
  Vector begin, exit;

  Maze(int r, int c) : rows{r}, cols{c}, cells{new Cell[r * c]} {}

  Cell& at(int r, int c) { return cells[r * cols + c]; }
  const Cell& at(int r, int c) const { return cells[r * cols + c]; }
  Cell& at(const Vector& pos) { return cells[pos.r * cols + pos.c]; }
  const Cell& at(const Vector& pos) const { return cells[pos.r * cols + pos.c]; }
};

char cell_names[] = { '-', 'e', '#' };

char CharFromCell(const Maze::Cell &inCell) {
  return cell_names[static_cast<int>(inCell)];
}

Maze::Cell CellFromChar(const char& inChar) {
  for(int i = 0; i < 3; ++i)
    if(cell_names[i] == inChar) return static_cast<Maze::Cell>(i);
  return Maze::Cell::FLOOR;
}

void readMaze(const char* maze_str, Maze* maze) {
  std::stringstream maze_data{maze_str};
  for(int r = 0; r < maze->rows; ++r) {
    char buf[250];
    maze_data.getline(buf, 250);
    for(int c = 0; c < maze->cols; ++c) {
      if(buf[c] == 'b') {
        maze->at(r, c) = Maze::Cell::FLOOR;
        maze->begin.r = r; maze->begin.c = c;
      } else if(buf[c] == 'e') {
        maze->at(r, c) = Maze::Cell::EXIT;
        maze->exit.r = r; maze->exit.c = c;
      } else maze->at(r, c) = CellFromChar(buf[c]);
    }
  }
}

void printMazePiece(const Maze& maze, const Vector &center, const Direction& dir) {
  Vector unit_up = VectorFromDirection(dir);
  Vector unit_right = VectorFromDirection(dir + Direction::RIGHT);
  // std::cout << center.r << ", " << center.c << "; "
  //           << unit_up.r << ", " << unit_up.c << "; "
  //           << unit_right.r << ", " << unit_right.c << "\n";
  for(int dr = +1; dr >= -1; --dr) {
    for(int dc = -1; dc <= +1; ++dc) {
      // Vector up = (unit_up * dr);
      // Vector right = (unit_right * dc);
      // Vector p = center + up + right;
      // std::cout << p.r << ", " << p.c << "; " << up.r << ", " << up.c << "; " << right.r << ", " << right.c << "| ";
      std::cout << CharFromCell(maze.at(center + unit_up * dr + unit_right * dc));
    }
    std::cout << '\n';
  }
}

class World {
  Maze* maze;
public:
  bool is_finished = false;
  bool is_successful = false;
  bool is_failed = false;
  std::string failed_reason;

  void init(std::string init_data) {
    std::stringstream init_stream{init_data};
    int rs, cs;
    init_stream >> rs >> cs;
    maze = new Maze{rs, cs};
    std::string empty;
    std::getline(init_stream, empty);
    int maze_data_length = (cs + 1) * rs;
    char maze_data[maze_data_length];
    init_stream.get(maze_data, maze_data_length);
    readMaze(maze_data, maze);
  }
  std::string prompt() { return "hello"; }
  void process(std::string input) {
    is_finished = true;
    is_successful = true;
  }

};

#ifndef PREVENT_WORLD_MAIN

std::string read_input() {
  std::string input;
  for(int i = 0; i < 3; ++i) {
    std::string line;
    std::cin >> line;
    input += line;
  }
  return input;
}

std::string read_file(char* file_name) {
  std::ifstream inf;
  inf.open(file_name);
  char buf[4096];
  inf.read(buf, 4096);
  return std::string{buf};
}

void print_use(std::string executable);

#ifdef UNITS
void test_direction_summ() {
  test_header("direction summ");
  int T;
  std::cin >> T;
  for(int i = 0; i < T; ++i) {
    std::string one, two;
    std::cin >> one >> two;
    Direction left = DirectionFromString(one);
    Direction right = DirectionFromString(two);
    std::cout << StringFromDirection(left + right) << "\n";
  }
}

void test_direction_diff() {
  test_header("direction diff");
  int T;
  std::cin >> T;
  for(int i = 0; i < T; ++i) {
    std::string one, two;
    std::cin >> one >> two;
    Direction left = DirectionFromString(one);
    Direction right = DirectionFromString(two);
    std::cout << StringFromDirection(left - right) << "\n";
  }
}

void test_world_pieces() {
  test_header("world pieces");
  int rs, cs;
  std::cin >> rs >> cs;
  std::string empty;
  std::getline(std::cin, empty);
  char maze_c_str[rs * (cs + 1) + 1];
  std::cin.get(maze_c_str, rs * (cs + 1), '\0');
  Maze maze{rs, cs};
  readMaze(maze_c_str, &maze);
  std::cout << maze.begin.r << " " << maze.begin.c << "\n"
            << maze.exit.r << " " << maze.exit.c << "\n";
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) {
    int r, c;
    std::string dir_name;
    std::cin >> r >> c >> dir_name;
    printMazePiece(maze, {r, c}, DirectionFromString(dir_name));
  }
}

void unit_tests() {
  test_direction_summ();
  test_direction_diff();
  test_world_pieces();
}
#endif

int main(int argc, char** argv) {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
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
