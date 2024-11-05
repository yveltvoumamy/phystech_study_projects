#include <iostream>

struct Node {
  Node* previus = nullptr;
  Node* next = nullptr;
  int64_t value = 0;
};

struct Stack {
  Node* last = nullptr;
  size_t size = 0;
};

void Top(Stack* stack, int& top);
void Push(Stack* stack, int val);
void Pop(Stack* stack);
void Clear(Stack* stack);
void Output(Stack* stack);
void Input(char bracket, Stack* stack);
size_t Size(Stack* stack);

int main() {
  auto stack = new Stack;
  char bracket = '0';
  Input(bracket, stack);
  Output(stack);
  Clear(stack);
  delete stack;
}

void Check(char bracket, Stack* stack) {
  int top;
  Top(stack, top);
  if (bracket == ')') {
    Push(stack, -1);
    if (top == 1) {
      Pop(stack);
      Pop(stack);
    }
  } else if (bracket == '(') {
    Push(stack, 1);
  } else if (bracket == ']') {
    Push(stack, -2);
    if (top == 2) {
      Pop(stack);
      Pop(stack);
    }
  } else if (bracket == '[') {
    Push(stack, 2);
  } else if (bracket == '}') {
    Push(stack, -3);
    if (top == 3) {
      Pop(stack);
      Pop(stack);
    }
  } else if (bracket == '{') {
    Push(stack, 3);
  }
}

void Input(char bracket, Stack* stack) {
  while (bracket != '\n') {
    bracket = getchar();
    Check(bracket, stack);
  }
}

void Output(Stack* stack) {
  if (Size(stack) != 0) {
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
}

void Top(Stack* stack, int& top) {
  if (stack->size != 0) {
    top = stack->last->value;
    return;
  }
  top = 0;
}

void Push(Stack* stack, int val) {
  auto new_node = new Node;
  new_node->previus = stack->last;
  new_node->value = val;
  ++stack->size;
  stack->last = new_node;
}

void Pop(Stack* stack) {
  Node* last_for_delete = stack->last;
  --stack->size;
  stack->last = stack->last->previus;
  delete last_for_delete;
}

void Clear(Stack* stack) {
  if (stack->size > 0) {
    Pop(stack);
    Clear(stack);
  }
  delete stack->last;
}

size_t Size(Stack* stack) {
  return stack->size;
}