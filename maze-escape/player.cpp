#include <memory>
#include <iostream>
#include <queue>
#include <cstdio>
#include <string>
#include <stack>
#include <array>
#include <unistd.h>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

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


/**
 * maze - 2D array with true, where walls are,
 * start - where to start,
 * destinations - 2D array with true on places which are valid end points.
 *
 * this method is intended to help searching path to the closest non-visible cell,
 * for exit - it will have all the field filled with falses, and single cell with true
 */
std::vector<Vector> breadthSearch(bool** maze, const Vector& start, bool** destinations) {
  std::vector<Vector> path;
}

class Maze {
public:
  enum Cell { FLOOR, EXIT, WALL };
  const int rows, cols;
  bool** visible, walls, exit_place;
  Vector pos, exit;
  bool is_exit_found = false;

  Maze(int r, int c) : rows{r}, cols{c}, cells{new Cell[r * c]}, pos{r / 2, c / 2} {}


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
