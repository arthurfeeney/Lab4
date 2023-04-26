#include <algorithm>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <random>

#include "fun.hpp"
#include "list.hpp"

const int test_iters = 5;
double pi_test();
double fibonnaci_test();
double convolution_test();
double list_traversal_test();
double histogram_test();

int main() {

  double fib_runtime = fibonnaci_test();
  double pi_runtime = pi_test();
  double convolution_runtime = convolution_test();
  double traversal_runtime = list_traversal_test();
  double histogram_runtime = histogram_test();

  std::cout << "Using " << omp_get_max_threads() << " threads\n";
  std::cout << " - Fibonacci Calc (s):\t " << std::to_string(fib_runtime) << '\n';
  std::cout << " - Convolution 1D (s):\t " << std::to_string(convolution_runtime) << '\n';
  std::cout << " - PI Approx (s):\t " << std::to_string(pi_runtime) << '\n';
  std::cout << " - List iter (s):\t " << std::to_string(traversal_runtime) << '\n';
  std::cout << " - Histogram (s):\t " << std::to_string(histogram_runtime) << '\n';
  
  return 0;
}

double pi_test() {
  double time_totals = 0.0;
  for (int i = 0; i < test_iters; ++i) {
    double start = omp_get_wtime();
    double approx_pi = approximate_pi();
    time_totals += omp_get_wtime() - start;
    if (std::abs(approx_pi - M_PI) >= 1e-3) {
      std::string msg = "PI Approximate wrong, got " + std::to_string(approx_pi);
      throw std::runtime_error(msg);
    }
  }
  return time_totals / test_iters;
}

double fibonnaci_test() {
  double time_totals = 0.0;
  for (int i = 0; i < test_iters; ++i) {
    std::vector<int> nums(100, 35);
    double start = omp_get_wtime();
    fibonacci_nums1(nums);
    time_totals += omp_get_wtime() - start;
    for (auto num : nums) {
      if (num != 9227465) {
        std::string msg = "Fibonacci wrong, got " + std::to_string(num);
	throw std::runtime_error(msg);
      }
    }
  }
  return time_totals / test_iters;
}

double convolution_test() {
  double time_totals = 0.0;
  for (int i = 0; i < test_iters; ++i) {
    std::vector<double> nums(10000000, 1);
    std::vector<double> filter(60, 1);
    double start = omp_get_wtime();
    std::vector<double> result = convolution_1d(nums, filter);
    time_totals += omp_get_wtime() - start;
    for (auto num : result) {
      if (num != filter.size()) {
        std::string msg = "Convolution wrong, got " +
	       	std::to_string(num) +
	       	" but expected " +
	        std::to_string(filter.size());
	throw std::runtime_error(msg);
      }
    }
  }
  return time_totals / test_iters;
}

double list_traversal_test() {
  double time_totals = 0.0;
  for (int i = 0; i < test_iters; ++i) {
    std::vector<float> nums(100, 35);
    linked_list_node* head = fill_linked_list(nums);

    double start = omp_get_wtime();
    linked_list_traversal(head);
    time_totals += omp_get_wtime() - start;

    linked_list_node* rover = head;

    int ll_size = linked_list_size(rover);
    if (ll_size != nums.size()) {
      std::string msg = "List Traversal got messed up, length should be " + std::to_string(nums.size()) +
	      "but list has length " + std::to_string(ll_size);
      throw std::runtime_error(msg);
    }

    while (rover->next) {
      if (rover->data != 9227465) {
        std::string msg = "List Traversal wrong, got " + std::to_string(rover->data);
	throw std::runtime_error(msg);
      }
      rover = rover->next; 
    }
  }
  return time_totals / test_iters;
}

double histogram_test() {
  std::random_device rnd_device;
  std::mt19937 mersenne_engine {rnd_device()};
  std::uniform_int_distribution<unsigned> dist {1, 10000};

  auto gen = [&dist, &mersenne_engine](){
    return dist(mersenne_engine);
  };

  double time_totals = 0.0;
  for (int i = 0; i < test_iters; ++i) {
    std::vector<unsigned> numbers(100000000);
    std::generate(numbers.begin(), numbers.end(), gen);

    double start = omp_get_wtime();
    auto bins = histogram(numbers);
    time_totals += omp_get_wtime() - start;

    unsigned max_elem = *std::max_element(numbers.begin(), numbers.end());
    std::vector<int> counters(max_elem, 0);
    for (int i = 0; i < numbers.size(); ++i) {
      unsigned value = numbers[i];
      counters[value] += 1;
    } 

    for (int i = 0; i < bins.size(); ++i) {
      if (bins[i] != counters[i]) {
        std::string msg = "Histogram wrong, doesn't match serial version...";
	throw std::runtime_error(msg);
      }
    }
  }
  return time_totals / test_iters;
}
