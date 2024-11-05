#include <iostream>
#include <cstring>

struct Node {
  Node* previous = nullptr;
  int64_t value = 0;
  int64_t min = 0;
};

struct Stack {
  Node* last = nullptr;
  size_t size = 0;
};

struct MinQueue {
  Stack* head = new Stack;
  Stack* tail = new Stack;
};

void FastOutput();
int Comparison(char* operation);
void TargetSetting(char* operation, MinQueue* queue, int& num);
void Push(Stack* stack, int64_t value);
int64_t Pop(Stack* stack);
int64_t Top(const Stack* stack);
void Clear(Stack* stack);
void Reload(MinQueue* queue);
void Enqueue(MinQueue* queue, int64_t x);
void Dequeue(MinQueue* queue);
void Front(MinQueue* queue);
void Size(MinQueue* queue);
void Clear(MinQueue* queue);
void Min(MinQueue* queue);
void GetRidOfGarbage(MinQueue* queue);

int main() {
  FastOutput();
  char operation[10];
  int num, m;
  auto queue = new MinQueue;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    TargetSetting(operation, queue, num);
  }
  GetRidOfGarbage(queue);
}

void FastOutput() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

void Push(Stack* stack, int64_t value) {
  auto new_node = new Node;
  if (stack->size <= 0) {
    new_node->min = value;
  } else {
    if (stack->last->min >= value) {
      new_node->min = value;
    } else {
      new_node->min = stack->last->min;
    }
  }
  new_node->value = value;
  new_node->previous = stack->last;
  stack->last = new_node;
  ++stack->size;
}

int64_t Pop(Stack* stack) {
  int64_t tmp = stack->last->value;
  Node* last_for_delete = stack->last;
  --stack->size;
  stack->last = stack->last->previous;
  delete last_for_delete;
  return tmp;
}

int64_t Top(const Stack* stack) {
  return stack->last->value;
}

void Clear(Stack* stack) {
  if (stack->size > 0) {
    Pop(stack);
    Clear(stack);
  }
  delete stack->last;
}

void Reload(MinQueue* queue) {
  if (queue->head->size == 0) {
    return;
  }
  while (queue->head->size != 0) {
    Push(queue->tail, Pop(queue->head));
  }
}

void Enqueue(MinQueue* queue, int64_t x) {
  Push(queue->head, x);
  std::cout << "ok\n";
}

void Dequeue(MinQueue* queue) {
  if (queue->tail->size != 0) {
    std::cout << Pop(queue->tail) << '\n';
  } else {
    if (queue->head->size != 0) {
      Reload(queue);
      std::cout << Pop(queue->tail) << '\n';
    } else {
      std::cout << "error\n";
    }
  }
}

void Front(MinQueue* queue) {
  if (queue->tail->size != 0) {
    std::cout << Top(queue->tail) << '\n';
  } else if (queue->head->size != 0) {
    Reload(queue);
    std::cout << Top(queue->tail) << '\n';
  } else {
    std::cout << "error\n";
  }
}

void Size(MinQueue* queue) {
  std::cout << queue->head->size + queue->tail->size << '\n';
}

void Clear(MinQueue* queue) {
  Clear(queue->tail);
  Clear(queue->head);
}

void Min(MinQueue* queue) {
  if (queue->head->size == 0 && queue->tail->size == 0) {
    std::cout << "error\n";
  } else if (queue->tail->size == 0) {
    std::cout << queue->head->last->min << '\n';
  } else if (queue->head->size == 0) {
    std::cout << queue->tail->last->min << '\n';
  } else if (queue->head->last->min > queue->tail->last->min) {
    std::cout << queue->tail->last->min << '\n';
  } else {
    std::cout << queue->head->last->min << '\n';
  }
}

void TargetSetting(char* operation, MinQueue* queue, int& num) {
  std::cin >> operation;
  switch (Comparison(operation)) {
    case 0:
      std::cout << "error";
      break;
    case 1:
      std::cin >> num;
      Enqueue(queue, num);
      break;
    case 2:
      Dequeue(queue);
      break;
    case 3:
      Front(queue);
      break;
    case 4:
      Size(queue);
      break;
    case 5:
      Clear(queue);
      std::cout << "ok\n";
      break;
    case 6:
      Min(queue);
      break;
  }
}

int Comparison(char* operation) {
  if (strcmp(operation, "enqueue") == 0) {
    return 1;
  }
  if (strcmp(operation, "dequeue") == 0) {
    return 2;
  }
  if (strcmp(operation, "front") == 0) {
    return 3;
  }
  if (strcmp(operation, "size") == 0) {
    return 4;
  }
  if (strcmp(operation, "clear") == 0) {
    return 5;
  }
  if (strcmp(operation, "min") == 0) {
    return 6;
  }
  return 404;
}

void GetRidOfGarbage(MinQueue* queue) {
  Clear(queue);
  delete queue->head;
  delete queue->tail;
  delete queue;
}