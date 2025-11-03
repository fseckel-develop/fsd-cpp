// Created by Franz Seckel on 08.10.25.
#include <iostream>
#include <ostream>
#include "src/DoubleList.h"
#include "src/Stack.h"

int main() {
    Stack<int, DoubleList<int>> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << stack.top() << std::endl;
    stack.pop();
    std::cout << stack.top() << std::endl;
    stack.pop();
    std::cout << stack.top() << std::endl;
}
