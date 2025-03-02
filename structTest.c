#include "SLL.h"
#include <stdio.h>
#include <stdlib.h>

struct person {
  int age;
  char *name;
};
bool compare_func(struct list *list, void *data, void *data2,
                  size_t data_size) {
  struct person *first = ((struct person *)data);
  struct person *second = ((struct person *)data2);
  bool age_equals = first->age == second->age;
  if (!age_equals) {
    return false;
  }
  return strncmp(first->name, second->name, strlen(first->name)) == 0;
}

void free_person(void *data) {
  struct person *to_free = (struct person *)data;
  free(to_free->name);
  free(to_free);
}

void *copy(struct list *list, void *data) {
  struct person *to_copy = (struct person *)data;
  struct person *new_person = (struct person *)malloc(sizeof(struct person));
  if (!new_person) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  new_person->age = to_copy->age;
  new_person->name = (char *)malloc(strlen(to_copy->name) + 1);
  strncpy(new_person->name, to_copy->name, strlen(to_copy->name) + 1);
  new_person->name[strlen(to_copy->name)] = '\0';
  return new_person;
}

void print_data_struct(void *data) {

  if (!data) {
    return;
  }
  struct person *person = (struct person *)data;

  printf("person name: %s, person age: %d\n", person->name, person->age);
}

int main() {

  struct list *list;

  struct person created_person = {.age = 20, .name = "nikos"};
  struct person to_insert = {.age = 22, .name = "nnnn"};
  struct person to_insert_front = {.age = 22, .name = "front"};
  struct person to_check = {.age = 22, .name = "check"};

  initialize_list(&list, print_data_struct, NULL, copy, free_person,
                  compare_func);

  list->addNode(list, sizeof(created_person), &created_person);
  list->insert_node(list, 1, &to_insert, sizeof(to_insert));
  list->addNode(list, sizeof(created_person), &created_person);
  list->addNode(list, sizeof(created_person), &created_person);
  list->delete_node_at_index(list, 1);
  list->pop_back(list);
  list->pop_back(list);
  list->add_front(list, &to_insert_front, sizeof(to_insert_front));
  printf("exists: %d\n",
         list->node_exists(list, &created_person, sizeof(created_person)));

  list->print_list(list);
  list->free_list(list);

  return 0;
}
