#ifndef LAB_FUN_H
#define LAB_FUN_H

#include <vector>

#include "list.hpp"

int really_slow_fibonacci(int n);


void fibonacci_nums1(std::vector<int>& nums);
double approximate_pi();
std::vector<double> convolution_1d(const std::vector<double>& nums,
				   const std::vector<double> filter);
void linked_list_traversal(linked_list_node* head);
std::vector<int> histogram(std::vector<unsigned int> numbers);

#endif
