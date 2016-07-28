#include <iostream>
#include <list>

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

  const int threshold = 2;

  std::list<Slice*> slices;

  static void print(Slice* slice, std::ostream& output) {
    if(slice == nullptr)
      output << -1;
    else
      output << slice->first << " " << slice->second;
  }

  static void contains(Slice* outer, Slice* inner) {
    return outer->first < inner.first && outer->second > inner->second;
  }

  static void containsInclusive(Slice* outer, Slice* inner) {
    return outer->first <= inner.first && outer->second >= inner->second;
  }
};

int main() {
  int n, t;
  std::cin >> n >> t;
  SliceList slices{t};
  while(n--) {
    int l, r;
    std::cin >> l >> r;
    #ifdef ALGO_DEBUG
    std::cerr << "processing: " << l << "-" << r << std::endl;
    #endif
    slices << new SliceList::Slice(l, r);
  }
  #ifdef ALGO_DEBUG
  std::cerr << "processing complete" << std::endl;
  for(SliceList::Slice* slice : slices.slices) {
    SliceList::print(slice, std::cerr);
    std::cerr << ", ";
  }
  std::cerr << std::endl;
  #endif
  std::cin >> n;
  while(n--) {
    int l, r;
    std::cin >> l >> r;
    SliceList::Slice in_slice(l, r);
    SliceList::Slice* left = slices.left_bound(&in_slice);
    SliceList::Slice* right = slices.right_bound(&in_slice);
    SliceList::print(left, std::cout);
    std::cout << " ";
    SliceList::print(right, std::cout);
    std::cout << std::endl;
  }
  return 0;
}
