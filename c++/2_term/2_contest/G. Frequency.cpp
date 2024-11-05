#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

void FastInputOutput();
bool Comp(std::pair<std::string, int32_t> a, std::pair<std::string, int32_t> b);
void Output(std::vector<std::pair<std::string, int32_t>> pv);
void Solution(std::vector<std::pair<std::string, int32_t>>& pv, std::unordered_map<std::string, int32_t>& map);
void Input(std::string& id, std::unordered_map<std::string, int32_t>& map);

int main() {
  FastInputOutput();
  std::string id;
  std::unordered_map<std::string, int32_t> map;
  Input(id, map);
  std::vector<std::pair<std::string, int32_t>> pv;
  Solution(pv, map);
}

void Input(std::string& id, std::unordered_map<std::string, int32_t>& map) {
  while (std::cin >> id) {
    map[id] = map[id] + 1;
  }
}

void Solution(std::vector<std::pair<std::string, int32_t>>& pv, std::unordered_map<std::string, int32_t>& map) {
  for (std::pair<const std::string, int32_t> i : map) {
    pv.emplace_back(i);
  }
  std::sort(pv.begin(), pv.end(), Comp);
  Output(pv);
}

void Output(std::vector<std::pair<std::string, int32_t>> pv) {
  int32_t i = 0;
  while (pv.begin() + i != pv.end()) {
    std::cout << pv[i].first << '\n';
    ++i;
  }
}

bool Comp(const std::pair<std::string, int32_t> a, const std::pair<std::string, int32_t> b) {
  if (a.second == b.second) {
    return b.first > a.first;
  }
  return b.second < a.second;
}

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}