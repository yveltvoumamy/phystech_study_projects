#include <iostream>

void Partition(int64_t* arr, int64_t pivot_idx, int64_t left, int64_t right, int64_t& left_eq, int64_t& right_eq);
void QuickSort(int64_t* arr, int64_t left, int64_t right);
void Sort(int64_t* begin, int64_t* end);
void Swap(int64_t& a, int64_t& b);
void Input(int64_t* arr, int64_t& sum_total, int n);
bool BorderCase(int64_t* arr, int n);
void Clean(int64_t* arr);
void RotateNums(int64_t* arr, int64_t& max_count, int64_t& max_sum, int64_t& sum, int64_t& previos_right_pos,
                int64_t& previos_left_pos, int n);
void GetAnswer(int64_t* arr, int64_t& max_count, int64_t& max_sum, int64_t& sum, int64_t& previos_right_pos,
               int64_t& previos_left_pos, int64_t& elements_not_in_sum, int64_t& sum_total, int64_t& count);

int main() {
  int n;
  int64_t sum_total = 0;
  int64_t count = 2;
  int64_t sum, max_count, max_sum, previos_right_pos, previos_left_pos;
  int64_t elements_not_in_sum = 0;
  std::cin >> n;
  auto arr = new int64_t[n];
  Input(arr, sum_total, n);
  Sort(arr, arr + n);
  if (BorderCase(arr, n)) {
    Clean(arr);
    return 0;
  }
  RotateNums(arr, max_count, max_sum, sum, previos_right_pos, previos_left_pos, n);
  GetAnswer(arr, max_count, max_sum, sum, previos_right_pos, previos_left_pos, elements_not_in_sum, sum_total, count);
  std::cout << max_count << '\n' << max_sum;
  Clean(arr);
}

void GetAnswer(int64_t* arr, int64_t& max_count, int64_t& max_sum, int64_t& sum, int64_t& previos_right_pos,
               int64_t& previos_left_pos, int64_t& elements_not_in_sum, int64_t& sum_total, int64_t& count) {
  int64_t i = previos_right_pos;
  while (i > 1) {
    elements_not_in_sum += arr[i];
    sum -= arr[previos_right_pos];
    int64_t j = previos_left_pos;
    while (j >= 0) {
      if (arr[j] + arr[j + 1] < arr[i]) {
        previos_left_pos = j;
        count = i - j - 1;
        break;
      }
      sum += arr[j];
      j--;
    }
    if (sum > max_sum) {
      max_sum = sum;
      max_count = (count + 1) * count / 2;
    }
    if (max_sum + elements_not_in_sum >= sum_total) {
      break;
    }
    previos_right_pos = i;
    i--;
  }
}

void RotateNums(int64_t* arr, int64_t& max_count, int64_t& max_sum, int64_t& sum, int64_t& previos_right_pos,
                int64_t& previos_left_pos, int n) {
  max_count = 2;
  max_sum = arr[n - 1] + arr[n - 2];
  sum = max_sum + arr[n - 1];
  previos_right_pos = n - 1;
  previos_left_pos = n - 3;
}

void Clean(int64_t* arr) {
  delete[] arr;
}

bool BorderCase(int64_t* arr, int n) {
  if (n == 1) {
    std::cout << 1 << ' ' << arr[0];
    delete[] arr;
    return true;
  }
  return false;
}

void Input(int64_t* arr, int64_t& sum_total, int n) {
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
    sum_total += arr[i];
  }
}

void Swap(int64_t& a, int64_t& b) {
  int64_t tmp = a;
  a = b;
  b = tmp;
}

void Partition(int64_t* arr, int64_t pivot_idx, int64_t left, int64_t right, int64_t& left_eq, int64_t& right_eq) {
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

void QuickSort(int64_t* arr, int64_t left, int64_t right) {
  if (right - left < 2) {
    return;
  }
  int64_t left_eq, right_eq;
  Partition(arr, left + rand() % (right - left), left, right, left_eq, right_eq);
  QuickSort(arr, left, left_eq);
  QuickSort(arr, right_eq, right);
}

void Sort(int64_t* begin, int64_t* end) {
  QuickSort(begin, 0, end - begin);
}