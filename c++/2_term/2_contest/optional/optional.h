#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <exception>

class BadOptionalAccess : public std::runtime_error {
 public:
  BadOptionalAccess() : std::runtime_error("BadOptionalAccess") {
  }
};

template <typename T>
class Optional {
 private:
  char value_[sizeof(T)];
  bool has_value_ = false;

  const T& Get() const {
    return *reinterpret_cast<const T*>(value_);
  }

  T& Get() {
    return *reinterpret_cast<T*>(value_);
  }

 public:
  Optional() = default;
  Optional(const Optional& other) {
    if (!other.has_value_) {
      has_value_ = false;
      return;
    }
    new (value_) T(other.Get());
    has_value_ = true;
  }
  Optional(Optional&& other) {
    if (!other.has_value_) {
      has_value_ = false;
      return;
    }
    new (value_) T(std::move(other.Get()));
    has_value_ = true;
  }
  Optional operator=(const Optional& other) {
    if (this == &other) {
      return *this;
    }
    if (!other.has_value_) {
      if (has_value_) {
        has_value_ = false;
        Get().~T();
      }
      return *this;
    }
    if (has_value_) {
      Get().~T();
    }
    new (value_) T(other.Get());
    has_value_ = true;
    return *this;
  }
  Optional& operator=(Optional&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (!other.has_value_) {
      if (has_value_) {
        has_value_ = false;
        Get().~T();
      }
      return *this;
    }
    if (has_value_) {
      Get() = std::move(other.Get());
      return *this;
    }
    new (value_) T(std::move(other.Get()));
    has_value_ = true;
    return *this;
  }
  explicit Optional(const T& other) {
    new (value_) T(other);
    has_value_ = true;
  }
  explicit Optional(T&& other) noexcept {
    new (value_) T(std::move(other));
    has_value_ = true;
  }
  Optional& operator=(const T& other) {
    if (!has_value_) {
      new (value_) T(other);
      has_value_ = true;
    } else {
      Get().~T();
      new (value_) T(other);
    }
    return *this;
  }
  Optional& operator=(T&& other) noexcept {
    if (!has_value_) {
      new (value_) T(std::move(other));
      has_value_ = true;
    } else {
      Get() = std::move(other);
    }
    return *this;
  }
  ~Optional() {
    if (has_value_) {
      Get().~T();
    }
  }
  T& Value() {
    if (!has_value_) {
      throw BadOptionalAccess{};
    }
    return *reinterpret_cast<T*>(value_);
  }
  T Value() const {
    if (!has_value_) {
      throw BadOptionalAccess{};
    }
    return *reinterpret_cast<const T*>(value_);
  }
  bool HasValue() const {
    return has_value_;
  }
  explicit operator bool() const {
    return has_value_;
  }
  T& operator*() {
    return *reinterpret_cast<T*>(value_);
  }
  T operator*() const {
    return *reinterpret_cast<const T*>(value_);
  }
  void Reset() {
    if (has_value_) {
      Get().~T();
    }
    has_value_ = false;
  }
  template <typename... Args>
  void Emplace(Args&&... args) {
    if (has_value_) {
      Get().~T();
    }
    new (value_) T(std::forward<Args>(args)...);
    has_value_ = true;
  }
  void Swap(Optional& other) {
    std::swap(*this, other);
  }
};
#endif