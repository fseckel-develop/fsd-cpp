// Created by Franz Seckel on 08.10.25.
#include <iostream>
#include <ostream>
#include "src/Deque.h"

int main() {
    const Deque deque = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << deque.size() << std::endl;
}
