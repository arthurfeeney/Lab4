#include <algorithm>
#include <numeric>
#include <omp.h>

#include "fun.hpp"

// Don't Parallelize this:
// Just a slow function to evaluate :-)
int really_slow_fibonacci(int n) {
  if (n <= 0) return 0;
  if (n <= 2) return 1;
  return really_slow_fibonacci(n - 1) + really_slow_fibonacci(n - 2);
}

void really_slow_fibonacci_inplace(float& n) {
  n = really_slow_fibonacci(static_cast<int>(n));
}

// Function 1
void fibonacci_nums1(std::vector<int>& nums) {
  for (int i = 0; i < nums.size(); ++i) {
    nums.at(i) = really_slow_fibonacci(nums.at(i));
  }
}

// Function 2
std::vector<double> convolution_1d(const std::vector<double>& nums,
				   const std::vector<double> filter) {
  std::vector<double> result(nums.size() - filter.size(), 0);
  for (int i = 0; i < nums.size(); ++i) {
    if (i + filter.size() < nums.size()) {
      for (int j = 0; j < filter.size(); ++j) {
        result[i] += nums[i + j] * filter[j];
      }
    }
  }
  return result;
}


// Function 3
double approximate_pi() {
  size_t num_steps = 1e9;
  double step_size = 1e-9;
  double sum = 0;
  for (size_t i = 0; i < num_steps; ++i) {
    double x = (i + 0.5) * step_size;
    sum += 4.0 / (1.0 + x*x);
  }
  double pi = step_size * sum;
  return pi;
}

// Function 4
// tricky, but can be done with tasks
void linked_list_traversal(linked_list_node* head) {
  linked_list_node* rover = head;
  while (rover->next) {
    really_slow_fibonacci_inplace(rover->data);
    rover = rover->next;
  }
}

// Function 5
// This one is probably the hardest... :-)
std::vector<int> histogram(std::vector<unsigned> numbers) {
  unsigned int max_elem = *std::max_element(numbers.begin(), numbers.end());
  std::vector<int> counters(max_elem, 0);
  
  for (int i = 0; i < numbers.size(); ++i) {
    unsigned value = numbers[i];
    counters[value] += 1;
  } 

  return counters;
}
