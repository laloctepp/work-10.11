#include <iostream>

struct IntArray {
  void add (int i);
  int get (size_t id) const;
  size_t size() const;
  int last() const;
  IntArray(int i);
  ~IntArray();
};

IntArray::~Intarray() {
  delete[] a;
}

int main() 
{
  int next = 0;
  std::cin >> next;

  try {
  IntArray a(next);    //вызов конструктора по умолчанию
  //a.add(next);   //add
  while (std::cin >> next) {
    a.add(next);
  }
  if (std::cin.fail()) {
    return 1;
  }
  size_t count = 1;

  for (size_t i = 0; i < a.size()-1; ++i) {
    int d = a.get(i);
    count += !(d % a.last());
  }
  std::cout << count << "\n";
  return 0;
  }
  catch (const std::bad_alloc()) {
  return 2;
  }
}
