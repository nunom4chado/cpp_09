#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) { (void)src; }

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    (void)rhs;
    return *this;
}

std::vector<int> PmergeMe::merge_insertion_sort(std::vector<int> A) {
    int stray = 0;

    // Check if list has odd elements
    bool has_stray = (A.size() % 2 != 0);

    // if true, remove it from the list and save it in stray
    if (has_stray) {
        stray = A.back();
        A.pop_back();
    }

    (void)stray; // TODO remove this

    /* ----------------------- Step 1: Pairwise comparison ---------------------- */

    std::vector<std::pair<int, int> > pairs;
    std::vector<int>::iterator it;
    std::vector<std::pair<int, int> >::iterator pair_it;

    // Create pairs
    for (it = A.begin(); it != A.end(); it += 2) {
        pairs.push_back(std::pair<int, int>(*it, *(it + 1)));
    }

    print_pairs(pairs, "Create pairs");

    // Sort each pair
    for (pair_it = pairs.begin(); pair_it != pairs.end(); pair_it++) {
        if (pair_it->first < pair_it->second) {
            std::swap(pair_it->first, pair_it->second);
        }
    }

    print_pairs(pairs, "After sort pairs");

    /* ---------------------------- Step 2: Recursion --------------------------- */

    recursive_sort_pair(pairs, pairs.size() - 1);
    print_pairs(pairs, "After recursive sort");

    /* ---------------------------- Step 3: Insertion --------------------------- */

    return A;
}

/* -------------------------------------------------------------------------- */
/*                                  Utilities                                 */
/* -------------------------------------------------------------------------- */

void insert(std::pair<int, int> element, std::vector<std::pair<int, int> > &A, int n) {
    if (n < 0) {
        A.insert(A.begin(), element);
    } else if (element.first >= A[n].first) {
        A.insert(A.begin() + n + 1, element);
    } else {
        insert(element, A, n - 1);
    }
}

void recursive_sort_pair(std::vector<std::pair<int, int> > &pairs, int n) {

    if (n < 1)
        return;

    recursive_sort_pair(pairs, n - 1);

    std::pair<int, int> element = pairs[n];
    pairs.erase(pairs.begin() + n);

    insert(element, pairs, n - 1);
}

/* -------------------------------------------------------------------------- */
/*                                   Extras                                   */
/* -------------------------------------------------------------------------- */

void print_pairs(std::vector<std::pair<int, int> > pairs, const std::string &msg) {
    std::cout << msg << std::endl;

    std::vector<std::pair<int, int> >::iterator it;
    for (it = pairs.begin(); it != pairs.end(); it++) {
        std::cout << "a: " << it->first << " b: " << it->second << std::endl;
    }

    std::cout << std::endl;
}