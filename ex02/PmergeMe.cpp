#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) { (void)src; }

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    (void)rhs;
    return *this;
}

/* -------------------------------------------------------------------------- */
/*                                   Vector                                   */
/* -------------------------------------------------------------------------- */

std::vector<int> PmergeMe::merge_insertion_sort(std::vector<int> A) {
    if (A.size() < 2)
        return A;

    int stray = 0;

    // Check if list has odd elements
    bool has_stray = (A.size() % 2 != 0);

    // if true, remove it from the list and save it in stray
    if (has_stray) {
        stray = A.back();
        A.pop_back();
    }

    /* ----------------------- Step 1: Pairwise comparison ---------------------- */

    std::vector<std::pair<int, int> > pairs;
    std::vector<int>::iterator it;
    std::vector<int>::iterator s_it;
    std::vector<std::pair<int, int> >::iterator pair_it;

    // Create pairs
    for (it = A.begin(); it != A.end(); it += 2) {
        pairs.push_back(std::pair<int, int>(*it, *(it + 1)));
    }

    // print_pairs(pairs, "Create pairs");

    // Sort each pair
    for (pair_it = pairs.begin(); pair_it != pairs.end(); pair_it++) {
        if (pair_it->first < pair_it->second) {
            std::swap(pair_it->first, pair_it->second);
        }
    }

    // print_pairs(pairs, "After sort pairs");

    /* ---------------------------- Step 2: Recursion --------------------------- */

    recursive_sort_pair(pairs, pairs.size() - 1);
    // print_pairs(pairs, "After recursive sort");

    /* ---------------------------- Step 3: Insertion --------------------------- */

    std::vector<int> main_branch = create_main_branch(pairs);

    // print_container(main_branch, "inserting...");

    // insert stray into the pairs now, the pair value will be 0 because wont need it
    // its easier to calculate and insert it at the right time
    if (has_stray)
        pairs.push_back(std::pair<int, int>(0, stray));

    std::vector<int> insert_sequence = create_insert_sequence(pairs);

    // print_container(insert_sequence, "insert sequence");

    for (it = insert_sequence.begin(); it != insert_sequence.end(); it++) {
        // std::cout << "b" << *it << " is " << pairs[*it - 1].second << std::endl;

        s_it = main_branch.begin();

        while (*s_it < pairs[*it - 1].second)
            s_it++;

        main_branch.insert(s_it, pairs[*it - 1].second);
    }

    // print_container(main_branch, "main branch");

    return main_branch;
}

std::vector<int> create_insert_sequence(std::vector<std::pair<int, int> > &pairs) {
    std::vector<int> insert_sequence;

    int jacobsthal[] = {
        1,     3,      5,       11,        43,        683, 2731,
        43691, 174763, 2796203, 715827883, 2147483647}; // last number was lowered down to INT_MAX

    int max_b_index = pairs.size();
    int max_index_needed = 0;

    while (max_b_index > jacobsthal[max_index_needed])
        max_index_needed++;

    // std::cout << "number of pairs " << pairs.size() << std::endl;
    // std::cout << "max index is " << max_index_needed << std::endl;
    // std::cout << "because highest b index is " << max_b_index << " and it's bellow or equal to "
    //           << jacobsthal[max_index_needed] << std::endl;

    if (max_index_needed == 0)
        return insert_sequence;

    for (int i = 0; i < max_index_needed; i++) {
        int cur = jacobsthal[i + 1];

        if (max_b_index < cur)
            cur = max_b_index;

        while (cur > jacobsthal[i]) {
            insert_sequence.push_back(cur);
            cur--;
        }
    }

    return insert_sequence;
}

