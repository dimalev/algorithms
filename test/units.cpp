/*
  Functions used in unit testing.

  If function fails - it writes (FF) into std::cout.

  If function succeeds - it writes (OK) into std::cout.
 */

#include <iostream>
#include <string>

class UnitsError {
public:
  std::string message;
  UnitsError(std::string m) : message{m} {}
};

class HeaderError : public UnitsError {
public:
  HeaderError(std::string m) : UnitsError{m} {}
};

template<class A, class B>
class EqualsError : public UnitsError {
public:
  A expected;
  B actual;
  EqualsError(std::string m, A e, B a)
    : UnitsError{m}, expected{e}, actual{a} {}
};

/*
  Reads given string from std::in, checks for validity, and prints it back into
  std::out.

  This function is intended to ease unit test input and output files management,
  by providing sections of tests.
 */
void test_header(const std::string &in_header) {
  std::string header;
  std::getline(std::cin, header);
  if(header.empty()) std::getline(std::cin, header);
  if(header != in_header) {
    std::cout << "(FF) Header \"" << in_header << "\" failed."
              << " Got \"" << header << "\".\n";
    throw new HeaderError{std::string{in_header}};
  }
  std::cout << "(OK) " << header << "\n";
}
