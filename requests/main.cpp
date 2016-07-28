#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

class SliceList {
public:
  using Slice = std::pair<int, int>;
  explicit SliceList(int threshold = 2):threshold{threshold} {
  }

  Slice* left_bound(Slice* in_slice) {
    for(Slice* slice : slices) {
      if(slice->first > in_slice->first) return nullptr;
      if(slice->second >= in_slice->first) return slice;
    }
    return nullptr;
  }

  Slice* right_bound(Slice* in_slice) {
    for(Slice* slice : slices) {
      if(slice->first > in_slice->second) return nullptr;
      if(slice->second >= in_slice->second) return slice;
    }
    return nullptr;
  }

  void operator<<(Slice* new_slice) {
    if(slices.empty()) {
      #ifdef ALGO_DEBUG
      std::cerr << "put first slice " << std::endl;
      #endif
      if(new_slice->second - new_slice->first + 1 >= threshold)
        slices.push_front(new_slice);
      return;
    }
    std::list<Slice*>::iterator sliceIter = slices.begin();
    while(sliceIter != slices.end()) {
      Slice* slice = *sliceIter;
      if(slice->first > new_slice->second) {
        #ifdef ALGO_DEBUG
        std::cerr << "push back slice " << slice->first << " " << new_slice->second << std::endl;
        #endif
        if(new_slice->second - new_slice->first + 1 >= threshold)
          slices.insert(sliceIter, new_slice);
        return;
      } else if(contains(slice, new_slice)) {
        #ifdef ALGO_DEBUG
        std::cerr << "inner slice " << std::endl;
        #endif
        if(new_slice->first - slice->first >= threshold) {
          #ifdef ALGO_DEBUG
          std::cerr << "add " << slice->first << "-" << (new_slice->first - 1) << std::endl;
          #endif
          slices.insert(sliceIter, new Slice(slice->first, new_slice->first - 1));
        }
        if(new_slice->second - new_slice->first + 1 >= threshold) {
          #ifdef ALGO_DEBUG
          std::cerr << "add " << new_slice->first << "-" << new_slice->second << std::endl;
          #endif
          slices.insert(sliceIter, new_slice);
        }
        if(slice->second - new_slice->second >= threshold) {
          #ifdef ALGO_DEBUG
          std::cerr << "add " << (new_slice->second + 1) << "-" << slice->second << std::endl;
          #endif
          slices.insert(sliceIter, new Slice(new_slice->second + 1, slice->second));
        }
        sliceIter = slices.erase(sliceIter);
        delete slice;
        return;
      } else if(slice->first < new_slice->first && slice->second >= new_slice->first) {
        #ifdef ALGO_DEBUG
        std::cerr << "left bound slice " << std::endl;
        #endif
        if(new_slice->first - slice->first < threshold) {
          sliceIter = slices.erase(sliceIter);
          delete slice;
          #ifdef ALGO_DEBUG
          std::cerr << "size: " << (slices.size()) << std::endl;
          #endif
          continue;
        }
        slice->second = new_slice->first - 1;
        ++sliceIter;
      } else if(containsInclusive(new_slice, slice)) {
        #ifdef ALGO_DEBUG
        std::cerr << "outer slice " << std::endl;
        #endif
        sliceIter = slices.erase(sliceIter);
        delete slice;
        continue;
      } else if(slice->first <= new_slice->second && slice->second >= new_slice->second) {
        #ifdef ALGO_DEBUG
        std::cerr << "right bound slice " << std::endl;
        #endif
        if(slice->second - new_slice->second < threshold) {
          sliceIter = slices.erase(sliceIter);
          delete slice;
        } else slice->first = new_slice->second + 1;
        if(new_slice->second - new_slice->first + 1 >= threshold)
          slices.insert(sliceIter, new_slice);
        return;
      }
      ++sliceIter;
    }
    #ifdef ALGO_DEBUG
    std::cerr << "push into end" << std::endl;
    #endif
    if(new_slice->second - new_slice->first + 1 >= threshold)
      slices.insert(sliceIter, new_slice);
  }

  const int threshold = 10;

  std::list<Slice*> slices;

  static void print(Slice* slice, std::ostream& output) {
    if(slice == nullptr)
      output << -1;
    else
      output << slice->first << " " << slice->second;
  }

  static bool contains(Slice* outer, Slice* inner) {
    return outer->first < inner->first && outer->second > inner->second;
  }

  static bool containsInclusive(Slice* outer, Slice* inner) {
    return outer->first <= inner->first && outer->second >= inner->second;
  }
};

template<class T>
class PartialySortedArray {
public:
  explicit PartialySortedArray(int capacity):
    capacity{capacity}
  {
    data.resize(capacity);
  };
  ~PartialySortedArray() {
  }

