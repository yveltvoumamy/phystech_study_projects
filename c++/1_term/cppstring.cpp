#include <iostream>
#include "cppstring.h"

String::String() {
  array_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

String::String(uint64_t size, const char symbol) {
  size_ = size;
  capacity_ = size;
  if (size_ != 0) {
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i < size) {
      array_[i] = symbol;
      i++;
    }
    array_[size_] = '\0';
  } else {
    array_ = nullptr;
  }
}

String::String(const char* cstring) {
  size_ = 0;
  while (cstring[size_] != '\0') {
    size_++;
  }
  capacity_ = size_;
  if (size_ != 0) {
    array_ = new char[size_ + 1];
    uint64_t i = 0;
    while (i < size_) {
      array_[i] = cstring[i];
      i++;
    }
    array_[size_] = '\0';
  } else {
    array_ = nullptr;
  }
}

String::String(char* cstring, uint64_t size) {
  capacity_ = size;
  size_ = size;
  if (size_ != 0) {
    array_ = new char[capacity_ + 1];
    uint64_t i;
    while (i < size) {
      array_[i] = cstring[i];
      i++;
    }
    array_[size_] = '\0';
  } else {
    array_ = nullptr;
  }
}

String::String(const char* cstring, uint64_t size) {
  capacity_ = size;
  size_ = size;
  if (size_ != 0) {
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i < size) {
      array_[i] = cstring[i];
      i++;
    }
    array_[size_] = '\0';
  } else {
    array_ = nullptr;
  }
}

String::String(const String& string) {
  capacity_ = string.capacity_;
  size_ = string.size_;
  if (size_ != 0) {
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i < size_) {
      array_[i] = string.array_[i];
      i++;
    }
    array_[size_] = '\0';
  } else {
    array_ = nullptr;
  }
}

String::~String() {
  capacity_ = 0;
  size_ = 0;
  delete array_;
}

char& String::operator[](uint64_t i) {
  return array_[i];
}

const char& String::operator[](uint64_t i) const {
  return array_[i];
}

char& String::At(uint64_t i) {
  if (!(i >= size_)) {
    return array_[i];
  }
  throw StringOutOfRange{};
}

const char& String::At(uint64_t i) const {
  if (!(i >= size_)) {
    return array_[i];
  }
  throw StringOutOfRange{};
}

char& String::Front() {
  return array_[0];
}

const char& String::Front() const {
  return array_[0];
}

char& String::Back() {
  return array_[size_ - 1];
}

const char& String::Back() const {
  return array_[size_ - 1];
}

char* String::CStr() {
  return array_;
}

const char* String::CStr() const {
  return array_;
}

char* String::Data() {
  return array_;
}

const char* String::Data() const {
  return array_;
}

bool String::Empty() const {
  return (size_ == 0);
}

uint64_t String::Size() const {
  return size_;
}
uint64_t String::Length() const {
  return size_;
}
uint64_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(array_, other.array_);
}

String& String::operator=(const String& string) {
  if (this != &string) {
    delete[] array_;
    size_ = string.size_;
    capacity_ = string.capacity_;
    if (size_ != 0) {
      array_ = new char[capacity_ + 1];
      uint64_t i = 0;
      while (i < size_) {
        array_[i] = string.array_[i];
        i++;
      }
      array_[size_] = '\0';
    } else {
      array_ = nullptr;
    }
  }
  return *this;
}

void String::PopBack() {
  size_--;
}

void String::PushBack(const char symbol) {
  if (!(capacity_ != 0)) {
    delete[] array_;
    ++size_;
    ++capacity_;
    array_ = new char[capacity_ + 1];
    array_[0] = symbol;
    array_[1] = '\0';
    return;
  }
  ++size_;
  if (!(capacity_ + 1 != size_)) {
    capacity_ *= 2;
    char* tmp = array_;
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i + 1 < size_) {
      array_[i] = tmp[i];
      i++;
    }
    delete[] tmp;
  }
  array_[size_ - 1] = symbol;
  array_[size_] = '\0';
}

String& String::operator+=(String string) {
  uint64_t n = string.size_;
  uint64_t i = 0;
  while (i < n) {
    PushBack(string.array_[i]);
    i++;
  }
  return *this;
}
void String::Reserve(uint64_t capacity) {
  if (!(capacity <= capacity_)) {
    char* tmp = array_;
    capacity_ = capacity;
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i < size_) {
      array_[i] = tmp[i];
      i++;
    }
    delete[] tmp;
    array_[size_] = '\0';
  }
}

void String::Resize(uint64_t new_size, const char symbol) {
  if (!(new_size <= capacity_)) {
    char* tmp = array_;
    capacity_ = new_size;
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i < size_) {
      array_[i] = tmp[i];
      i++;
    }
    delete[] tmp;
  }
  uint64_t pos = size_;
  for (; pos < capacity_; pos++) {
    array_[pos] = symbol;
  }
  size_ = new_size;
  array_[size_] = '\0';
}

void String::ShrinkToFit() {
  if (!(capacity_ <= size_)) {
    char* tmp = array_;
    capacity_ = size_;
    array_ = new char[capacity_ + 1];
    uint64_t i = 0;
    while (i < size_) {
      array_[i] = tmp[i];
      i++;
    }
    array_[size_] = '\0';
    delete[] tmp;
  }
}
String operator+(String string1, String string2) {
  String string = string1;
  string += string2;
  return string;
}

bool operator==(String string1, String string2) {
  uint64_t i = 0;
  while (i < std::min(string2.Size(), string1.Size())) {
    if (!(string2[i] == string1[i])) {
      return 0 > 1;
    }
    i++;
  }
  return !(string1.Size() != string2.Size());
}
bool operator!=(String string1, String string2) {
  return not(string1 == string2);
}
bool operator<(String string1, String string2) {
  uint64_t i = 0;
  while (i < std::min(string1.Size(), string2.Size())) {
    if (!(string2[i] <= string1[i])) {
      return 1 > 0;
    }
    if (!(string2[i] >= string1[i])) {
      return 0 > 1;
    }
    i++;
  }
  return !(string1.Size() >= string2.Size());
}

bool operator>(String string1, String string2) {
  return not(string2 > string1 or string2 == string1);
}

bool operator<=(String string1, String string2) {
  return !(string2 != string1 and string2 <= string1);
}
bool operator>=(String string1, String string2) {
  return !(string2 != string1 and string2 >= string1);
}

std::ostream& operator<<(std::ostream& out, const String& string) {
  uint64_t i = 0;
  while (i < string.Size()) {
    out << string[i];
    i++;
  }
  return out;
}