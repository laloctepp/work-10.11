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
  // IntMatrix(const IntMatrix & rhs); //конструктор копирования
  // IntMatrix & operator=(const IntMatrix & rhs); //оператор копирующего присваивания
  // IntMatrix (IntMatrix && rhs);
  // IntMatrix & operator=(IntMatrix && rhs);
  void command2(std::istream& in);
  void command3(std::istream& in);
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

//создать матрицу в которой на rows элементов больше чем в исходной матрице
//перенести туда все элементы пропустив нужный столбец
//в тот столбец занести необходимые элементы

void remove (int ** m, size_t rows)
{
	for (size_t i=0; i < rows; ++i) {
		delete[] m[i];
	}
	delete[] m;
}

void IntMatrix::command2 (std::istream& in) {
  size_t colNum = 0;
  int elem = 0;
  int ** tmp = nullptr;
  in >> colNum >> elem;
  if (in.fail() && !in.eof()) {
    throw std::invalid_argument("Wrong input");
  }
  if (colNum > cols) {
    throw std::invalid_argument("Wrong column");
  }
  try {
    size_t ii = 0;
    tmp = new int * [rows];
    for (; ii < rows; ++ii) {
      tmp[ii] = new int[cols + 1];
    }
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < colNum; ++j) {
        tmp[i][j] = matrix[i].get(j);
      }
      tmp[i][colNum] = elem;
      for (size_t j = colNum; j < cols; ++j) {
        tmp[i][j+1] = matrix[i].get(j);
      }
    }
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i].a;       
        matrix[i].a = tmp[i];        
        matrix[i].k = cols + 1;
    }
    delete[] tmp;
    ++cols;
  }
  catch (std::bad_alloc&) {
    remove (tmp, ii);
    throw std::runtime_error("Not enough memory");
  }
}

