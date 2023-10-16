#include<utility>


template <typename T>
class Array{

private:
  T* data;
   unsigned int N;

public:
  explicit Array() : data(nullptr),  N(0) {}

  explicit Array(unsigned int size, const T& value) {
    N = size;
    data = new T[N];
    for (unsigned int i = 0; i < N; ++i) {
      data[i] = value;
    }
  }

  Array(const Array& other) {
    N = other.N;
    data = new T[N];
    for (unsigned int i = 0; i < N; ++i) {
      data[i] = other.data[i];
    }
  }

  Array(const Array&& other) {
    // конструктор перемещения
    N = std::exchange(other.N, 0);  // N <- other.N <- 0
    data = std::exchange(other.data, nullptr);  // data <- other.data <- nullptr
  }

  ~Array() {
    delete[] data;
  }

  Array& operator=(const Array& other) {
    // оператор копирующего присваивания
    if(this != other) {
      N = other.N;
      delete[] data;  // освобождаем память текущего объекта, чтобы размеры совпадали
      data = new T[N];
      for (unsigned int i = 0; i < N; ++i) {
        data[i] = other.data[i];
      }
    }
    return *this;
  }

  Array& operator=(Array&& other) {
    // оператор перемещающего присваивания
    if (this != &other) {
      N = std::exchange(other.N, 0);  // N <- other.N <- 0
      delete[] data;
      data = std::exchange(other.data, nullptr);  // data <- other.data <- nullptr
      return *this;
    }
  }

  unsigned int size() const {
    return N;
  }

  T& operator[](unsigned int idx) {
    return data[idx];
  }

  const T& operator[](unsigned int idx) const {
    return data[idx];
  }
};