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
    std::deque<int> second;

    // checks if arguments are only numbers
    // insert them into the containers
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
        second.push_back(static_cast<int>(nb));
    }

    /* ------------------------------ Print before ------------------------------ */
    std::cout << "Before: ";
    for (std::vector<int>::iterator it = first.begin(); it != first.end(); it++) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;

    /* --------------------------------- Sorting -------------------------------- */

    struct timeval vector_timer_begin, vector_timer_end;
    start_timer(&vector_timer_begin);

    first = PmergeMe::merge_insertion_sort(first);

    double vector_time = stop_timer(&vector_timer_begin, &vector_timer_end);

    struct timeval deque_timer_begin, deque_timer_end;
    start_timer(&deque_timer_begin);

    second = PmergeMe::merge_insertion_sort(second);

    double deque_time = stop_timer(&deque_timer_begin, &deque_timer_end);

    /* ------------------------------- Print after ------------------------------ */
    std::cout << "After:  ";
    for (std::vector<int>::iterator it = first.begin(); it != first.end(); it++) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;

    /* ----------------------------- Display timers ----------------------------- */

    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.precision(8);

    std::cout << "Time to process a range of " << argc - 1
              << " elements with std::vector : " << vector_time << " s" << std::endl;
    std::cout << "Time to process a range of " << argc - 1
              << " elements with std::deque : " << deque_time << " s" << std::endl;

    // std::cout << "is vector sorted? " << is_sorted(first) << std::endl;
    // std::cout << "is deque sorted? " << is_sorted(second) << std::endl;

    return 0;
}