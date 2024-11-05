#ifndef ALGORITMS_S_H
#define ALGORITMS_S_H

template <typename T>
void PushHeap(T* begin, T* end) {
  T* element = end - 1;
  T* parent = begin + (end - begin - 2) / 2;
  for (; (begin < element) && (*parent < *element);) {
    T temp = *element;
    *element = *parent;
    *parent = temp;
    element = parent;
    parent = begin + (element - begin - 1) / 2;
  }
}

template <typename T>
void PopHeap(T* begin, T* end) {
  T temp = *begin;
  *begin = *(end - 1);
  *(end - 1) = temp;
  T* parent = begin;
  T* left_child = begin + 2 * (parent - begin) + 1;
  T* right_child = begin + 2 * (parent - begin) + 2;
  for (; (left_child + 1 < end) || (right_child + 1 < end);) {
    left_child = begin + 2 * (parent - begin) + 1;
    right_child = begin + 2 * (parent - begin) + 2;
    T* cell = parent;
    if ((left_child + 1 < end) && (*cell < *left_child)) {
      cell = left_child;
    }
    if ((right_child + 1 < end) && (*cell < *right_child)) {
      cell = right_child;
    }
    if (!((cell < parent) || (parent < cell))) {
      return;
    }
    temp = *parent;
    *parent = *cell;
    *cell = temp;
    parent = cell;
  }
}
#endif