  void sort(int left, int right) {
    SliceList::Slice* new_slice = new SliceList::Slice(left, right);
    SliceList::Slice* left_sorted = sorted_areas.left_bound(new_slice);
    if(left_sorted != nullptr && SliceList::contains(left_sorted, new_slice)) return;
    SliceList::Slice* right_sorted = sorted_areas.right_bound(new_slice);

    // std::cerr << "adding " << left << "-" << right << std::endl;

    if(left_sorted == nullptr && right_sorted == nullptr) {
      // std::cerr << "just sorting " << std::endl;
      std::sort(data.begin() + left, data.begin() + right + 1);
      return;
    }
    if(left_sorted == nullptr) {
      // std::cerr << "merging left " << left_sorted->second << " " << right << std::endl;
      sort(left_sorted->second + 1, right);
      merge(left, left_sorted->second, right);
    } else if(right_sorted == nullptr) {
      // std::cerr << "merging right " << left << " " << right_sorted->first << std::endl;
      sort(left, right_sorted->first - 1);
      merge(left, right_sorted->first - 1, right);
    } else {
      // std::cerr << "merging three " << left_sorted->second << " " << right_sorted->first << std::endl;
      sort(left_sorted->second + 1, right_sorted->first - 1);
      merge3(left, left_sorted->second, right_sorted->first, right);
    }
    sorted_areas << new_slice;
  }

  void merge(int left, int middle, int right) {
    std::vector<int> left_copy{data.begin() + left, data.begin() + middle};
    std::vector<int> right_copy{data.begin() + (middle + 1), data.begin() + right};
    int l1 = 0, l1l = middle - left + 1,
      l2 = 0, l2l = right - middle - 1,
      i = 0;
    while(l1 < l1l && l2 < l2l) {
      if(left_copy[l1] < right_copy[l2]) {
        data[i++] = left_copy[l1++];
      } else {
        data[i++] = right_copy[l2++];
      }
    }
    while(l1 < l1l) data[i++] = left_copy[l1++];
    while(l2 < l2l) data[i++] = left_copy[l2++];
  }

  void merge3(int left, int middle1, int middle2, int right) {
    std::vector<int> left_copy{data.begin() + left, data.begin() + middle1};
    std::vector<int> middle_copy{data.begin() + (middle1 + 1), data.begin() + middle2};
    std::vector<int> right_copy{data.begin() + (middle2 + 1), data.begin() + right};
    int l1 = 0, l1l = middle1 - left + 1,
      l2 = 0, l2l = middle2 - middle1 - 1,
      l3 = 0, l3l = right - middle2 - 1,
      i = 0;
    while(l1 < l1l || l2 < l2l || l3 < l3l) {
      if(l1 < l1l) {
        if(l2 < l2l && left_copy[l1] <= middle_copy[l2]) {
          if(l3 < l3l && left_copy[l1] <= right_copy[l3]) {
            data[i++] = left_copy[l1++];
            continue;
          } else if(l3 == l3l) {
            data[i++] = left_copy[l1++];
            continue;
          }
        } else if(l2 == l2l) {
          if(l3 < l3l && left_copy[l1] <= right_copy[l3]) {
            data[i++] = left_copy[l1++];
            continue;
          } else if(l3 == l3l) {
            data[i++] = left_copy[l1++];
            continue;
          }
        }
      }
      if(l2 < l2l) {
        if(l3 < l3l && middle_copy[l2] <= right_copy[l3]) {
          data[i++] = middle_copy[l2++];
          continue;
        } else if(l3 == l3l) {
          data[i++] = middle_copy[l2++];
          continue;
        }
      }
      data[i++] = right_copy[l3++];
    }
  }

  std::vector<T> data;
  SliceList sorted_areas;
  int capacity;
};

// void force_sort(long* start, long* end) {
//   for(long* next = end; next > start; --next) {
//     long* winner = next;
//     for(long* candidate = start; candidate < next; ++candidate) {
//       if(*candidate > *winner) winner = candidate;
//     }
//     if(winner != next) {
//       long swap = (*next);
//       *next = *winner;
//       *winner = swap;
//     }
//   }
// }

// void quick_sort(long* start, long* end, long* break_point) {
//   if(
// }

// template<class T>
// void test(PartialySortedArray<T>& seq,
//           int l, int r,
//           int ll, int lr,
//           int rl, int rr)
// {
//   auto lit = seq.find_left_bound(l, r);
//   if(ll != -1) {
//   } else {
//     if(nullptr != lit) std::cout << l << "-" << r << " : " << lit->left << "-" << lit->right << std::endl;
//   }
// }

int main() {
  int n, q, k;
  std::cin >> n >> q >> k;
  PartialySortedArray<long> arr{n};
  for(int i = 0; i < n; ++i) {
    std::cin >> arr.data[i];
  }
  for(int i = 0; i < q; ++i) {
    int left, right;
    std::cin >> left >> right;
    arr.sort(left, right);
  }
  std::cout << arr.data[k] << std::endl;
}
