#include <cstdlib>
#include <vector>

#include "list.hpp"

linked_list_node* malloc_linked_list_node() {
  return (linked_list_node*) malloc(sizeof(linked_list_node));
}

linked_list_node* constr_linked_list_node(float data) {
  linked_list_node* ll = malloc_linked_list_node();
  ll->data = data;
  ll->next = nullptr;
  return ll;
}

linked_list_node* fill_linked_list(const std::vector<float>& data) {
  linked_list_node* head = constr_linked_list_node(data.at(0));
  linked_list_node* rover = head;
  for (int i = 1; i < data.size(); ++i) {
    rover->next = constr_linked_list_node(data.at(i));
    rover = rover->next;
  }
  return head;
}

int linked_list_size(linked_list_node* head) {
  linked_list_node* rover = head;
  int size = 0;
  while (rover) {
    rover = rover->next;
    ++size;
  }
  return size;
}
