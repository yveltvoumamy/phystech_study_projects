#include <iostream>

void Erase(int n);
void Draw(int n);

int main() {
  int n;
  std::cin >> n;
  Draw(n);
  return 0;
}

void Draw(int n) {
  if (n <= 2) {
    if (n == 2) {
      std::cout << "1 2 ";
    } else if (n == 1) {
      std::cout << "1 ";
    }
    return;
  }
  Draw(n - 1);
  Erase(n - 2);
  std::cout << n << ' ';
  Draw(n - 2);
}

void Erase(int n) {
  if (n <= 2) {
    if (n == 2) {
      std::cout << "-2 -1 ";
    } else if (n == 1) {
      std::cout << "-1 ";
    }
    return;
  }
  Erase(n - 2);
  std::cout << '-' << n << ' ';
  Draw(n - 2);
  Erase(n - 1);
}