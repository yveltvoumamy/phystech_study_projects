#include <iostream>

struct Abiturient;
void Merge(Abiturient* list, int left, int right);
void MergeSort(Abiturient* arr, int l, int r);

struct Abiturient {
  char last_name[41];
  char first_name[41];
  double average_sum = 0;
};

int main() {
  int n, first_ex, second_ex, third_ex;
  std::cin >> n;
  auto* list = new Abiturient[n];
  for (int i = 0; i < n; i++) {
    std::cin >> list[i].last_name >> list[i].first_name >> first_ex >> second_ex >> third_ex;
    list[i].average_sum = (static_cast<double>(first_ex + second_ex + third_ex)) / 3;
  }
  MergeSort(list, 0, n - 1);
  for (int i = 0; i < n; i++) {
    std::cout << list[i].last_name << ' ' << list[i].first_name << '\n';
  }
  delete[] list;
}

void Merge(Abiturient* list, int left, int right) {
  int ind_l, ind_r, ind;
  int mid = left + (right - left) / 2 + 1;
  ind_l = left;
  ind_r = mid;
  ind = 0;
  auto* list_tmp = new Abiturient[right - left + 1];
  while ((mid > ind_l) && (right >= ind_r)) {
    if (list[ind_l].average_sum >= list[ind_r].average_sum) {
      list_tmp[ind++] = list[ind_l++];
    } else {
      list_tmp[ind++] = list[ind_r++];
    }
  }
  while (mid > ind_l) {
    list_tmp[ind++] = list[ind_l++];
  }
  while (right >= ind_r) {
    list_tmp[ind++] = list[ind_r++];
  }
  ind_l = left;
  while (right >= ind_l) {
    list[ind_l] = list_tmp[ind_l - left];
    ind_l++;
  }
  delete[] list_tmp;
}

void MergeSort(Abiturient* arr, int l, int r) {
  if (l < r) {
    MergeSort(arr, l + (r - l) / 2 + 1, r);
    MergeSort(arr, l, l + (r - l) / 2);
    Merge(arr, l, r);
  }
}