#include <iostream>
#include <iomanip>
#include <algorithm>

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

using ll = long long;

constexpr ll MOD = 1e9+9;

int size, m; // size = m * m

template<class T>
class vector {
  T *vals;
 public:
  vector() : vals{new T[size]} {
    std::fill_n(vals, size, 0);
  }

  vector(int val) : vals{new T[size]} {
    std::fill_n(vals, size, 0);
    vals[val] = 1;
  }

  // vector(vector &&other) {
  //   vals = other.vals;
  //   other.vals = nullptr;
  // }

  ~vector() {
    if (vals != nullptr) {
      delete[] vals;
    }
  }

  vector& operator+=(const vector &other) {
    for(int i = 0; i < size; ++i) {
      (*this)[i] = ((*this)[i] + other[i]) % MOD;
    }
    return *this;
  }

  T& operator[](int pos) {
    return vals[pos];
  }

  T operator[](int pos) const {
    return vals[pos];
  }

  vector& operator=(vector &other) {
    for(int i = 0; i < size; ++i) {
      vals[i] = other.vals[i];
    }
  }
};

template<class T>
vector<T> operator+(const vector<T> &one, const vector<T> &two) {
  vector<T> resp;
  for(int i = 0; i < size; ++i) {
    resp[i] = (one[i] + two[i]) % MOD;
  }
  return resp;
}

template<class T>
T take(const T *array, const vector<T> &pos) {
  T res = 0;
  for(int r = 0; r < m; ++r) {
    for(int c = 0; c < m; ++c) {
      res = (res + array[r * m + c] * pos[r * m + c]) % MOD;
    }
  }
  return res;
}

template<class T>
vector<T>* take(vector<T> **array, const vector<T> &pos) {
  vector<T> *res = new vector<T>;
  for(int i = 0; i < size; ++i) {
    vector<T> *target = array[i];
    vector<T> newVec;
    T multi = pos[i];
    for(int j = 0; j < size; ++j)
      (*res)[j] = ((*res)[j] + (*target)[j] * multi) % MOD;
  }
  return res;
}

#ifdef UNITS
void unit_tests() {
  test_header("test units");}

#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  ll s;
  int d;
  std::cin >> s >> m >> d;
  size = m * m;
  // count initial matrix with values up to s = m
  ll *S = new ll[m * m];
  for(int r = 0; r < m; ++r) {
    S[r * m + r] = 1;
    for(int c = 0; c < r; ++c)
      S[r * m + c] = 0;
  }
  for(int c = 1; c < m; ++c) {
    for(int r = 0; r < m; ++r) {
      if(r >= c) continue;
      S[r * m + c] = 0;
      for(int k = std::max(0, r - d); k <= std::min(m - 1, r + d); ++k) {
        S[r * m + c] = (S[r * m + c] + S[k * m + c - r - 1]) % MOD;
      }
    }
  }
  if (s < m) {
    ll total = 0ll;
    for(int r = 0; r < m; ++r) {
      total = (total + S[r * m + s - 1]) % MOD;
    }
    std::cout << total << std::endl;
    delete[] S;
    return 0;
  }
  vector<ll> **X = new vector<ll>*[m * m];
  for(int r = 0; r < m; ++r)
    for(int c = 0; c < m; ++c)
      X[r * m + c] = new vector<ll>(r * m + c);
  ll left = s - m, id = -1;
  int dec[100];
  while(left > 0) {
    ++id;
    dec[id] = left % 2;
    left >>= 1;
  }
  while(id >= 0) {
    vector<ll> **X2 = new vector<ll>*[m * m];
    for (int i = 0; i < size; ++i) {
      X2[i] = take(X, *X[i]);
    }
    for (int i = 0; i < size; ++i) {
      delete X[i];
    }
    delete[] X;
    X = X2;
    if(dec[id] == 1) {
      vector<ll> **next = new vector<ll>*[m];
      for(int r = 0; r < m; ++r) {
        next[r] = new vector<ll>;
        for(int dr = std::max(0, r - d); dr <= std::min(m - 1, r + d); ++dr) {
          (*next[r]) += *X[dr * m + m - 1 - r];
        }
      }
      for(int r = 0; r < m; ++r) {
        delete X[r * m];
        for(int c = 0; c < m - 1; ++c) {
          X[r * m + c] = X[r * m + c + 1];
        }
        X[r * m + m - 1] = next[r];
      }
      delete[] next;
    }
    --id;
  }
  ll total = 0ll;
  for(int r = 0; r < m; ++r) {
    total = (total + take(S, *X[(r + 1) * m - 1])) % MOD;
  }
  std::cout << total << std::endl;
  for(int r = 0; r < m; ++r)
    for(int c = 0; c < m; ++c)
      delete X[r * m + c];
  delete[] X;
  delete[] S;
  return 0;
}
