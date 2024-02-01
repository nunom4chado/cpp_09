#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <sys/time.h>
#include <time.h>
#include <utility>
#include <vector>

class PmergeMe {
  public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &src);
    PmergeMe &operator=(const PmergeMe &rhs);

    static std::vector<int> merge_insertion_sort(std::vector<int> A);
    static std::deque<int> merge_insertion_sort(std::deque<int> A);
};

void print_container(std::vector<int> list, const std::string &msg);
void print_pairs(std::vector<std::pair<int, int> > pairs, const std::string &msg);
std::vector<int> create_main_branch(std::vector<std::pair<int, int> > &pairs);
std::deque<int> create_main_branch(std::deque<std::pair<int, int> > &pairs);
std::vector<int> create_insert_sequence(std::vector<std::pair<int, int> > &pairs);
std::deque<int> create_insert_sequence(std::deque<std::pair<int, int> > &pairs);
// void insert(std::pair<int, int> element, std::deque<std::pair<int, int> > &A, int n);
void recursive_sort_pair(std::vector<std::pair<int, int> > &pairs, int n);
void recursive_sort_pair(std::deque<std::pair<int, int> > &pairs, int n);
bool is_sorted(std::vector<int> a);
bool is_sorted(std::deque<int> a);

void start_timer(struct timeval *begin);
double stop_timer(struct timeval *begin, struct timeval *end);

#endif /* PMERGEME_HPP */
