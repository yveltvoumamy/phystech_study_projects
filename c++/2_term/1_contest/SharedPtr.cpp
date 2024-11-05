#include <iostream>
#ifndef SHAREDPTR
#define SHAREDPTR
template <class T>
class SharedPtr {
private:
  T *ptr_ = nullptr;
  int *strong_counter_ = nullptr;

public:
  inline SharedPtr() {
    ptr_ = nullptr;
    strong_counter_ = new int(1);
  }
  inline SharedPtr(T *ptr) noexcept {  // NOLINT
    ptr_ = ptr;
    strong_counter_ = new int(1);
  }
  inline SharedPtr(const SharedPtr &ptr) noexcept {
    if (ptr.strong_counter_ != nullptr) {
      *ptr.strong_counter_ += 1;
    }
    strong_counter_ = ptr.strong_counter_;
    ptr_ = ptr.ptr_;
  }
  inline SharedPtr<T> &operator=(const SharedPtr &ptr) {
    if (this == &ptr) {
      return *this;
    }
    *strong_counter_ -= 1;
    if (*strong_counter_ == 0) {
      delete strong_counter_;
      delete ptr_;
    }
    ptr_ = ptr.ptr_;
    if (ptr.strong_counter_ != nullptr) {
      *ptr.strong_counter_ += 1;
    }
    strong_counter_ = ptr.strong_counter_;
    return *this;
  }
  inline SharedPtr(SharedPtr<T> &&ptr) noexcept {
    ptr_ = ptr.ptr_;
    strong_counter_ = ptr.strong_counter_;
    ptr.ptr_ = nullptr;
    ptr.strong_counter_ = nullptr;
  }
  inline SharedPtr<T> &operator=(SharedPtr<T> &&ptr) noexcept {
    if (this == &ptr) {
      return *this;
    }
    *strong_counter_ -= 1;
    if (*strong_counter_ == 0) {
      delete strong_counter_;
      delete ptr_;
    }
    ptr_ = ptr.ptr_;
    strong_counter_ = ptr.strong_counter_;
    ptr.ptr_ = nullptr;
    ptr.strong_counter_ = nullptr;
    return *this;
  }
  inline void Reset(T *ptr = nullptr) {
    *strong_counter_ -= 1;
    if (*strong_counter_ == 0) {
      delete strong_counter_;
      delete ptr_;
    }
    ptr_ = ptr;
    strong_counter_ = new int(1);
  }
  inline void Swap(SharedPtr<T> &ptr) noexcept {
    T *tmp_ptr = ptr.ptr_;
    int *tmp_counter = ptr.strong_counter_;
    ptr.ptr_ = ptr_;
    ptr.strong_counter_ = strong_counter_;
    ptr_ = tmp_ptr;
    strong_counter_ = tmp_counter;
  }
  inline T *Get() const {
    return ptr_;
  }
  inline int UseCount() const {
    if (ptr_ == nullptr) {
      return 0;
    }
    return *strong_counter_;
  }
  inline T &operator*() const {
    return *ptr_;
  }
  inline T *operator->() const {
    return ptr_;
  }
  inline explicit operator bool() const {
    return ptr_;
  }
  inline void Clear() {
    if (strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        ptr_ = nullptr;
        *strong_counter_ -= 1;
        strong_counter_ = nullptr;
      }
    }
  }
  inline ~SharedPtr() {
    Clear();
  }
};
#endif