#include <iostream>
#include <string>
#include <random>
#include <vector>

int main(int argc, char** argv) {
  constexpr int S = 1000, K = 66, N = 100;

  bool is_debug = false;
  if(argc > 1) {
    std::string arg{argv[1]};
    if(arg == "--debug") {
      is_debug = true;
    }
  }

  std::vector<bool> smiles(S);
  std::fill(smiles.begin(), smiles.end(), true);

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, S - K);

  for(int i = 0; i < N; ++i) {
    int random_flip = distribution(generator);
    if(is_debug) {
      std::cout << "flipping: " << random_flip << "\n";
    }
    for(int j = 0; j < K; ++j) {
      smiles[random_flip + j] = !smiles[random_flip + j];
    }
  }

  for(int i = 0; i < S; ++i) {
    std::cout << (smiles[i] ? "+" : "-");
  }
  std::cout << std::endl;

  return 0;
}
