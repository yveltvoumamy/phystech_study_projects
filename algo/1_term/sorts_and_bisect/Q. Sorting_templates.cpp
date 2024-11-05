#ifndef ALGORITMS_Q_H
#define ALGORITMS_Q_H

#include <cstdlib>

template <class T>
void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <class T>
void Partition(T* arr, long pivot_idx, long left, long right, long& left_eq, long& right_eq) {
  Swap(arr[left], arr[pivot_idx]);
  left_eq = left;
  right_eq = left_eq + 1;
  while (right_eq < right) {
    if (arr[left_eq] < arr[right_eq]) {
      Swap(arr[right_eq], arr[--right]);
    } else if (arr[right_eq] < arr[left_eq]) {
      Swap(arr[right_eq++], arr[left_eq++]);
    } else {
      ++right_eq;
    }
  }
}

template <class T>
void QuickSort(T* arr, long left, long right) {
  if (right - left < 2) {
    return;
  }
  long left_eq, right_eq;
  Partition(arr, left + rand() % (right - left), left, right, left_eq, right_eq);
  QuickSort(arr, left, left_eq);
  QuickSort(arr, right_eq, right);
}

template <class T>
void Sort(T* begin, T* end) {
  QuickSort(begin, 0, end - begin);
}
#endif