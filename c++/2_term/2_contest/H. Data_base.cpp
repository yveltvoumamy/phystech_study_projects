#include <iostream>
#include <map>

void FastInputOutput();

int main() {
  FastInputOutput();
  std::string process, result;
  uint32_t count;
  std::map<std::string, std::map<std::string, uint64_t>> array;
  while (std::cin >> process >> result >> count) {
    array[process][result] += count;
  }
  for (auto q : array) {
    std::cout << q.first << ':' << "\n";
    std::map<std::string, uint64_t> products = q.second;
    for (auto p : products) {
      std::cout << p.first << ' ' << p.second << "\n";
    }
  }
}

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}
