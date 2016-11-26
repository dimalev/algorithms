#define ASSERT(expr) \
  if(expr) { } \
  else { \
    std::cerr << "\n(AE)\n(AE)\t" << #expr << " FAILED!\n" \
    << "(AE)\tline: " << __LINE__ << "\n(AE)\n"; \
  }

#define TRACE(message) \
  std::cerr << message;

#define TRACE_LINE(message) \
  std::cerr << message << std::endl;

#ifdef UNITS
#define UNIT_TESTS() unit_tests(); return 0;
#else
#define UNIT_TESTS()
#endif
