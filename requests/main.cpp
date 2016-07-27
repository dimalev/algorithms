#include <iostream>
#include <list>

template<class T>
class PartialySortedArray {
public:
  explicit PartialySortedArray(int capacity):
    data{(T*)(malloc(sizeof(T) * capacity))},
    capacity{capacity}
  {
  };
  ~PartialySortedArray() {
    free(data);
  }

  std::iterator<std::pair<T, T>>* find_left_bound(int left, int right) {
    std::iterator<std::pair<T, T>>* it = sorted_areas.begin();
    if((*it)->left > left) return nullptr;
    while(it < sorted_areas.end()) {
      if((*it)->left > left) return nullptr;
      if((*it)->right >= left) return it;
      it->next();
    }
    return nullptr;
  };
  std::iterator<std::pair<T, T>>* find_right_bound(int left, int right) {
    std::iterator<std::pair<T, T>>* it = sorted_areas.begin();
    if((*it)->left > right) return nullptr;
    while(it < sorted_areas.end()) {
      if((*it)->left > right) return nullptr;
      if((*it)->right >= right) return it;
      it->next();
    }
    return nullptr;
  };

  T* data;
  std::list<std::pair<T, T>> sorted_areas;
  int capacity;
};

void force_sort(long* start, long* end) {
  for(long* next = end; next > start; --next) {
    long* winner = next;
    for(long* candidate = start; candidate < next; ++candidate) {
      if(*candidate > *winner) winner = candidate;
    }
    if(winner != next) {
      long swap = (*next);
      *next = *winner;
      *winner = swap;
    }
  }
}

// void quick_sort(long* start, long* end, long* break_point) {
//   if(
// }

template<class T>
void test(PartialySortedArray<T>& seq,
          int l, int r,
          int ll, int lr,
          int rl, int rr)
{
  auto lit = seq.find_left_bound(l, r);
  if(ll != -1) {
  } else {
    if(nullptr != lit) std::cout << l << "-" << r << " : " << lit->left << "-" << lit->right << std::endl;
  }
}

int main() {
  int n, q, k;
  std::cin >> n >> q >> k;
  PartialySortedArray<long> seq{n};
  seq.sorted_areas.push_back(std::pair<int, int>(0, 3));
  seq.sorted_areas.push_back(std::pair<int, int>(5, 10));
  seq.sorted_areas.push_back(std::pair<int, int>(11, 17));
  test(seq, 2, 8, 0, 3, 5, 10);
  for(int i = 0; i < n; ++i) std::cin >> seq.data[i];
  force_sort(seq.data, seq.data + seq.capacity - 1);
  for(int i = 0; i < seq.capacity; ++i)
    std::cout << seq.data[i] << std::endl;
  // std::list<std::pair<int, int>> sorted;
  // for(int i = 0; i < q; ++i) {
  //   int l, r, sl;
  //   std::cin >> l >> r;
  //   sl = l;
  //   // std::iterator<std::pair<int, int>> st = sorted.begin();
  //   // bool found = false;
  //   // while(st < sorted.end()) {
  //   //   if((*st).key > l) break;
  //   //   if((*st).key <= l && (*st).value > l) {
  //   //     found = true;
  //   //     break;
  //   //   }
  //   // }
  //   // if(found) {
  //   //   sl = (*st).value;
  //   //   if((*st).key < l) {
  //   //     std::iterator<std::pair<int>> strest = sorted.insert(st, std::pair<int, int>((*st).key, l));
  //   //   }
  //   // }
  //   while(++sl <= r) {
  //     int pl = l, pr = sl - 1, pm = (pl + pr) / 2;
  //     while(pr > pl) {
  //       if(seq[pm] > seq[sl]) pl = pm;
  //       else if(seq[pm] < seq[sl]) pr = pm;
  //       else {
  //         pl = pm;
  //         pr = pm;
  //       }
  //     }
  //   }
  // }
}
