#include <iostream>

void Hanoi(int n, int start, int end);

int main() {
  int n;
  std::cin >> n;
  Hanoi(n, 1, 3);
  return 0;
}

void Hanoi(int n, int start, int end) {
  char space = ' ';
  char end_line = '\n';
  int no_turn = 0;
  int turn = 1;
  if (n == no_turn) {
    return;
  }
  if (n == turn) {
    std::cout << n << space << start << space << end << end_line;
    return;
  }
  Hanoi(n - 1, start, end);
  std::cout << n << space << start << space << 6 - start - end << end_line;
  Hanoi(n - 1, end, start);
  std::cout << n << space << 6 - start - end << space << end << end_line;
  Hanoi(n - 1, start, end);
}