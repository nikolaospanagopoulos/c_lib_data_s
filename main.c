#include "SLL.h"
#include <stdio.h>
#include <string.h>

struct person {
  int age;
  char *name;
};

void *copy(struct list *list, void *data) {
  struct person *to_copy = (struct person *)data;
  struct person *new_person = (struct person *)malloc(sizeof(struct person));
  new_person->age = to_copy->age;
  new_person->name = (char *)malloc(strlen(to_copy->name) + 1);
  strncpy(new_person->name, to_copy->name, strlen(to_copy->name) + 1);
  new_person->name[strlen(to_copy->name)] = '\0';
  return new_person;
}

void free_person(void *data) {
  struct person *to_free = (struct person *)data;
  free(to_free->name);
  free(to_free);
}

void print_data(struct list *list) {

  struct node *tmp_node = list->head;

  while (tmp_node) {

    printf("node data: %d\n", *(int *)tmp_node->data);
    tmp_node = tmp_node->next_node;
  }
}
void print_data_str(struct list *list) {

  struct node *tmp_node = list->head;

  while (tmp_node) {

    printf("node data: %s\n", (char *)tmp_node->data);
    tmp_node = tmp_node->next_node;
  }
}
void print_data_double(struct list *list) {
  struct node *tmp_node = list->head;

  while (tmp_node) {

    printf("node data: %f\n", *(double *)tmp_node->data);
    tmp_node = tmp_node->next_node;
  }
}
void print_data_person(struct list *list) {
  struct node *tmp_node = list->head;

  while (tmp_node) {

    printf("person name %s\nperson age: %d\n",
           ((struct person *)tmp_node->data)->name,
           ((struct person *)tmp_node->data)->age);
    tmp_node = tmp_node->next_node;
  }
}
int main() {

  struct list *my_list;
  initialize_list(&my_list, &print_data, &create_node, NULL, NULL);

  int toAdd = 1;
  int toAdd2 = 77;
  int toAdd3 = 85;

  my_list->addNode(my_list, sizeof(int), &toAdd);
  my_list->addNode(my_list, sizeof(int), &toAdd2);
  my_list->addNode(my_list, sizeof(int), &toAdd3);
  my_list->insert_node(my_list, 0, &toAdd2, sizeof(int));

  my_list->print(my_list);

  struct list *double_list;

  initialize_list(&double_list, print_data_double, &create_node, NULL, NULL);

  double toadd_double = 1.1;
  double toadd_double2 = 2.1;
  double toadd_double3 = 3.1;

  double_list->addNode(double_list, sizeof(double), &toadd_double);
  double_list->addNode(double_list, sizeof(double), &toadd_double2);
  double_list->addNode(double_list, sizeof(double), &toadd_double3);

  double_list->print(double_list);

  printf("\n");

  struct list *string_list;
  initialize_list(&string_list, print_data_str, &create_node_str, NULL, NULL);

  char *toadd = "dwdefefedewdefef test";
  char *toadd2 = " test||";
  char *toadd3 = "dwdefefedewdefef test+++++";
  char *toadd4 = "first place";
  string_list->insert_node(string_list, 0, toadd4, strlen(toadd4) + 1);
  string_list->add_front(string_list, toadd, strlen(toadd) + 1);

  string_list->print(string_list);

  printf("list head->%d\n", *(int *)my_list->head->data);
  printf("list tail->%d\n", *(int *)my_list->tail->data);
  printf("list size: %d\n", my_list->get_size(my_list));

  string_list->free_list(string_list);
  my_list->free_list(my_list);
  double_list->free_list(double_list);

  free(double_list);
  free(my_list);
  free(string_list);

  struct list *struct_list;

  struct person first_person = {.age = 10, .name = "nikos"};

  initialize_list(&struct_list, print_data_person, &create_node, copy,
                  free_person);

  struct_list->addNode(struct_list, sizeof(struct person), &first_person);
  struct_list->addNode(struct_list, sizeof(struct person), &first_person);

  struct_list->print(struct_list);

  struct_list->free_list(struct_list);
  free(struct_list);
}
