#ifndef MY_LIST_HPP
#define MY_LIST_HPP

#include <cstdlib>
#include <vector>

struct linked_list_node {
  float data;
  linked_list_node* next;
};

linked_list_node* malloc_linked_list_node();
linked_list_node* constr_linked_list_node(float data); 
linked_list_node* fill_linked_list(const std::vector<float>& data);
int linked_list_size(linked_list_node* head);

#endif
