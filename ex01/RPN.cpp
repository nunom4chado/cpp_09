#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &src) { (void)src; }

RPN &RPN::operator=(const RPN &rhs) {
    (void)rhs;
    return *this;
}

void RPN::make_operation(const char op, std::stack<float> &stack) {

    // not enough number to make calculation
    if (stack.size() < 2)
        throw std::string("Invalid Expression");

    float second = stack.top();
    stack.pop();
    float first = stack.top();
    stack.pop();

    switch (op) {
    case '+':
        stack.push(first + second);
        break;
    case '-':
        stack.push(first - second);
        break;
    case '*':
        stack.push(first * second);
        break;
    case '/':
        if (second == 0)
            throw std::string("Division by 0");
        stack.push(first / second);
        break;
    default:
        // just to make it more safe (will never reach here)
        throw std::string("Invalid Expression");
        break;
    }
}

float RPN::calculate(const std::string &expression) {
    std::stack<float> stack;

    for (std::string::const_iterator it = expression.begin();
         it != expression.end(); it++) {

        if (*it == ' ') // skip spaces
            continue;

        if (std::isdigit(*it)) {
            stack.push(*it - '0'); // convert to int
            continue;
        }

        if (*it == '+' || *it == '-' || *it == '*' || *it == '/') {
            RPN::make_operation(*it, stack);
        } else {
            throw std::string("Invalid Expression");
        }
    }

    // Check if has only 1 number in the stack
    if (stack.size() != 1) {
        throw std::string("Invalid Expression");
    }

    return (stack.top());
}