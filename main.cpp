#include <iostream>

struct IntArray {
    int* a;
    size_t k;
    void add(int i);
    int get(size_t id) const noexcept;
    size_t size() const noexcept;
    int last() const noexcept;
    IntArray(int i);
    ~IntArray();
};

IntArray::~IntArray() {
    delete[] a;
}

IntArray::IntArray(int i) :
    a(new int[1]),
    k(1)

{
    *a = i;
}

int IntArray::get(size_t id) const noexcept {
    return a[id];
}

size_t IntArray::size() const noexcept {
    return k;
}

int IntArray::last() const noexcept {
    return get(size() - 1);
}

void IntArray::add(int i) {
    int* tmp = new int[size() + 1];
    for (size_t i = 0; i < size(); ++i) {
        tmp[i] = get(i);
    }
    delete[] a;
    a = tmp;
    ++k;
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
        if (std::cin.fail() && !(std::cin.eof())) {
            return 1;
        }
        size_t count = 1;

        for (size_t i = 0; i < a.size() - 1; ++i) {
            int d = a.get(i);
            // std::cout << d;
            count += !(d % a.last());
        }
        std::cout << count << "\n";
        return 0;
    }
    catch (const std::bad_alloc()) {
        return 2;
    }
}