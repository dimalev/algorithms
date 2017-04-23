#include <iostream>
#include <algorithm>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void fill(char *buffer, char *proto, int count) {
  for(int i = 0; i < count; ++i) {
    buffer[i] = proto[i % 2];
  }
}

void solve(int t) {
  int colors[6], N;
  std::cin >> N;
  for(int i = 0; i < 6; ++i) {
    std::cin >> colors[i];
  }
  char output[N + 1];
  output[N] = '\0';
  if(colors[0] == colors[3] && colors[0] > 0) {
    if(colors[2] != 0 || colors[1] != 0 || colors[4] != 0 || colors[5] != 0) {
      std::cout << "Case #" << t << ": IMPOSSIBLE\n";
      return;
    }
    fill(output, "RG", N);
    std::cout << "Case #" << t << ": " << output << "\n";
    return;
  }
  if(colors[2] == colors[5] && colors[2] > 0) {
    if(colors[0] != 0 || colors[3] != 0 || colors[4] != 0 || colors[1] != 0) {
      std::cout << "Case #" << t << ": IMPOSSIBLE\n";
      return;
    }
    fill(output, "YV", N);
    std::cout << "Case #" << t << ": " << output << "\n";
    return;
  }
  if(colors[4] == colors[1] && colors[4] > 0) {
    if(colors[0] != 0 || colors[3] != 0 || colors[2] != 0 || colors[5] != 0) {
      std::cout << "Case #" << t << ": IMPOSSIBLE\n";
      return;
    }
    fill(output, "OB", N);
    std::cout << "Case #" << t << ": " << output << "\n";
    return;
  }
  std::map<char, char> counter_char;
  counter_char['R'] = 'G';
  counter_char['Y'] = 'V';
  counter_char['B'] = 'O';
  std::map<char, int> char_index;
  char_index['O'] = 1;
  char_index['G'] = 3;
  char_index['V'] = 5;
  std::multimap<int, char> horses;
  horses.emplace(colors[0] - colors[3], 'R');
  horses.emplace(colors[2] - colors[5], 'Y');
  horses.emplace(colors[4] - colors[1], 'B');
  int count[3];
  char letter[3];
  int h = 0;
  for(auto horse : horses) {
    count[h] = horse.first;
    letter[h] = horse.second;
    ++h;
  }
  if(count[0] < 0) {
    std::cout << "Case #" << t << ": IMPOSSIBLE\n";
    return;
  }
  TRACE_LINE(count[0] << " " << count[1] << " " << count[2]);
  if(count[2] > count[1] + count[0]) {
    std::cout << "Case #" << t << ": IMPOSSIBLE\n";
    return;
  }
  int pos = 0;
  for(int i = 0; i < count[2]; ++i) {
    output[pos++] = letter[2];
    if(colors[char_index[counter_char[letter[2]]]] > 0) {
      char counter_letter = counter_char[letter[2]];
      for(int j = 0; j < colors[char_index[counter_letter]]; ++j) {
        output[pos++] = counter_letter;
        output[pos++] = letter[2];
      }
      colors[char_index[counter_letter]] = 0;
    }
    if(count[1] > count[0]) {
      output[pos++] = letter[1];
      if(colors[char_index[counter_char[letter[1]]]] > 0) {
        char counter_letter = counter_char[letter[1]];
        for(int j = 0; j < colors[char_index[counter_letter]]; ++j) {
          output[pos++] = counter_letter;
          output[pos++] = letter[1];
        }
        colors[char_index[counter_letter]] = 0;
      }
      --count[1];
    } else {
      output[pos++] = letter[0];
      if(colors[char_index[counter_char[letter[0]]]] > 0) {
        char counter_letter = counter_char[letter[0]];
        for(int j = 0; j < colors[char_index[counter_letter]]; ++j) {
          output[pos++] = counter_letter;
          output[pos++] = letter[0];
        }
        colors[char_index[counter_letter]] = 0;
      }
      --count[0];
    }
  }
  while(count[0] > 0 || count[1] > 0) {
    if(count[1] > count[0]) {
      output[pos++] = letter[1];
      if(colors[char_index[counter_char[letter[1]]]] > 0) {
        char counter_letter = counter_char[letter[1]];
        for(int j = 0; j < colors[char_index[counter_letter]]; ++j) {
          output[pos++] = counter_letter;
          output[pos++] = letter[1];
        }
        colors[char_index[counter_letter]] = 0;
      }
      --count[1];
    } else {
      output[pos++] = letter[0];
      if(colors[char_index[counter_char[letter[0]]]] > 0) {
        char counter_letter = counter_char[letter[0]];
        for(int j = 0; j < colors[char_index[counter_letter]]; ++j) {
          output[pos++] = counter_letter;
          output[pos++] = letter[0];
        }
        colors[char_index[counter_letter]] = 0;
      }
      --count[0];
    }
  }
  std::cout << "Case #" << t << ": " << output << "\n";
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 1; t <= T; ++t) solve(t);
  return 0;
}
