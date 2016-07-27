#include <iostream>
#include <list>

class SliceList {
public:
  using Slice = std::pair<int, int>;
  SliceList() {
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
      if(new_slice->second - new_slice->first + 1 >= threshold)
        slices.push_front(new_slice);
      return;
    }
    auto sliceIter = slices.begin();
    while(sliceIter != slices.end()) {
      Slice* slice = *sliceIter;
      if(slice->first < new_slice->second) {
        if(new_slice->second - new_slice->first + 1 >= threshold)
          slices.insert(sliceIter, new_slice);
        return;
      } else if(slice->first < new_slice->first && slice->second > new_slice->second) {
        slices.erase(sliceIter);
        if(new_slice->first - slice->first >= threshold)
          slices.insert(sliceIter, new Slice(slice->first, new_slice->first - 1));
        if(new_slice->second - new_slice->first + 1 >= threshold)
          slices.insert(sliceIter, new_slice);
        if(slice->second - new_slice->second >= threshold)
          slices.insert(sliceIter, new Slice(new_slice->second + 1, slice->second));
        delete slice;
        return;
      } else if(slice->first < new_slice->first && slice->second >= new_slice->first) {
        if(new_slice->first - slice->first < threshold) {
          slices.erase(sliceIter);
          delete slice;
          continue;
        }
        slice->second = new_slice->first - 1;
        ++sliceIter;
      } else if(slice->first >= new_slice->first && slice->second <= new_slice->second) {
        slices.erase(sliceIter);
        delete slice;
        continue;
      } else if(slice->first <= new_slice->second && slice->second >= new_slice->second) {
        if(slice->second - new_slice->second < threshold) {
          slices.erase(sliceIter);
          delete slice;
        } else slice->first = new_slice->second + 1;
        if(new_slice->second - new_slice->first + 1 >= threshold)
          slices.insert(sliceIter, new_slice);
        return;
      }
    }
    slices.push_back(new_slice);
  }

  static const int threshold = 2;

  std::list<Slice*> slices;

  static void print(Slice* slice) {
    if(slice == nullptr)
      std::cout << -1;
    else
      std::cout << slice->first << " " << slice->second;
  }
};

int main() {
  int n;
  std::cin >> n;
  SliceList slices;
  while(n--) {
    int l, r;
    std::cin >> l >> r;
    slices << new SliceList::Slice(l, r);
  }
  std::cin >> n;
  while(n--) {
    int l, r;
    std::cin >> l >> r;
    SliceList::Slice in_slice(l, r);
    SliceList::Slice* left = slices.left_bound(&in_slice);
    SliceList::Slice* right = slices.right_bound(&in_slice);
    SliceList::print(left);
    std::cout << " ";
    SliceList::print(right);
    std::cout << std::endl;
  }
  return 0;
}
