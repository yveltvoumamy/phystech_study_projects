#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  Node* next = nullptr;
  int value = 0;
};

struct Deque {
  Node* end = nullptr;
  Node* begin = nullptr;
  size_t size = 0;
};

void PushFront(Deque& deque, int value);
void PushBack(Deque& deque, int value);
void PopFront(Deque& deque);
void PopBack(Deque& deque);
void Front(Deque& deque);
void Back(Deque& deque);
void Size(Deque& deque);
void Clear(Deque& deque);
void Exit(Deque& deque);
bool TargetSetting(char* command, Deque& deque, int& tmp);
int Comparison(char* command);

int main() {
  int k;
  std::cin >> k;
  Deque deque;
  int tmp;
  char command[11];
  for (int i = 0; i < k; ++i) {
    std::cin >> command;
    if (!TargetSetting(command, deque, tmp)) {
      return 0;
    }
  }
}

bool TargetSetting(char* command, Deque& deque, int& tmp) {
  switch (Comparison(command)) {
    case 1:
      std::cin >> tmp;
      PushFront(deque, tmp);
      break;
    case 2:
      std::cin >> tmp;
      PushBack(deque, tmp);
      break;
    case 3:
      PopFront(deque);
      break;
    case 4:
      PopBack(deque);
      break;
    case 5:
      Front(deque);
      break;
    case 6:
      Back(deque);
      break;
    case 7:
      Size(deque);
      break;
    case 8:
      Clear(deque);
      std::cout << "ok\n";
      break;
    case 0:
      Exit(deque);
      return false;
  }
  return true;
}

int Comparison(char* command) {
  if (strcmp(command, "push_front") == 0) {
    return 1;
  }
  if (strcmp(command, "push_back") == 0) {
    return 2;
  }
  if (strcmp(command, "pop_front") == 0) {
    return 3;
  }
  if (strcmp(command, "pop_back") == 0) {
    return 4;
  }
  if (strcmp(command, "front") == 0) {
    return 5;
  }
  if (strcmp(command, "back") == 0) {
    return 6;
  }
  if (strcmp(command, "size") == 0) {
    return 7;
  }
  if (strcmp(command, "clear") == 0) {
    return 8;
  }
  if (strcmp(command, "exit") == 0) {
    return 0;
  }
  return 404;
}

void PushFront(Deque& deque, int value) {
  auto* new_node = new Node{nullptr, nullptr, value};
  if (deque.begin == nullptr) {
    deque.end = new_node;
    deque.begin = new_node;
  } else {
    deque.begin->prev = new_node;
    new_node->next = deque.begin;
    deque.begin = new_node;
  }
  deque.size++;
  std::cout << "ok\n";
}

void PushBack(Deque& deque, int value) {
  auto* new_node = new Node{nullptr, nullptr, value};
  if (deque.end == nullptr) {
    deque.end = new_node;
    deque.begin = new_node;
  } else {
    deque.end->next = new_node;
    new_node->prev = deque.end;
    deque.end = new_node;
  }
  deque.size++;
  std::cout << "ok\n";
}

void PopFront(Deque& deque) {
  if (deque.begin == nullptr) {
    std::cout << "error\n";
  } else {
    std::cout << deque.begin->value << "\n";
    Node* tmp = deque.begin;
    deque.begin = deque.begin->next;
    if (deque.size != 1) {
      deque.begin->prev = nullptr;
    } else {
      deque.end = nullptr;
      deque.begin = nullptr;
    }
    deque.size--;
    delete tmp;
  }
}

void PopBack(Deque& deque) {
  if (deque.end == nullptr) {
    std::cout << "error\n";
  } else {
    std::cout << deque.end->value << "\n";
    Node* tmp = deque.end;
    deque.end = deque.end->prev;
    if (deque.size != 1) {
      deque.end->next = nullptr;
    } else {
      deque.begin = nullptr;
      deque.end = nullptr;
    }
    deque.size--;
    delete tmp;
  }
}

void Front(Deque& deque) {
  if (deque.begin == nullptr) {
    std::cout << "error\n";
  } else {
    std::cout << deque.begin->value << "\n";
  }
}

void Back(Deque& deque) {
  if (deque.end == nullptr) {
    std::cout << "error\n";
  } else {
    std::cout << deque.end->value << "\n";
  }
}

void Size(Deque& deque) {
  std::cout << deque.size << "\n";
}

void Clear(Deque& deque) {
  if (deque.size != 0) {
    Node* tmp;
    while (0 < deque.size) {
      tmp = deque.begin;
      deque.begin = deque.begin->next;
      if (deque.size != 1) {
        deque.begin->prev = nullptr;
      } else {
        deque.end = nullptr;
        deque.begin = nullptr;
      }
      deque.size--;
      delete tmp;
    }
  }
}

void Exit(Deque& deque) {
  Clear(deque);
  std::cout << "bye\n";
}
