#include <cstring>
#include <iostream>

void GetAnswer(char* str, char* val, int len);
void BinaryMe(char* val, int& j, int& firts_zero_in_val);
template <class T>
void Print(T i);
void Clean(char* str, char* val);
void FastInputOutput();

int main() {
  FastInputOutput();
  auto* str = new char[256]{};
  auto* val = new char[256]{};
  std::cin.getline(str, 256);
  auto len = static_cast<int>(strlen(str));
  GetAnswer(str, val, len);
  Clean(str, val);
}

void Clean(char* str, char* val) {
  delete[] str;
  delete[] val;
}

void GetAnswer(char* str, char* val, int len) {
  int j = 0;
  int firts_zero_in_val = -1;
  int i = 0;
  while (i < len) {
    if ((str[i] < '0' || str[i] > '9')) {
      Print(str[i]);
    } else {
      for (; (str[i] >= '0') && (str[i] <= '9') && (i < len);) {
        val[j] = str[i];
        ++j;
        ++i;
      }
      BinaryMe(val, j, firts_zero_in_val);
      if (len > i) {
        Print(str[i]);
      }
      firts_zero_in_val = -1;
      j = 0;
    }
    i++;
  }
}

void BinaryMe(char* val, int& j, int& firts_zero_in_val) {
  if ((val[j - 1] != '1') || (firts_zero_in_val + 1 != j - 1)) {
    int remainder, pre_num;
    int tmp_rem = 0;
    int not_zero_in_val = j - 1;
    int i = firts_zero_in_val + 1;
    while (i < j) {
      pre_num = val[i] - '0';
      val[i] = static_cast<char>((val[i] - '0' + tmp_rem * 10) / 2 + '0');
      if ((val[i] == '0') && (i < not_zero_in_val)) {
        firts_zero_in_val = i;
      }
      if (val[i] != '0') {
        not_zero_in_val = i;
      }
      tmp_rem = pre_num % 2;
      i++;
    }
    remainder = tmp_rem;
    BinaryMe(val, j, firts_zero_in_val);
    Print(remainder);
  } else {
    Print('1');
  }
}

template <class T>
void Print(T i) {
  std::cout << i;
}

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}