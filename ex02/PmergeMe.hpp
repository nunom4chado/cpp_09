#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

class PmergeMe {
  public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &src);
    PmergeMe &operator=(const PmergeMe &rhs);

    static std::vector<int> merge_insertion_sort(std::vector<int> A);
};

void print_pairs(std::vector<std::pair<int, int> > pairs, const std::string &msg);
void recursive_sort_pair(std::vector<std::pair<int, int> > &pairs, int n);

#endif /* PMERGEME_HPP */
