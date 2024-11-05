#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <stdexcept>

template <class T, size_t SIZE>
class Array {
public:
  T arr[SIZE];
  T& operator[](size_t idx);
  T& At(size_t idx);
  T& Front();
  T& Back();
  T* Data();
  size_t Size() const;
  bool Empty() const;
  void Fill(const T& value);
  void Swap(Array<T, SIZE>& other);

  const T& operator[](size_t idx) const;
  const T& At(size_t idx) const;
  const T& Front() const;
  const T& Back() const;
  const T* Data() const;
};

class ArrayOutOfRange : public std::out_of_range {
public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t SIZE>
T& Array<T, SIZE>::operator[](size_t idx) {
  return arr[idx];
}

template <class T, size_t SIZE>
T& Array<T, SIZE>::At(size_t idx) {
  if (idx < SIZE) {
    return arr[idx];
  }
  throw ArrayOutOfRange{};
}

template <class T, size_t SIZE>
T& Array<T, SIZE>::Front() {
  return *arr;
}

template <class T, size_t SIZE>
T& Array<T, SIZE>::Back() {
  return arr[SIZE - 1];
}

template <class T, size_t SIZE>
T* Array<T, SIZE>::Data() {
  return arr;
}

template <class T, size_t SIZE>
size_t Array<T, SIZE>::Size() const {
  return SIZE;
}

template <class T, size_t SIZE>
bool Array<T, SIZE>::Empty() const {
  return Size() == 0;
}

template <class T, size_t SIZE>
void Array<T, SIZE>::Fill(const T& value) {
  for (size_t i = 0; i < SIZE; ++i) {
    arr[i] = value;
  }
}

template <class T, size_t SIZE>
void Array<T, SIZE>::Swap(Array<T, SIZE>& other) {
  for (size_t i = 0; i < SIZE; ++i) {
    T tmp = arr[i];
    arr[i] = other[i];
    other[i] = tmp;
  }
}

template <class T, size_t SIZE>
const T& Array<T, SIZE>::operator[](size_t idx) const {
  return arr[idx];
}

template <class T, size_t SIZE>
const T& Array<T, SIZE>::At(size_t idx) const {
  if (idx < SIZE) {
    return arr[idx];
  }
  throw ArrayOutOfRange{};
}

template <class T, size_t SIZE>
const T& Array<T, SIZE>::Front() const {
  return *arr;
}

template <class T, size_t SIZE>
const T& Array<T, SIZE>::Back() const {
  return arr[SIZE - 1];
}

template <class T, size_t SIZE>
const T* Array<T, SIZE>::Data() const {
  return arr;
}
#endif