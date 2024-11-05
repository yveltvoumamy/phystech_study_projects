#pragma once
#include <algorithm>
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
template <typename T>
class UniquePtr {
public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T *ptr) : ptr_(ptr) {
  }
  UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }
  UniquePtr(const UniquePtr &pointer) = delete;
  UniquePtr &operator=(const UniquePtr &pointer) = delete;
  UniquePtr &operator=(UniquePtr &&r_value) noexcept {
    if (this == &r_value) {
      return (*this);
    }
    delete ptr_;
    ptr_ = r_value.ptr_;
    r_value.ptr_ = nullptr;
    return (*this);
  }
  ~UniquePtr() {
    delete ptr_;
  }
  T &operator*() const {
    return *ptr_;
  }
  T *operator->() const {
    return ptr_;
  }
  T *Get() const {
    return ptr_;
  }
  void Reset(T *ptr = nullptr) {
    T *buff = ptr_;
    ptr_ = ptr;
    delete buff;
  }
  T *Release() {
    T *buff = ptr_;
    ptr_ = nullptr;
    return buff;
  }
  void Swap(UniquePtr<T> &unique_ptr) {
    T *arr = std::move(unique_ptr.ptr_);
    unique_ptr.ptr_ = std::move(ptr_);
    ptr_ = std::move(arr);
  }
  explicit operator bool() const noexcept {
    return (ptr_ != nullptr);
  }

private:
  T *ptr_;
};

#endif