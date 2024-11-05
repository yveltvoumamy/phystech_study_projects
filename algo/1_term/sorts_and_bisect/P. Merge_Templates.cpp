//
// Created by yveltvoumamy on 06.11.2022.
//

#ifndef MERGESORT_H
#define MERGESORT_H

template <typename T, typename U, typename Y>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, Y* out) {
  while (first_begin != first_end && second_begin != second_end) {
    if (*second_begin < *first_begin) {
      *out++ = *second_begin++;
    } else {
      *out++ = *first_begin++;
    }
  }
  while (first_begin != first_end) {
    *out++ = *first_begin++;
  }
  while (second_begin != second_end) {
    *out++ = *second_begin++;
  }
}
#endif
