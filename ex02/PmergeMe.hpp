#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

/*  parsing */
int     parsing_vector(char **argv);

/*  display */
void    display_arg(char **argv);
void    display_container(std::vector<int> container);

/*  algorithm vector    */
int     algo_vector(char **argv, clock_t &time);
int     fill_vector(std::vector<int> &container, char **argv);
void    sort_inside_pair_descendant_vector(std::vector<int> &container);
void    split_pair(std::vector<int> &container, std::vector<int> &pair);
void    merge_sort_vector_split(std::vector<int> &container, std::vector<int> &pair);
void    merge_sort_vector(std::vector<int> &container, std::vector<int> &copy1, std::vector<int> &copy2, size_t length, std::vector<int> &pair, std::vector<int> &copy_pair1, std::vector<int> &copy_pair2);
void    binary_search_jacobsthal_vector(std::vector<int> &container, std::vector<int> &pair);
void    binary_search_place_vector(std::vector<int> &container, int min, int max, int value);

/*  algorithm deque    */
int     algo_deque(char **argv, clock_t &time);
int     fill_deque(std::deque<int> &container, char **argv);
void    sort_inside_pair_descendant_deque(std::deque<int> &container);
void    split_pair(std::deque<int> &container, std::deque<int> &pair);
void    merge_sort_deque_split(std::deque<int> &container, std::deque<int> &pair);
void    merge_sort_deque(std::deque<int> &container, std::deque<int> &copy1, std::deque<int> &copy2, size_t length, std::deque<int> &pair, std::deque<int> &copy_pair1, std::deque<int> &copy_pair2);
void    binary_search_jacobsthal_deque(std::deque<int> &container, std::deque<int> &pair);
void    binary_search_place_deque(std::deque<int> &container, int min, int max, int value);



#endif