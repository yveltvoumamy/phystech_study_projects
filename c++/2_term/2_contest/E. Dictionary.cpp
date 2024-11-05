#include <iostream>
#include <unordered_map>

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  FastInputOutput();
  int n;
  std::cin >> n;
  std::string first_word, second_word;
  std::unordered_map<std::string, std::string> array(n * 2 + 1);
  for (int32_t i = 1; i <= n; ++i) {
    std::cin >> first_word >> second_word;
    array[second_word] = first_word;
    array[first_word] = second_word;
  }
  int32_t quest;
  std::cin >> quest;
  int32_t i = 0;
  while (i < quest) {
    std::cin >> first_word;
    std::cout << array[first_word] << std::endl;
    ++i;
  }
}