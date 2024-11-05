#include <iostream>
#include <cstring>

void Decoder(char* code_word, int len_code_word, char* word);
void OutputString(char* string, int n);
int main() {
  char code_word[100001] = {};
  char word[100001] = {};
  std::cin.getline(code_word, 100001);
  int n = strlen(code_word);
  --n;
  Decoder(code_word, n, word);
  OutputString(word, n);
}

void Decoder(char* code_word, int len_code_word, char* word) {
  int j = 0;
  for (int i = 0; i < len_code_word; i += 2) {
    word[j++] = code_word[i];
  }
  if (len_code_word % 2 == 0) {
    len_code_word -= 1;
  } else {
    len_code_word -= 2;
  }
  for (int i = len_code_word; i >= 0; i -= 2) {
    word[j++] = code_word[i];
  }
}

void OutputString(char* string, int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << string[i];
  }
}