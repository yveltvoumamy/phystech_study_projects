#include <iostream>

void LifeInTheSquare(int** rectangle, int size, int t, int** check);
void Turn(int** rectangle, int size, int** check);
void CheckNeighbors(int** rectangle, int line, int column, int** check);
void CreateNullTwoDimensionalArray(int** array, int size);
void InputTwoDimensionalArrayWithZeroBounds(int** array, int size);
void OutputTwoDimensionalArrayWithoutZeroBounds(int** array, int size);
void DeleteTwoDimensionalArray(int** array, int size);

int main() {
  int n;
  int t;
  int** check;
  std::cin >> n;
  std::cin >> t;
  auto rectangle = new int*[n + 2];
  check = new int*[n + 2];
  CreateNullTwoDimensionalArray(rectangle, n + 2);
  CreateNullTwoDimensionalArray(check, n + 2);
  InputTwoDimensionalArrayWithZeroBounds(rectangle, n + 2);
  LifeInTheSquare(rectangle, n + 2, t, check);
  OutputTwoDimensionalArrayWithoutZeroBounds(rectangle, n + 2);
  DeleteTwoDimensionalArray(rectangle, n + 2);
  DeleteTwoDimensionalArray(check, n + 2);
  return 0;
}

void DeleteTwoDimensionalArray(int** array, int size) {
  for (int i = 0; i < size; ++i) {
    delete[] array[i];
  }
  delete[] array;
}

void LifeInTheSquare(int** rectangle, int size, int t, int** check) {
  for (int i = 0; i < t; ++i) {
    Turn(rectangle, size, check);
  }
}

void OutputTwoDimensionalArrayWithoutZeroBounds(int** array, int size) {
  for (int i = 1; i < size - 1; ++i) {
    for (int j = 1; j < size - 1; ++j) {
      std::cout << array[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void InputTwoDimensionalArrayWithZeroBounds(int** array, int size) {
  for (int i = 1; i < size - 1; ++i) {
    for (int j = 1; j < size - 1; ++j) {
      std::cin >> array[i][j];
    }
  }
}

void CreateNullTwoDimensionalArray(int** array, int size) {
  for (int i = 0; i < size; ++i) {
    array[i] = new int[size]{};
  }
}
void CheckNeighbors(int** rectangle, int line, int column, int** check) {
  int neighbors;
  int two_neighbors = 2;
  int three_neighbors = 3;
  neighbors = rectangle[line + 1][column] + rectangle[line - 1][column] + rectangle[line][column + 1] +
              rectangle[line][column - 1] + rectangle[line + 1][column + 1] + rectangle[line - 1][column - 1] +
              rectangle[line - 1][column + 1] + rectangle[line + 1][column - 1];
  // std::cout << "ok " << line << column << '\n';
  if (rectangle[line][column] == 0) {
    if (neighbors == three_neighbors) {
      check[line][column] = 1;
    } else {
      check[line][column] = 0;
    }
  } else {
    if (neighbors < two_neighbors) {
      check[line][column] = 0;
    } else if (neighbors > three_neighbors) {
      check[line][column] = 0;
    } else {
      check[line][column] = 1;
    }
  }
}

void Turn(int** rectangle, int size, int** check) {
  for (int i = 1; i < size - 1; ++i) {
    for (int j = 1; j < size - 1; ++j) {
      CheckNeighbors(rectangle, i, j, check);
    }
  }
  for (int i = 1; i < size - 1; ++i) {
    for (int j = 1; j < size - 1; ++j) {
      rectangle[i][j] = check[i][j];
    }
  }
}