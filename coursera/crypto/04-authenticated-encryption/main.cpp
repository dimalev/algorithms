#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;
  long response_code;

  curl_global_init(CURL_GLOBAL_ALL);

  std::string url = "http://crypto-class.appspot.com/po?er=";
  std::string ciphertext = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4";
  std::vector<unsigned int> bytes;
  std::stringstream ss;
  for(int i = 0; i < ciphertext.size(); i += 2) {
    ss.clear();
    ss << std::hex << ciphertext.substr(i, 2);
    unsigned int b;
    ss >> b;
    bytes.push_back(b);
  }

  std::vector<unsigned int> found;
  for(int i = 0; i < 9; ++i) found.push_back(9);
  for(int i = found.size(); i < 16; ++i) {
    bool cracked = false;
    for(int j = 0; j <= 255; ++j) {
      std::string hacked = ciphertext;

      unsigned int new_v;
      std::string new_s;

      for(int k = 0; k < i; ++k) {
        new_v = (*(bytes.rbegin() + k + 16)) xor found[k] xor (i + 1);
        ss.clear();
        ss << std::hex << std::setfill('0') << std::setw(2) << (int)new_v;
        ss >> new_s;
        hacked.replace(ciphertext.size() - 2 * (k + 1) - 32, 2, new_s);
      }

      new_v = (*(bytes.rbegin() + i + 16)) xor j xor (i + 1);

      ss.clear();
      ss << std::hex << std::setfill('0') << std::setw(2) << (int)new_v;
      ss >> new_s;
      hacked.replace(ciphertext.size() - 2 * (i + 1) - 32, 2, new_s);
      std::cout << hacked << std::endl;

      std::string full_path = url + hacked;

      bool first = true;
      do {
        if(!first) {
          std::cout << ".";
          std::cout.flush();
        }
        first = false;
        /* init the curl session */
        curl = curl_easy_init();

        /* set URL to get */
        curl_easy_setopt(curl, CURLOPT_URL, full_path.c_str());

        /* no progress meter please */
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        /* don't wait too long */
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);

        /* get it! */
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
          // std::cout << "failed to make a call\n";
        } else {

          res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
          if(res == CURLE_OK) {
            std::cout << j << " response: " << response_code << "\n";
            if(response_code == 404) {
              found.push_back(j);
              cracked = true;
            } else if(response_code != 403 && response_code != 200) {
              res = CURL_LAST;
            }
          } else {
            std::cout << "failed to extract response code\n";
          }

        }
        /* cleanup curl stuff */
        curl_easy_cleanup(curl);
      } while(res != CURLE_OK);
      if(cracked) break;
    }
  }
      for(int b : found) {
        std::cout << b << std::endl;
      }
  return 0;
}


//http://crypto-class.appspot.com/po?er=f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4
