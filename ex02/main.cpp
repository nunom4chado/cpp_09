#include "PmergeMe.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Error" << std::endl;
        return 1;
    }

    std::vector<int> first;

    // checks if arguments are only numbers
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]).find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Error" << std::endl;
            return 1;
        }
        std::size_t nb = std::atol(argv[i]);
        if (nb >= INT_MAX) {
            std::cout << "Error" << std::endl;
            return 1;
        }
        first.push_back(static_cast<int>(nb));
    }

    std::cout << "Arguments: " << std::endl;
    for (std::vector<int>::iterator it = first.begin(); it != first.end(); it++) {
        std::cout << *it << std::endl;
    }

    PmergeMe::merge_insertion_sort(first);

    return 0;
}