#include <iostream>
#include <vector>

template<class T>
class Heap {
public:
  Heap(): size{0} { data.resize(1); }
  void put(T v);
  void remove(T v);
  int left(int pos) const;
  bool hasLeft(int pos) const;
  int right(int pos) const;
  bool hasRight(int pos) const;
  int parent(int pos) const;
  bool hasParent(int pos) const;
  bool hasPos(int pos) const;
  int getPos(T v) const;
  int getPos(T v, int from) const;
  T getMin() const;
  int getSize() const;

protected:
  void fixUp(int pos);
  void fixDown(int pos);
  int fixNode(int pos);
  void swap(int one, int two);
  int size;
  std::vector<T> data;
};

template<class T>
T Heap<T>::getMin() const {
  return data[0];
}

template<class T>
int Heap<T>::left(int pos) const {
  return 2 * pos + 1;
}
template<class T>
bool Heap<T>::hasLeft(int pos) const {
  return hasPos(pos) && hasPos(left(pos));
}
template<class T>
int Heap<T>::right(int pos) const {
  return 2 * (pos + 1);
}
template<class T>
bool Heap<T>::hasRight(int pos) const {
  return hasPos(pos) && hasPos(right(pos));
}
template<class T>
int Heap<T>::parent(int pos) const {
  return (pos - 1) / 2;
}
template<class T>
bool Heap<T>::hasParent(int pos) const {
  return hasPos(pos) && hasPos(parent(pos));
}
template<class T>
bool Heap<T>::hasPos(int pos) const {
  return pos >= 0 && pos < size;
}

template<class T>
void Heap<T>::put(T v) {
  if(data.size() == size) {
    data.resize(2 * data.size() + 1);
  }
  int pos = size;
  ++size;
  data[pos] = v;
  if(hasParent(pos)) fixUp(parent(pos));
}

template<class T>
void Heap<T>::remove(T v) {
  int pos = getPos(v);
  if(pos < 0) return;
  --size;
  if(size == data.size() / 2 && data.size() > 1)
    data.resize(data.size() / 2);
  if(pos == size) return;
  data[pos] = data[size];
  fixDown(pos);
  if(hasParent(pos)) fixUp(parent(pos));
}

template<class T>
int Heap<T>::getPos(T v) const {
  return getPos(v, 0);
}

template<class T>
int Heap<T>::getPos(T v, int from) const {
  if(!hasPos(from)) return -1;
  if(v == data[from]) return from;
  if(v < data[from]) return -1;
  int leftPos = getPos(v, left(from));
  if(leftPos >= 0) return leftPos;
  int rightPos = getPos(v, right(from));
  if(rightPos >= 0) return rightPos;
  return -1;
}

template<class T>
int Heap<T>::getSize() const {
  return size;
}

template<class T>
void Heap<T>::fixUp(int pos) {
  if(!hasPos(pos)) return;
  int badChild = fixNode(pos);
  if(badChild != -1 && hasParent(pos)) fixUp(parent(pos));
}

template<class T>
void Heap<T>::fixDown(int pos) {
  if(!hasPos(pos)) return;
  int badChild = fixNode(pos);
  if(badChild != -1) fixDown(badChild);
}

template<class T>
int Heap<T>::fixNode(int pos) {
  if(!hasPos(pos)) return -1;
  if(hasLeft(pos) && data[pos] > data[left(pos)]) {
    if(hasRight(pos) && data[left(pos)] > data[right(pos)]) {
      swap(right(pos), pos);
      return right(pos);
    } else {
      swap(left(pos), pos);
      return left(pos);
    }
  } else if(hasRight(pos) && data[pos] > data[right(pos)]) {
    swap(right(pos), pos);
    return right(pos);
  }
  return - 1;
}

template<class T>
void Heap<T>::swap(int left, int right) {
  if(left < 0 || left >= size) return;
  if(right < 0 || right >= size) return;
  T temp = data[left];
  data[left] = data[right];
  data[right] = temp;
}

int main() {
  int n;
  std::cin >> n;
  Heap<int> heap;
  for(int i = 0; i < n; ++i) {
    int op;
    std::cin >> op;
    if(op == 3) {
      std::cout << heap.getMin() << std::endl;
    } else {
      int v;
      std::cin >> v;
      if(op == 1) heap.put(v);
      else heap.remove(v);
    }
  }
  return 0;
}
