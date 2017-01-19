#include <iostream>
#include <cstdio>
#include <string>
#include <array>
#include <unistd.h>

// incoming maze piece
int piece[3][3];

// walls. zero - empty cell (might turn out to be wall), one - wall
int maze[70][70];

// where have we been?
bool visited[70][70];

// our relative position
int x = 35, y = 35;

enum Direction {
  TOP, RIGHT, DOWN, LEFT
};

Direction sum_directions(const Direction &from, const Direction &to) {
  return static_cast<Direction>((from + to) % 4);
}

std::array<std::string, 4> direction_names{
  std::string{"TOP"}, std::string{"RIGHT"}, std::string{"DOWN"}, std::string{"LEFT"}
};

Direction current_direction = Direction::TOP;

// move to given new position, from current, taking current dirrection into account.
// output - is turn, which should have been taken
Direction moveTo(int newX, int newY) {
  return Direction::LEFT;
}

// by given global x, y and 
int from_piece(const int &in_x, const int &in_y) {
  return 0;
}

// scan through current maze location and copy piece into it with proper rotation
void plug_maze_piece() {
}

// read piece from input
void read_piece() {
  // visited[x][y] = true;
  // for(int i = x - 1; i <= x + 1; ++i) {
  //   for(int j = y - 1; j <= y + 1; ++j) {
  //     maze[i][j] = 
  //   }
  // }
}

int main() {
  std::cout << direction_names[sum_directions(Direction::DOWN, Direction::RIGHT)] << std::endl;
  return 0;
}
