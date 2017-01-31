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
int r = MAX_R / 2, c = MAX_C / 2, exit_r = 0, exit_l = 0;
bool exit_found = false;

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

Direction diff_directions(const Direction &from, const Direction &to) {
  return static_cast<Direction>((4 + to - from) % 4);
}

std::array<std::string, 4> direction_names{"UP", "RIGHT", "DOWN", "LEFT"};

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

Direction new_direction(const int &dr, const int &dc) {
  return diff_directions(current_direction, direction_from_delta(dr, dc));
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

std::queue<std::array<int, 2>> visible_path_to_first_empty() {
  int trace[MAX_R][MAX_C]{0};
  std::queue<std::array<int, 2>> cells;
  cells.emplace(r, c);
  trace[r][c] = 1;
  std::array<int, 2> target_cell;
  while(cells.size() > 0) {
    std::array<int, 2> next_cell = cells.front();
    cells.pop();
    int next_trace = trace[next_cell[0]][next_cell[1]];
    if(next_cell[0] > MIN_R && trace[next_cell[0] - 1][next_cell[1]] == 0 &&
       visible[next_cell[0] - 1][next_cell[1]] &&
       maze[next_cell[0] - 1][next_cell[1]] == 0)
      {
        trace[next_cell[0] - 1][next_cell[1]] = next_trace + 1;
        if(!visited[next_cell[0] - 1][next_cell[1]]) {
          target_cell[0] = next_cell[0] - 1;
          target_cell[1] = next_cell[1];
        }
        cells.emplace(next_cell[0] - 1, next_cell[1]);
      }

    if(next_cell[0] + 1 < MAX_R && trace[next_cell[0] + 1][next_cell[1]] == 0 &&
       visible[next_cell[0] + 1][next_cell[1]] &&
       maze[next_cell[0] + 1][next_cell[1]] == 0)
      {
        trace[next_cell[0] + 1][next_cell[1]] = next_trace + 1;
        if(!visited[next_cell[0] + 1][next_cell[1]]) {
          target_cell[0] = next_cell[0] + 1;
          target_cell[1] = next_cell[1];
        }
        cells.emplace(next_cell[0] + 1, next_cell[1]);
      }

    if(next_cell[1] + 1 < MAX_C && trace[next_cell[0]][next_cell[1] + 1] == 0 &&
       visible[next_cell[0]][next_cell[1] + 1] &&
       maze[next_cell[0]][next_cell[1] + 1] == 0)
      {
        trace[next_cell[0]][next_cell[1] + 1] = next_trace + 1;
        if(!visited[next_cell[0] + 1][next_cell[1]]) {
          target_cell[0] = next_cell[0];
          target_cell[1] = next_cell[1] + 1;
        }
        cells.emplace(next_cell[0], next_cell[1] + 1);
      }

    if(next_cell[1] > MIN_C && trace[next_cell[0]][next_cell[1] - 1] == 0 &&
       visible[next_cell[0]][next_cell[1] - 1] &&
       maze[next_cell[0]][next_cell[1] - 1] == 0)
      {
        trace[next_cell[0]][next_cell[1] - 1] = next_trace + 1;
        if(!visited[next_cell[0] - 1][next_cell[1]]) {
          target_cell[0] = next_cell[0];
          target_cell[1] = next_cell[1] - 1;
        }
        cells.emplace(next_cell[0], next_cell[1] - 1);
      }
  }
  std::stack<std::array<int, 2>> path;
  while(trace[target_cell[0]][target_cell[1]] > 1) {
    path.push(target_cell);
    int next_trace = trace[target_cell[0]][target_cell[1]] - 1;
    if(target_cell[0] > MIN_R && trace[target_cell[0] - 1][target_cell[1]] == next_trace)
      --target_cell[0];
    else if(target_cell[0] + 1 < MAX_R && trace[target_cell[0] + 1][target_cell[1]] == next_trace)
      ++target_cell[0];
    else if(target_cell[1] > MIN_C && trace[target_cell[0]][target_cell[1] - 1] == next_trace)
      --target_cell[1];
    else if(target_cell[1] + 1 > MAX_C && trace[target_cell[0]][target_cell[1] + 1] == next_trace)
      ++target_cell[1];
  }

  return std::vector<std::array<int, 2>>{path.begin(), path.end()};
}

std::queue<std::array<int, 2>> next_steps;

std::array<int, 2> make_step() {
  // if(next_steps.size()) {
  //   std::array<int,2> new_pos = next_steps.head();
  //   next_steps.pop();
  //   if(
  //   return ;
  // }
}

void cleanup() {
  for(int i = MIN_R; i < MAX_R; ++i) {
    for(int j = MIN_C; j < MAX_C; ++j) {
      visible[i][j] = visited[i][j] = false;
      maze[i][j] = 0;
    }
  }
  exit_found = false;
}

void fake_piece(std::array<std::array<int, 3>, 3> fake) {
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      piece[i][j] = fake[i][j];
}

void fake_position(int new_r, int new_c, Direction new_direction) {
  r = new_r;
  c = new_c;
  current_direction = new_direction;
}

void test_maze_piece(int x, int y, std::array<std::array<int, 3>, 3> fake) {
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      ASSERT(maze[x + i][y + j] == fake[i][j]);
}

void test_piece_plug() {
  fake_position(5, 10, Direction::UP);
  fake_piece({1,1,1, 0,0,1, 0,0,1});
  plug_piece();
  test_maze_piece(4, 9, {1,1,1, 0,0,1, 0,0,1});

  fake_position(8, 11, Direction::LEFT);
  fake_piece({1,1,1, 0,0,1, 0,0,1});
  plug_piece();
  test_maze_piece(7, 10, {1,1,1, 1,0,0, 1,0,0});

  fake_position(2, 3, Direction::RIGHT);
  fake_piece({1,1,1, 0,0,1, 0,0,1});
  plug_piece();
  test_maze_piece(1, 2, {0,0,1, 0,0,1, 1,1,1});

  fake_position(8, 11, Direction::DOWN);
  fake_piece({1,1,1, 0,0,1, 0,0,1});
  plug_piece();
  test_maze_piece(7, 10, {1,0,0, 1,0,0, 1,1,1});
}

void test_directions() {
  ASSERT(diff_directions(Direction::UP, Direction::UP) == Direction::UP);
  ASSERT(diff_directions(Direction::DOWN, Direction::DOWN) == Direction::UP);
  ASSERT(diff_directions(Direction::DOWN, Direction::RIGHT) == Direction::LEFT);
  ASSERT(diff_directions(Direction::DOWN, Direction::LEFT) == Direction::RIGHT);
  ASSERT(diff_directions(Direction::LEFT, Direction::UP) == Direction::RIGHT);

  current_direction = Direction::UP;
  ASSERT(Direction::UP == new_direction(-1, 0));
  ASSERT(Direction::RIGHT == new_direction(0, +1));
  ASSERT(Direction::DOWN == new_direction(+1, 0));
  ASSERT(Direction::LEFT == new_direction(0, -1));
  current_direction = Direction::LEFT;
  ASSERT(Direction::RIGHT == new_direction(-1, 0));
  ASSERT(Direction::DOWN == new_direction(0, +1));
  ASSERT(Direction::LEFT == new_direction(+1, 0));
  ASSERT(Direction::UP == new_direction(0, -1));
}

void test_empty_search() {
  int sr, sc, rr, cc, f;
  std::cin >> sr >> sc >> rr >> cc >> r >> c;
  cleanup();
  for(int i = 0; i < rr; ++i)
    for(int j = 0; j < cc; ++j)
      cin >> maze[sr + i][sc + j];
  for(int i = 0; i < rr; ++i)
    for(int j = 0; j < cc; ++j) {
      cin >> f;
      visible[sr + i][sc + j] = f == 1;
    }
  for(int i = 0; i < rr; ++i)
    for(int j = 0; j < cc; ++j) {
      cin >> f;
      visited[sr + i][sc + j] = f == 1;
    }
  std::queue<std::array<int, 2>> path = visible_path_to_first_empty();
  while(!path.empty()) {
    std::array<int, 2> cell = path.front();
    path.pop();
    std::cout << cell[0] << " " << cell[1] << "\n";
  }
  std::cout << "\n";
}

void unit_tests() {
  test_piece_plug();
  test_directions();
  test_empty_search();
}

int main() {
  UNIT_TESTS();
  std::cout << direction_names[sum_directions(Direction::DOWN, Direction::RIGHT)] << std::endl;
  return 0;
}
