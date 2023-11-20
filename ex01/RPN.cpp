#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &src) : _stack(src._stack) {}

RPN &RPN::operator=(const RPN &rhs) {
    if (this == &rhs)
        return *this;

    this->_stack = rhs._stack;
    return *this;
}