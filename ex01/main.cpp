#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Error" << std::endl;
        return 1;
    }

    try {
        std::cout << RPN::calculate(argv[1]) << std::endl;
    } catch (std::string error) {
        std::cout << "Error" << std::endl;
    }

    return 0;
}