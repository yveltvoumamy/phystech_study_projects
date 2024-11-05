#include <iostream>
#include <queue>

void FastInputOutput();
void Input(std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>>& queue);
void Solution(std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>>& queue);

int main() {
  FastInputOutput();
  std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>> queue;
  Input(queue);
  Solution(queue);
}

void Solution(std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>>& queue) {
  int32_t st, other;
  double result = 0.0;
  for (int j = 0; !queue.empty(); j++) {
    st = queue.top();
    queue.pop();
    if (!queue.empty()) {
      other = queue.top();
      queue.pop();
      result += (st + other) * 0.05;
      queue.push(st + other);
    }
  }
  std::cout << result;
}

void Input(std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>>& queue) {
  int32_t n;
  std::cin >> n;
  int32_t number;
  int32_t i = 0;
  while (i < n) {
    std::cin >> number;
    queue.push(number);
    i++;
  }
}

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}