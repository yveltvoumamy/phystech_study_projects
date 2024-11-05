#include <iostream>
#include <map>

void FastInputOutput();
void Solution(std::map<std::string, int32_t> arr, std::string term, int32_t n);
void FirstTypeRequest(std::map<std::string, int32_t>& arr, std::string& term);
void SecondTypeRequest(std::map<std::string, int32_t>& arr, std::string& term);
void InputProcessing(std::map<std::string, int32_t>& arr, std::string term, int32_t p);

int main() {
  FastInputOutput();
  int32_t n;
  std::string term;
  std::map<std::string, int32_t> arr;
  std::cin >> n;
  Solution(arr, term, n);
}

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

void FirstTypeRequest(std::map<std::string, int32_t>& arr, std::string& term) {
  std::cin >> term;
  if (arr.count(term) == 0) {
    std::cout << "ERROR" << std::endl;
  } else {
    std::cout << arr[term] << std::endl;
  }
}

void SecondTypeRequest(std::map<std::string, int32_t>& arr, std::string& term) {
  int32_t c;
  std::cin >> term;
  std::cin >> c;
  if (arr.count(term) == 0) {
    arr[term] = 0;
    arr[term] = arr[term] + c;
  } else {
    arr[term] = arr[term] + c;
  }
}

void InputProcessing(std::map<std::string, int32_t>& arr, std::string term, int32_t p) {
  if (p != 1) {
    FirstTypeRequest(arr, term);
  } else {
    SecondTypeRequest(arr, term);
  }
}

void Solution(std::map<std::string, int32_t> arr, std::string term, int32_t n) {
  int32_t i = 0;
  int32_t p;
  while (i < n) {
    std::cin >> p;
    InputProcessing(arr, term, p);
    ++i;
  }
}