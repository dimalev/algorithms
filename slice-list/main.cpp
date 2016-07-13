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
    slices.push_back(new_slice);
  }

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
