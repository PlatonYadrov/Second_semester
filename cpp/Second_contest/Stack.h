#include <iostream>
#include <deque>
#ifndef STACK_H
#define STACK_H

template <class T, class Container = std::deque<T>>
class Stack {
 public:
  Container stack;
  Stack() = default;

  Stack(const Container& other) {  // NOLINT
    for (auto to : other) {
      stack.push_back(to);
    }
  }

  template <class Iter>
  Stack(Iter begin, Iter end) {
    stack = Container(begin, end);
  }

  const T& Top() const {
    return stack.back();
  }

  T& Top() {
    return stack.back();
  }

  bool Empty() const {
    return stack.empty();
  }

  size_t Size() const {
    return stack.size();
  }

  void Push(T&& var) {
    stack.push_back(std::move(var));
  }

  void Push(const T& var) {
    stack.push_back(var);
  }

  void Pop() {
    stack.pop_back();
  }

  template <class... Arguments>
  void Emplace(Arguments&&... arguments) {
    stack.emplace_back(std::forward<Arguments>(arguments)...);
  }

  void Swap(Stack& other) {
    Container temp = other.stack;
    other.stack = stack;
    stack = temp;
  }
};
#endif
