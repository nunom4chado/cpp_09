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

    std::vector<int> main_branch = create_main_branch(pairs, has_stray, stray);

    print_container(main_branch, "inserting...");

    return A;
}

/* -------------------------------------------------------------------------- */
/*                                  Utilities                                 */
/* -------------------------------------------------------------------------- */

std::vector<int> create_main_branch(std::vector<std::pair<int, int> > &pairs, bool has_stray,
                                    int stray) {
    std::vector<int> main_branch;
    std::vector<std::pair<int, int> >::iterator pairs_it;

    (void)has_stray;
    (void)stray;

    for (pairs_it = pairs.begin(); pairs_it != pairs.end(); pairs_it++) {
        if (pairs_it == pairs.begin()) {
            // first pair (a1 and b1)
            // since b1 can be inserted immediately, lets do it now
            main_branch.push_back(pairs_it->second);
            main_branch.push_back(pairs_it->first);
        } else {
            // other b's can't be inserted now! so only add the a's (a2, a3, a4...)
            main_branch.push_back(pairs_it->first);
        }
    }

    return main_branch;
}

void insert(std::pair<int, int> element, std::vector<std::pair<int, int> > &A, int n) {
    if (n < 0) {
        // if n is 0 insert it at the begin
        A.insert(A.begin(), element);
    } else if (element.first >= A[n].first) {
        // if element is bigger or equal to the element in the n position, insert it after
        A.insert(A.begin() + n + 1, element);
    } else {
        // else try find another place for it in a lower index
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

void print_container(std::vector<int> list, const std::string &msg) {
    std::cout << msg << std::endl;

    std::vector<int>::iterator it;
    for (it = list.begin(); it != list.end(); it++) {
        std::cout << *it << std::endl;
    }

    std::cout << std::endl;
}