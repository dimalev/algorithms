#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

int main() {
  byte digest[CryptoPP::SHA256::DIGESTSIZE];
  std::fill_n(digest, CryptoPP::SHA256::DIGESTSIZE, 0);
  std::ifstream video_file;
  video_file.open("test.mp4", std::ifstream::binary);
  if(video_file) {
    video_file.seekg(0, video_file.end);
    int length = video_file.tellg();
    bool has_tag = false;
    for(int k = length / 1024; k >= 0; --k) {
      video_file.seekg(k * 1024);
      char buffer[1024 + CryptoPP::SHA256::DIGESTSIZE];
      std::fill_n(buffer, 1024, 0);
      video_file.read(buffer, std::min(1024, length - k * 1024));
      std::copy_n(digest, CryptoPP::SHA256::DIGESTSIZE, buffer + 1024);
      CryptoPP::SHA256().CalculateDigest(
          digest,
          (const byte*)buffer,
          (has_tag ? 1024 + CryptoPP::SHA256::DIGESTSIZE : video_file.gcount()));
      has_tag = true;
    }
    video_file.close();
    CryptoPP::HexEncoder encoder;
    std::string output;

    encoder.Attach( new CryptoPP::StringSink( output ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();

    std::transform(output.begin(), output.end(), output.begin(), ::tolower);
    std::cout << output << std::endl;
    // std::cout << std::hex;
    // for(int i = 0; i < CryptoPP::SHA::DIGESTSIZE; ++i)
    //   std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)digest[i] << std::endl;
    // std::cout << std::endl;
  }
  return 0;
}
