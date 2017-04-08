#include <iostream>
#include <string>

bool is_tidy(int number) {
  int first = number % 10;
  number /= 10;
  while(number > 0) {
    int next = number % 10;
    number /= 10;
    if(next > first) {
      return false;
    }
    first = next;
  }
  return true;
}

int main(int argc, char** argv) {
  constexpr int T = 10000;
  if(argc < 2) {
    std::cout << "use --input or --output to generate either input or output\n";
    return 0;
  }
  std::string mode{argv[1]};
  bool is_input = mode == "--input";
  bool is_output = mode == "--output";
  if(!is_input && !is_output) {
    std::cerr << "invalid mode " << mode << "\n";
    return 0;
  }
  if(is_input) {
    std::cout << T << "\n";
  }
  int biggest = 0;
  for(int i = 1; i <= T; ++i) {
    if(is_input) {
      std::cout << i << "\n";
    } else {
      if(is_tidy(i)) {
        biggest = i;
      }
      std::cout << "Case #" << i << ": " << biggest << "\n";
    }
  }
}
