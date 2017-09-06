// replace:
// Pay Bob 100$
// Pay Bob 500$
// 0123456789

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int main() {
  std::stringstream hex_convert;
  std::string iv = "20814804c1767293b99f1d9cab3bc3e7";
  int c_id = 8;
  char from = '1', to = '5';
  std::string iv_at_c = iv.substr(c_id * 2, 2);
  hex_convert << iv_at_c;
  int c_enc;
  hex_convert >> std::hex >> c_enc;
  int c_enc_broken = c_enc xor from xor to;
  std::string new_hex;
  std::stringstream back_hex_convert;
  back_hex_convert << std::hex << c_enc_broken;
  back_hex_convert >> new_hex;
  std::cout << (int)c_enc_broken << " -> " << back_hex_convert.str() << std::endl;
  iv.replace(c_id * 2, 2, new_hex);
  std::cout << iv << std::endl;
}
