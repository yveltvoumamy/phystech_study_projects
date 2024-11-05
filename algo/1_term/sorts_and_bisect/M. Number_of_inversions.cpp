#include <cstdint>
#include <iostream>

void Merge(int* first_begin, int* first_end, int* second_begin, int* second_end, int* result, int64_t& counter);
int* MergeSort(int* begin, int* end, int64_t& counter);
void InputArray(int* arr, int n);

int main() {
  int n;
  std::cin >> n;
  auto array = new int[n];
  int64_t counter = 0;
  InputArray(array, n);
  int* end = &array[n];
  auto sorted_array = MergeSort(array, end, counter);
  std::cout << counter;
  delete[] sorted_array;
  delete[] array;
  return 0;
}

int* MergeSort(int* begin, int* end, int64_t& counter) {
  if (end - begin == 1) {
    auto result = new int[1];
    *result = *begin;
    return result;
  }
  int* mid = begin + (end - begin) / 2;
  int* first_res = MergeSort(begin, mid, counter);
  int* second_res = MergeSort(mid, end, counter);
  auto result = new int[end - begin];
  Merge(first_res, first_res + (mid - begin), second_res, second_res + (end - mid), result, counter);
  delete[] first_res;
  delete[] second_res;
  return result;
}

void Merge(int* first_begin, int* first_end, int* second_begin, int* second_end, int* result, int64_t& counter) {
  while (first_begin != first_end && second_begin != second_end) {
    if (*first_begin <= *second_begin) {
      *result++ = *first_begin++;
    } else {
      counter += first_end - first_begin;
      *result++ = *second_begin++;
    }
  }
  while (first_begin != first_end) {
    *result++ = *first_begin++;
  }
  while (second_begin != second_end) {
    *result++ = *second_begin++;
  }
}

void InputArray(int* arr, int n) {
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
}