#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

/*  parsing */
int     parsing_vector(std::vector<int> &number, char **argv);

/*  algorithm vector    */
int     algo_vector(std::vector<int> &container);
void    sort_inside_pair_descendant_vector(std::vector<int> &container);
void    split_pair(std::vector<int> &container, std::vector<int> &pair);
void    merge_sort_vector_split(std::vector<int> &container, std::vector<int> &pair);
void    merge_sort_vector(std::vector<int> &container, std::vector<int> &copy1, std::vector<int> &copy2, size_t length, std::vector<int> &pair, std::vector<int> &copy_pair1, std::vector<int> &copy_pair2);
void    binary_search_jacobsthal_vector(std::vector<int> &container, std::vector<int> &pair);
void    binary_search_place_vector(std::vector<int> &container, int min, int max, int value);

#endif