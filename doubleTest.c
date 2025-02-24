#include "SLL.h"
#include <stdio.h>

void print_data(void *data) {
  if (!data) {
    return;
  }
  double data_to_print = *(double *)data;
  printf("data : %.2f\n", data_to_print);
}

int main() {

  struct list *list;
  initialize_list(&list, print_data, NULL, NULL, NULL, NULL);

  double toadd = 10.2;
  double toadd2 = 20.21;
  double tocompare = 1.2;

  list->addNode(list, sizeof(double), &toadd);
  list->addNode(list, sizeof(double), &toadd);
  list->addNode(list, sizeof(double), &toadd);
  list->addNode(list, sizeof(double), &toadd);
  list->addNode(list, sizeof(double), &toadd);
  list->addNode(list, sizeof(double), &toadd2);
  list->add_front(list, &toadd2, sizeof(double));
  list->delete_node_at_index(list, 0);

  printf("exists: %d\n", list->node_exists(list, &tocompare, sizeof(double)));

  list->print_list(list);

  list->free_list(list);
  free(list);

  return 0;
}
