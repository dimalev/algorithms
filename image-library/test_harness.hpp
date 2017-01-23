#ifndef IMAGE_LIBRARY_TEST_HARNESS_H_
#define IMAGE_LIBRARY_TEST_HARNESS_H_

/**
 * Helpers to write better test. Allow creating tests who register themselves,
 * throw excruciating TestError in case of something, and report asserts.
 *
 * Use START_TEST(test_name) and END_TEST to wrap logically related test cases
 * into single suite.
 *
 * Use ASSERT to test something truethy (will appear in std::cout with OK
 * suffics), or become a reason in test error.
 */

std::string current_test_name;

class TestError {
  std::string m_reason;
public:
  TestError(std::string reason) : m_reason{reason} {}
  std::string reason() { return m_reason; }
};

#define START_TEST(test_name) void test_name() { current_test_name = #test_name;
#define END_TEST std::cout << current_test_name << " - OK" << std::endl; }

#define ASSERT(what, message) \
  if(!(what)) throw TestError(message); \
  else std::cout << message << " - OK" << std::endl;

#endif
