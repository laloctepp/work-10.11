#include <iostream>

struct IntArray {
  void add(int i);
  int get(size_t id) const noexcept;
  size_t getSize() const noexcept;
  int last() const noexcept;
  IntArray();
  IntArray(int i);
  ~IntArray();
  int* a;
  size_t size;
  int at(size_t id()) const;
  IntArray(const IntArray & rhs); //конструктор копирования
  IntArray & operator=(const IntArray & rhs); //оператор копирующего присваивания
  IntArray (IntArray && rhs);
  IntArray & operator=(IntArray && rhs);
};

struct IntMatrix {
  IntArray* matrix;
  size_t rows;
  size_t cols;
  IntMatrix(size_t rows, size_t cols);
  ~IntMatrix();
  void command2();
  void command3();
};

int main()
{
  int next = 0;
  std::cin >> next;
  try {
    IntArray a(next);    //вызов конструктора по умолчанию
    while (std::cin >> next) {
      a.add(next);
    }
    if (std::cin.fail() && !(std::cin.eof())) {
      return 1;
    }
    size_t count = 1;
    for (size_t i = 0; i < a.getSize() - 1; ++i) {
      int d = a.get(i);
      count += !(d % a.last());
    }
    std::cout << count << "\n";
  }
  catch (const std::bad_alloc()) {
    return 2;
  }
  return 0;
}

IntArray::~IntArray() {
  delete[] a;
}

IntArray::IntArray() :
  a(new int[1]),
  size(1)
  {
    *a = 0;
  }

IntArray::IntArray(int i) :
  a(new int[1]),
  size(1)

{
  *a = i;
}

int IntArray::get(size_t id) const noexcept {
  return a[id];
}

size_t IntArray::getSize() const noexcept {
  return size;
}

int IntArray::last() const noexcept {
  return get(getSize() - 1);
}

void IntArray::add(int i) {
  int* tmp = new int[getSize() + 1];
  for (size_t j = 0; j < getSize(); ++j) {
    tmp[j] = get(j);
  }
  tmp[getSize()] = i;
  delete[] a;
  a = tmp;
  ++size;
}

IntArray::IntArray (const IntArray & rhs) :
  a(new int [rhs.getSize()]),
  size(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); ++i)
  {
    a[i] = rhs.get(i);
  }
}

IntArray & IntArray::operator=(const IntArray & rhs)
{
  int * tmp = new int [rhs.getSize()];
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    tmp[i] = rhs.get(i);
  }
  delete[] a;
  a = tmp;
  size = rhs.getSize();
  return *this; //то, что слева
}

IntArray::IntArray (IntArray && rhs):
a(rhs.a),
size(rhs.getSize())
{
  rhs.a = nullptr;
}

//IntArray c (std::move(b)) перемещение
//IntArray p (a) копирование

IntArray & IntArray::operator=(IntArray && rhs)
{
  delete[] a;
  a = rhs.a;
  size = rhs.size;
  rhs.a = nullptr;
  return * this;
}

IntMatrix::IntMatrix(size_t rows, size_t cols) :
  matrix(new IntArray[rows]),
  rows(rows),
  cols(cols)
  {}

IntMatrix::~IntMatrix() {
  delete[] matrix;
}