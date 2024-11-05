#include <iostream>

void InputTwoDimensionalCharArray(char** arr, int lines, int columns);
void DeleteTwoDimensionalCharArray(char** arr, int lines);
void CheckCopybook(char** copybook, int lines, int columns);
void CheckColumns(char** copybook, int start, int lines, int columns, int& count_columns, int& distance);
void CheckLines(char** copybook, int start, int lines, int columns, int& count_lines, int& distance);
void CheckDistanceBetweenLines(char** copybook, int start, int n, int& distance);
void CheckDistanceBetweenColumns(char** copybook, int start, int n, int& distance);
void GetAnswer(int lines, int columns, int count_lines, int count_columns, int distance);

int main() {
  int n;
  int m;
  std::cin >> n;
  std::cin >> m;
  auto copybook = new char*[n];
  for (int i = 0; i < n; ++i) {
    copybook[i] = new char[m];
  }
  InputTwoDimensionalCharArray(copybook, n, m);
  CheckCopybook(copybook, n, m);
  DeleteTwoDimensionalCharArray(copybook, n);
  return 0;
}

void CheckCopybook(char** copybook, int lines, int columns) {
  int count_columns = 0;
  int count_lines = 0;
  int distance = 0;
  CheckColumns(copybook, 0, lines, columns, count_columns, distance);
  CheckLines(copybook, 0, lines, columns, count_lines, distance);
  GetAnswer(lines, columns, count_lines, count_columns, distance);
}

void GetAnswer(int lines, int columns, int count_lines, int count_columns, int distance) {
  if (count_lines > 0 && count_columns > 0) {
    std::cout << "Square";
  } else if (count_columns > 1 && count_lines == 0) {
    if (distance < lines) {
      std::cout << "Vertical line";
    } else {
      std::cout << "?";
    }
  } else if (count_lines > 1 && count_columns == 0) {
    if (distance < columns) {
      std::cout << "Line";
    } else {
      std::cout << "?";
    }
  } else {
    std::cout << "?";
  }
}

void CheckColumns(char** copybook, int start, int lines, int columns, int& count_columns, int& distance) {
  int sum = 0;
  for (int i = 0; i < columns; ++i) {
    if (copybook[start][i] == '1') {
      ++sum;
    }
  }
  if (sum != columns) {
    count_columns = sum;
    if (count_columns > 0) {
      CheckDistanceBetweenColumns(copybook, start, columns, distance);
    }
  } else {
    if (start + 1 < lines) {
      CheckColumns(copybook, start + 1, lines, columns, count_columns, distance);
    }
  }
}

void CheckDistanceBetweenLines(char** copybook, int start, int n, int& distance) {
  for (int i = 0; i < n; ++i) {
    if (copybook[i][start] == '1') {
      if (distance) {
        break;
      }
      ++distance;
    }
    if (distance) {
      ++distance;
    }
  }
}

void CheckDistanceBetweenColumns(char** copybook, int start, int n, int& distance) {
  for (int i = 0; i < n; ++i) {
    if (copybook[start][i] == '1') {
      if (distance) {
        break;
      }
      ++distance;
    }
    if (distance) {
      ++distance;
    }
  }
}

void CheckLines(char** copybook, int start, int lines, int columns, int& count_lines, int& distance) {
  int sum = 0;
  for (int i = 0; i < lines; ++i) {
    if (copybook[i][start] == '1') {
      ++sum;
    }
  }
  if (sum != lines) {
    if (count_lines != 0) {
      CheckDistanceBetweenLines(copybook, start, lines, distance);
    }
    count_lines = sum;
  } else if (start + 1 < columns) {
    CheckLines(copybook, start + 1, lines, columns, count_lines, distance);
  }
}

void InputTwoDimensionalCharArray(char** arr, int lines, int columns) {
  for (int i = 0; i < lines; ++i) {
    for (int j = 0; j < columns; ++j) {
      std::cin >> arr[i][j];
    }
  }
}

void DeleteTwoDimensionalCharArray(char** arr, int lines) {
  for (int i = 0; i < lines; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}