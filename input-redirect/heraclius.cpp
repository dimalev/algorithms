#include <iostream>
#include <queue>
#include <cstdio>
#include <string>
#include <array>
#include <unistd.h>
#include <algorithm>

// incoming maze piece
int piece[3][3];

constexpr int MIN_R = 0, MIN_C = 0, MAX_R = 70, MAX_C = 70;

// walls. zero - empty cell (might turn out to be wall), one - wall
int maze[MAX_R][MAX_C];

// where have we been?
bool visited[MAX_R][MAX_C];

// what have we seen?
bool visible[MAX_R][MAX_C];

// our relative position
int r = MAX_R / 2, c = MAX_C / 2;

enum Direction {
  UP, RIGHT, DOWN, LEFT
};

#define D_C(dx, dy) std::array<int, 2>{dx, dy}
#define D_R std::array<std::array<int, 2>, 9>

std::array<std::array<std::array<int, 2>, 9>, 4> directions_rows{
  D_R { D_C(-1, -1), D_C(-1, 0), D_C(-1, +1), D_C(0, -1), D_C(0, 0), D_C(0, +1), D_C(+1, -1), D_C(+1, 0), D_C(+1, +1) },
  D_R { D_C(-1, +1), D_C(0, +1), D_C(+1, +1), D_C(-1, 0), D_C(0, 0), D_C(+1, 0), D_C(-1, -1), D_C(0, -1), D_C(+1, -1) },
  D_R { D_C(+1, +1), D_C(+1, 0), D_C(+1, -1), D_C(0, +1), D_C(0, 0), D_C(0, -1), D_C(-1, +1), D_C(-1, 0), D_C(-1, -1) },
  D_R { D_C(+1, -1), D_C(0, -1), D_C(-1, -1), D_C(+1, 0), D_C(0, 0), D_C(-1, 0), D_C(+1, +1), D_C(0, +1), D_C(-1, +1) }
};

Direction sum_directions(const Direction &from, const Direction &to) {
  return static_cast<Direction>((from + to) % 4);
}

std::array<std::string, 4> direction_names{"UP", "RIGHT", "BOTTOM", "LEFT"};

Direction current_direction = Direction::UP;

Direction direction_from_delta(const int &dr, const int &dc) {
  if(dr == -1) return Direction::UP;
  if(dr == +1) return Direction::DOWN;
  if(dc == -1) return Direction::LEFT;
  if(dc == +1) return Direction::RIGHT;
  std::cerr << "Wrong delta: " << dr << ", " << dc << std::endl;
  exit(EXIT_FAILURE);
}

void delta_from_direction(const Direction &in_dir, int *dr, int *dc) {
  *dr = 0; *dc = 0;
  if(in_dir == Direction::UP) *dr = -1;
  if(in_dir == Direction::DOWN) *dr = +1;
  if(in_dir == Direction::LEFT) *dc = -1;
  if(in_dir == Direction::RIGHT) *dc = +1;
}

// scan through current maze location and copy piece into it with proper rotation
void plug_piece() {
  visited[r][c] = true;
  int l = 0;
  std::array<std::array<int, 2>, 9> rows = directions_rows[current_direction];
  for(int dr = 0; dr < 3; ++dr) {
    for(int dc = 0; dc < 3; ++dc) {
      maze[r + rows[l][0]][c + rows[l][1]] = piece[dr][dc];
      visible[r + rows[l][0]][c + rows[l][1]] = true;
      ++l;
    }
  }
}

int maze_from_char(const char &in_c) {
  if(in_c == '#') return 1;
  if(in_c == '-') return 0;
  std::cerr << "Unknown maze char " << in_c << std::endl;
  exit(EXIT_FAILURE);
}

// read piece from input
void read_piece() {
  for(int r = 0; r < 3; ++r) {
    std::string line;
    std::cin >> line;
    for(int c = 0; c < 3; ++c) {
      piece[r][c] = maze_from_char(line[c]);
    }
  }
}

std::queue<std::array<int, 2>> next_steps;

void make_step() {
  if(next_steps.size()
}

int main() {
  std::cout << direction_names[sum_directions(Direction::DOWN, Direction::RIGHT)] << std::endl;
  return 0;
}
