#include <iostream>
void CreateBoard(int** board, int n);
void DeleteBoard(int** board, int n);
void GetQueen(int** board, int n, int line, int& counter);
bool CheckQueen(int** board, int n, int line, int column);

int main() {
  int n;
  std::cin >> n;
  auto board = new int*[n];
  CreateBoard(board, n);
  int counter = 0;
  GetQueen(board, n, 0, counter);
  DeleteBoard(board, n);
  std::cout << counter;
}

void GetQueen(int** board, int n, int line, int& counter) {
  int queen_place = 9;
  if (line == n) {
    ++counter;
  }
  for (int i = 0; i < n; ++i) {
    if (CheckQueen(board, n, line, i)) {
      board[line][i] = queen_place;

      GetQueen(board, n, line + 1, counter);

      board[line][i] = 0;
    }
  }
}

bool CheckQueen(int** board, int n, int line, int column) {
  int queen_place = 9;
  for (int i = 0; i < line; ++i) {
    if (board[i][column] == queen_place) {
      return false;
    }
  }
  for (int i = 1; line - i >= 0 && column + i < n; ++i) {
    if (board[line - i][column + i] == queen_place) {
      return false;
    }
  }
  for (int i = 1; line - i >= 0 && column - i >= 0; ++i) {
    if (board[line - i][column - i] == queen_place) {
      return false;
    }
  }
  return true;
}

void CreateBoard(int** board, int n) {
  for (int i = 0; i < n; ++i) {
    board[i] = new int[n]{};
  }
}

void DeleteBoard(int** board, int n) {
  for (int i = 0; i < n; ++i) {
    delete[] board[i];
  }
  delete[] board;
}