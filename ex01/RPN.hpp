#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>

class RPN {
  public:
    RPN();
    ~RPN();
    RPN(const RPN &src);
    RPN &operator=(const RPN &rhs);

    static void make_operation(const char op, std::stack<float> &stack);
    static float calculate(const std::string &expression);
};

#endif /* RPN_HPP */
