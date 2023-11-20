#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class RPN {
  private:
    std::stack<int> _stack;

  public:
    RPN();
    ~RPN();
    RPN(const RPN &src);
    RPN &operator=(const RPN &rhs);
};

#endif /* RPN_HPP */
