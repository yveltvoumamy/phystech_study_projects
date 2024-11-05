#include <iostream>

void InputArray(int* arr, int n);
void GetSet(int* array, int* set, int n, int& true_size);
void GetAnswer(int* first_array, int n1, int* second_array, int n2);
bool CompareSets(int* first_set, int n1, int* second_set, int n2);
void QuickSort(int* arr, int left, int right);
void Swap(int& a, int& b);
void Partition(int* arr, int pivot_idx, int left, int right, int& left_eq, int& right_eq);

int main() {
  int n1;
  int n2;

  std::cin >> n1;
  auto first_array = new int[n1];
  InputArray(first_array, n1);

  std::cin >> n2;
  auto second_array = new int[n2];
  InputArray(second_array, n2);

  GetAnswer(first_array, n1, second_array, n2);
  delete[] first_array;
  delete[] second_array;
  return 0;
}

void GetAnswer(int* first_array, int n1, int* second_array, int n2) {
  auto first_set = new int[n1]{};
  auto second_set = new int[n2]{};
  int true_size_first_set = 0;
  int true_size_second_set = 0;

  QuickSort(first_array, 0, n1);
  QuickSort(second_array, 0, n2);
  GetSet(first_array, first_set, n1, true_size_first_set);
  GetSet(second_array, second_set, n2, true_size_second_set);

  if (CompareSets(first_set, true_size_first_set, second_set, true_size_second_set)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  delete[] first_set;
  delete[] second_set;
}

bool CompareSets(int* first_set, int n1, int* second_set, int n2) {
  if (n1 != n2) {
    return false;
  }
  for (int i = 0; i < n1; ++i) {
    if (first_set[i] != second_set[i]) {
      return false;
    }
  }
  return true;
}

void GetSet(int* array, int* set, int n, int& true_size) {
  int j = 0;
  set[j++] = array[0];
  for (int i = 1; i < n; ++i) {
    if (array[i - 1] != array[i]) {
      set[j++] = array[i];
    }
  }
  true_size = j;
}

void QuickSort(int* arr, int left, int right) {
  if (right - left < 2) {
    return;
  }
  int left_eq;
  int right_eq;
  Partition(arr, left + rand() % (right - left), left, right, left_eq, right_eq);
  QuickSort(arr, left, left_eq);
  QuickSort(arr, right_eq, right);
}

void Partition(int* arr, int pivot_idx, int left, int right, int& left_eq, int& right_eq) {
  Swap(arr[left], arr[pivot_idx]);
  left_eq = left;
  right_eq = left_eq + 1;
  while (right_eq < right) {
    if (arr[right_eq] > arr[left_eq]) {
      Swap(arr[right_eq], arr[--right]);
    } else if (arr[right_eq] < arr[left_eq]) {
      Swap(arr[right_eq++], arr[left_eq++]);
    } else {
      ++right_eq;
    }
  }
}

void Swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void InputArray(int* arr, int n) {
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
}