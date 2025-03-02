#include "SLL.h"
#include <stdio.h>

void print_data_str(void *data) { printf("node data: %s\n", (char *)data); }

int main() {

  struct list *string_list;
  initialize_list(&string_list, print_data_str, &create_node_str, NULL, NULL,
                  NULL);

  char *toadd = "dwdefefedewdefef test";
  char *toadd2 = " test||";
  char *toadd3 = "dwdefefedewdefef test+++++";
  char *toadd4 = "first place";
  string_list->insert_node(string_list, 0, toadd4, strlen(toadd4) + 1);
  string_list->insert_node(string_list, 1, toadd2, strlen(toadd4) + 1);
  string_list->add_front(string_list, toadd, strlen(toadd) + 1);
  string_list->addNode(string_list, strlen(toadd4) + 1, toadd4);
  string_list->addNode(string_list, strlen(toadd) + 1, toadd);
  // string_list->delete_node_at_index(string_list, 0);
  //  string_list->pop_front(string_list);
  //  string_list->pop_back(string_list);
  string_list->pop_front(string_list);
  printf("exists %d\n",
         string_list->node_exists(string_list, toadd, strlen(toadd) + 1));

  printf("---------------------------------------\n");
  if (string_list->head) {
    printf("list head= %s\n", (char *)string_list->head->data);
  }
  if (string_list->tail) {
    printf("list tail= %s\n", (char *)string_list->tail->data);
  }
  printf("---------------------------------------\n");

  string_list->print_list(string_list);

  string_list->free_list(string_list);
  return 0;
}
