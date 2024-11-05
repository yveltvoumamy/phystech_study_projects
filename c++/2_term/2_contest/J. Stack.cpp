#ifndef STACK
#define STACK
#include <iostream>
#include <queue>

template <typename T, typename Container = std::deque<T>>
class Stack {
public:
  Container container_;
  size_t size_;
  Stack() = default;
  explicit Stack(const Container& data) {  // NOLINT
    size_ = Container(data.begin(), data.end()).size();
    container_ = Container(data.begin(), data.end());
  }
  template <class Iterator>
  Stack(Iterator begin, Iterator end) {
    size_ = Container(begin, end).size();
    container_ = Container(begin, end);
  }
  const T& Top() const {
    return container_.back();
  }
  T& Top() {
    return container_.back();
  }
  bool Empty() const {
    return container_.empty();
  }
  uint64_t Size() const {
    return container_.size();
  }
  void Push(T&& value) {
    size_++;
    container_.push_back(std::move(value));
  }
  void Push(const T& value) {
    size_++;
    container_.push_back(value);
  }
  template <typename... Args>
  void Emplace(Args&&... args) {
    container_.emplace_back(std::forward<Args>(args)...);
  }
  void Pop() {
    if (size_ != 0) {
      size_--;
      container_.pop_back();
    }
  }
  void Clear() {
    while (!container_.empty()) {
      this->Pop();
    }
  }
  void Swap(Stack& other) {
    std::swap(size_, other.size_);
    std::swap(container_, other.container_);
  }
};

#endif