#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstdint>

template <class T>
void Swap(T& a, T& b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

template <class T>
void SiftDown(int i, T* begin, T* end) {
  int size = end - begin;
  int left, right, j;
  while (true) {
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (right < size) {
      if (begin[left] < begin[right]) {
        j = right;
      } else {
        j = left;
      }
      if (begin[i] < begin[j]) {
        Swap(begin[i], begin[j]);
        i = j;
      } else {
        break;
      }
    } else if (left < size) {
      if (begin[i] < begin[left]) {
        Swap(begin[i], begin[left]);
        i = left;
      } else {
        break;
      }
    } else {
      break;
    }
  }
}

template <class T>
void MakeHeap(T* start, T* end) {
  int64_t sz = end - start;
  while (sz - 1 >= 0) {
    SiftDown(sz - 1, start, end);
    sz--;
  }
}

template <class T>
void SortHeap(T* begin, T* end) {
  MakeHeap(begin, end);
  int64_t size = end - begin;
  for (int i = 0; i < size; i++) {
    Swap(begin[size - 1 - i], begin[0]);
    end--;
    SiftDown(0, begin, end);
  }
}

#endif