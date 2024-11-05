#ifndef ALGORITMS_O_H
#define ALGORITMS_O_H

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  while (1 < end - begin) {
    if (value < *(begin + (end - begin) / 2)) {
      end -= (end - begin) / 2;
    } else {
      begin += (end - begin) / 2;
    }
  }
  if (!(*begin < value) && !(value < *begin)) {
    return true;
  }
  return false;
}

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  int size = end - begin;
  const T* it;
  while (size) {
    it = begin;
    int step = size / 2;
    it += step;
    if (*it < value) {
      begin = ++it;
      size -= step + 1;
    } else {
      size = step;
    }
  }
  return begin;
}

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  int size = end - begin;
  const T* it;
  while (size) {
    it = begin;
    int step = size / 2;
    it += step;
    if (value < *it) {
      size = step;
    } else {
      begin = ++it;
      size -= step + 1;
    }
  }
  return begin;
}
#endif
