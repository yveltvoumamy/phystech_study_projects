#ifndef ALGORITMS_R_H
#define ALGORITMS_R_H

template <typename T>
void KthElement(T* begin, T* kth, T* end) {
  --end;
  if (end < 1 + begin) {
    return;
  }
  T tmp;
  T* right = end;
  T* left = begin;
  T mid = *kth;
  for (; left < right;) {
    for (; *left < mid;) {
      left++;
    }
    for (; mid < *right;) {
      right--;
    }
    if (left - right < 1) {
      tmp = *left;
      *left = *right;
      *right = tmp;
      right--;
      left++;
    }
  }
  if (right < kth) {
    KthElement(left, kth, end + 1);
  }
  if (kth < left) {
    KthElement(begin, kth, right + 1);
  }
}
#endif