std::vector<int> create_main_branch(std::vector<std::pair<int, int> > &pairs) {
    std::vector<int> main_branch;
    std::vector<std::pair<int, int> >::iterator pairs_it;

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
/*                                   Deque                                    */
/* -------------------------------------------------------------------------- */

std::deque<int> PmergeMe::merge_insertion_sort(std::deque<int> A) {
    if (A.size() < 2)
        return A;

    int stray = 0;

    // Check if list has odd elements
    bool has_stray = (A.size() % 2 != 0);

    // if true, remove it from the list and save it in stray
    if (has_stray) {
        stray = A.back();
        A.pop_back();
    }

    /* ----------------------- Step 1: Pairwise comparison ---------------------- */

    std::deque<std::pair<int, int> > pairs;
    std::deque<int>::iterator it;
    std::deque<int>::iterator s_it;
    std::deque<std::pair<int, int> >::iterator pair_it;

    // Create pairs
    for (it = A.begin(); it != A.end(); it += 2) {
        pairs.push_back(std::pair<int, int>(*it, *(it + 1)));
    }

    // print_pairs(pairs, "Create pairs");

    // Sort each pair
    for (pair_it = pairs.begin(); pair_it != pairs.end(); pair_it++) {
        if (pair_it->first < pair_it->second) {
            std::swap(pair_it->first, pair_it->second);
        }
    }

    // print_pairs(pairs, "After sort pairs");

    /* ---------------------------- Step 2: Recursion --------------------------- */

    recursive_sort_pair(pairs, pairs.size() - 1);
    // print_pairs(pairs, "After recursive sort");

    /* ---------------------------- Step 3: Insertion --------------------------- */

    std::deque<int> main_branch = create_main_branch(pairs);

    // print_container(main_branch, "inserting...");

    // insert stray into the pairs now, the pair value will be 0 because wont need it
    // its easier to calculate and insert it at the right time
    if (has_stray)
        pairs.push_back(std::pair<int, int>(0, stray));

    std::deque<int> insert_sequence = create_insert_sequence(pairs);

    // print_container(insert_sequence, "insert sequence");

    for (it = insert_sequence.begin(); it != insert_sequence.end(); it++) {
        // std::cout << "b" << *it << " is " << pairs[*it - 1].second << std::endl;

        s_it = main_branch.begin();

        while (*s_it < pairs[*it - 1].second)
            s_it++;

        main_branch.insert(s_it, pairs[*it - 1].second);
    }

    // print_container(main_branch, "main branch");

    return main_branch;
}

std::deque<int> create_insert_sequence(std::deque<std::pair<int, int> > &pairs) {
    std::deque<int> insert_sequence;

    int jacobsthal[] = {
        1,     3,      5,       11,        43,        683, 2731,
        43691, 174763, 2796203, 715827883, 2147483647}; // last number was lowered down to INT_MAX

    int max_b_index = pairs.size();
    int max_index_needed = 0;

    while (max_b_index > jacobsthal[max_index_needed])
        max_index_needed++;

    // std::cout << "number of pairs " << pairs.size() << std::endl;
    // std::cout << "max index is " << max_index_needed << std::endl;
    // std::cout << "because highest b index is " << max_b_index << " and it's bellow or equal to "
    //           << jacobsthal[max_index_needed] << std::endl;

    if (max_index_needed == 0)
        return insert_sequence;

    for (int i = 0; i < max_index_needed; i++) {
        int cur = jacobsthal[i + 1];

        if (max_b_index < cur)
            cur = max_b_index;

        while (cur > jacobsthal[i]) {
            insert_sequence.push_back(cur);
            cur--;
        }
    }

    return insert_sequence;
}

std::deque<int> create_main_branch(std::deque<std::pair<int, int> > &pairs) {
    std::deque<int> main_branch;
    std::deque<std::pair<int, int> >::iterator pairs_it;

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

void insert(std::pair<int, int> element, std::deque<std::pair<int, int> > &A, int n) {
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

void recursive_sort_pair(std::deque<std::pair<int, int> > &pairs, int n) {

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

void start_timer(struct timeval *begin) { gettimeofday(begin, 0); }

double stop_timer(struct timeval *begin, struct timeval *end) {
    // Stop measuring time and calculate the elapsed time
    gettimeofday(end, 0);
    long seconds = end->tv_sec - begin->tv_sec;
    long microseconds = end->tv_usec - begin->tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    return elapsed;
}

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

bool is_sorted(std::vector<int> a) {
    std::vector<int>::iterator it;

    for (it = a.begin(); it != a.end(); it++) {
        if (it == a.begin())
            continue;
        if (*it < *(it - 1))
            return false;
    }

    return true;
}

bool is_sorted(std::deque<int> a) {
    std::deque<int>::iterator it;

    for (it = a.begin(); it != a.end(); it++) {
        if (it == a.begin())
            continue;
        if (*it < *(it - 1))
            return false;
    }

    return true;
}