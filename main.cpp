#include <iostream>
#include <fstream>

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
  void command2(std::istream& in);
  void command3(std::istream& in);
};

int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cerr << "Wrong number of arguments";
    return 1;
  }
  std::ifstream input(argv[1]);
  size_t cols = 0;
  size_t rows = 0;
  input >> rows >> cols;
  if (input.fail() && !input.eof()) {
    std::cerr << "Wrong input";
    return 1;
  }
  if (cols == 0 || rows == 0) {
    std::cerr << "Wrong matrix characteristics";
    return 1;
  }
  IntMatrix matrix(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      input >> matrix.matrix[i].a[j];
      if (input.fail() && !input.eof()) {
        std::cerr << "Wrong input";
        return 1;
      }
    }
  }
  input.close();
  size_t param = 0;
  while (std::cin >> param) {
    if (std::cin.fail() && !std::cin.eof()) {
      std::cerr << "Wrong input";
      return 1;
    }
    try {
      if (param == 2) {
        matrix.command2(std::cin); 
      }
      else if (param == 3) {
        matrix.command3(std::cin);
      }
      else {
        std::cerr << "Wrong parametr";
        return 3;
      }
      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          std::cout << matrix.matrix[i].a[j] << " ";
        }
        std::cout << "\n";
      }
    }
    catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return 3;
    }
    catch (const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    return 2;
    }
    catch (const std::out_of_range& e) {
    std::cerr << e.what() << std::endl;
    return 3;
    }
  }
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
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i].add(0);
        }
    }
}

IntMatrix::~IntMatrix() {
  delete[] matrix;
}

void remove (int ** m, size_t rows)
{
	for (size_t i=0; i < rows; ++i) {
		delete[] m[i];
	}
	delete[] m;
}

void IntMatrix::command2(std::istream& in) {
  size_t colNum = 0;
  size_t elem = 0;
  in >> colNum >> elem;
  if (in.fail() && !in.eof()) {
    throw std::invalid_argument("Wrong parametr");
  }
  if (colNum > cols) {
    throw std::out_of_range("Wrong argument");
  }
  IntArray* new_matrix = nullptr;
  try {
    new_matrix = new IntArray[rows + 1];
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols + 1; ++j) {
        new_matrix[i].add(elem);
      }
    }
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        size_t new_j = (j < colNum) ? j : j + 1;
        new_matrix[i].a[new_j] = matrix[i].get(j);
      }
    }
    delete[] matrix;
    matrix = new_matrix;
    cols++;
  }
  catch (const std::bad_alloc& e) {
    delete[] new_matrix;
    throw std::bad_alloc();
  }
}

void IntMatrix::command3(std::istream& in) {
  size_t rowNum = 0;
  size_t colNum = 0;
  in >> rowNum >> colNum;
  if (in.fail() && !in.eof()) {
    throw std::invalid_argument("Wrong parametr");
  }
  if (rowNum > rows || colNum > cols) {
    throw std::out_of_range("Wrong argument");
  }
  IntArray* new_matrix = nullptr;
  try {
    new_matrix = new IntArray[rows + 1];
    for (size_t i = 0; i < rows + 1; ++i) {
      for (size_t j = 0; j < cols + 1; ++j) {
        new_matrix[i].add(0);
      }
    }
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        size_t new_i = (i < rowNum) ? i : i + 1;
        size_t new_j = (j < colNum) ? j : j + 1;
        new_matrix[new_i].a[new_j] = matrix[i].get(j);
      }
    }
    delete[] matrix;
    matrix = new_matrix;
    rows++;
    cols++;
  }
  catch (const std::bad_alloc& e) {
    delete[] new_matrix;
    throw std::bad_alloc();
  }
}