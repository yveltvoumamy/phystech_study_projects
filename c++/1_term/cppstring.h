#ifndef CPPSTRING_H
#define CPPSTRING_H
class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* array_;
  uint64_t size_;
  uint64_t capacity_;

 public:
  String();
  String(uint64_t, const char);
  String(const char*);  // NOLINT
  String(char*, uint64_t);
  String(const char*, uint64_t);
  String(const String&);
  String& operator=(const String&);
  const char& operator[](uint64_t) const;
  char& operator[](uint64_t);
  char& At(uint64_t);
  const char& At(uint64_t) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  const char* CStr() const;
  char* CStr();
  const char* Data() const;
  char* Data();
  bool Empty() const;
  uint64_t Size() const;
  uint64_t Length() const;
  uint64_t Capacity() const;
  void PopBack();
  void PushBack(const char);
  void Clear();
  void Swap(String&);
  String& operator+=(String);
  void Reserve(uint64_t);
  void Resize(uint64_t, const char);
  void ShrinkToFit();
  friend String operator+(String, String);
  friend bool operator<(String, String);
  friend bool operator>(String, String);
  friend bool operator<=(String, String);
  friend bool operator>=(String, String);
  friend bool operator==(String, String);
  friend bool operator!=(String, String);
  friend std::ostream& operator<<(std::ostream&, const String&);
  ~String();
};

#endif