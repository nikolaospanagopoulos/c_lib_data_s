#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
  char *name;
  int age;
};

int compare_func(void *element1, void *element2, size_t data_size) {
  if (!element1 || !element2) {
    return -1;
  }
  struct person *first = (struct person *)element1;
  struct person *second = (struct person *)element2;

  if (first->age == second->age &&
      strncmp(first->name, second->name, strlen(first->name)) == 0) {
    return 0;
  }
  return -1;
}

void special_free(void *data) {
  if (!data) {
    return;
  }
  struct person *to_d = (struct person *)data;

  free(to_d->name);
  free(data);
}

void *copy(struct vector *v, void *data, size_t data_size) {
  if (!data || !v) {
    return NULL;
  }
  struct person *to_copy = (struct person *)data;
  struct person *person_copied = (struct person *)malloc(sizeof(struct person));
  if (!person_copied) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  person_copied->age = to_copy->age;
  person_copied->name = (char *)malloc(strlen(to_copy->name) + 1);
  if (!person_copied->name) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  strncpy(person_copied->name, to_copy->name, strlen(to_copy->name) + 1);
  person_copied->name[strlen(to_copy->name)] = '\0';

  return person_copied;
}

void print_func_s(const void *data) { printf("data->%s\n", (char *)data); }
void print_func(const void *data) { printf("data->%d\n", *(int *)data); }
void print_func_person(const void *data) {
  struct person to_print = *(struct person *)data;
  printf("person age %d, name: %s\n", to_print.age, to_print.name);
}
int main() {

  struct vector *vec = NULL;

  initialize_vector(&vec, NULL, print_func, NULL, NULL);

  int toadd = 1;
  int toadd2 = 2;
  int toadd3 = 4;
  int toinsert = 8;
  int totest = 56;

  vec->append(vec, &toadd, sizeof(int));
  vec->append(vec, &toadd, sizeof(int));
  vec->append(vec, &toadd, sizeof(int));
  vec->append(vec, &toadd, sizeof(int));
  vec->append(vec, &toadd2, sizeof(int));
  vec->append(vec, &toadd3, sizeof(int));
  vec->insert(vec, 2, &toinsert, sizeof(int));
  vec->delete_at(vec, 3);
  vec->delete_at(vec, 2);
  vec->delete_at(vec, 1);
  vec->delete_at(vec, 0);
  vec->append(vec, &toadd3, sizeof(int));
  vec->insert(vec, 0, &toinsert, sizeof(int));
  vec->print_vector(vec);
  int pos = vec->exists(vec, &totest, sizeof(int));
  if (pos >= 0) {
    printf("element exists at position :%d, and element is %d\n", pos,
           *(int *)vec->arr[pos]);
  } else {
    printf("element exists at position :%d\n", pos);
  }
  printf("vector size: %lu\n", vec->get_size(vec));

  vec->free_vector(vec);

  struct vector *str_v = NULL;

  initialize_vector(&str_v, NULL, print_func_s, NULL, NULL);

  char *name = "nikos";
  char *name2 = "kikos";
  char *name3 = "fikos";

  str_v->add_front(str_v, name2, strlen(name2) + 1);
  str_v->add_front(str_v, name2, strlen(name2) + 1);
  str_v->add_front(str_v, name2, strlen(name2) + 1);
  str_v->add_front(str_v, name, strlen(name) + 1);
  str_v->add_front(str_v, name2, strlen(name2) + 1);
  str_v->add_front(str_v, name2, strlen(name2) + 1);
  str_v->add_front(str_v, name2, strlen(name2) + 1);
  int pos2 = str_v->exists(str_v, name3, strlen(name3) + 1);
  if (pos2 >= 0) {
    printf("element exists at position :%d, and element is %s\n", pos2,
           (char *)str_v->arr[pos2]);
  } else {
    printf("element exists at position :%d\n", pos2);
  }

  str_v->print_vector(str_v);

  str_v->free_vector(str_v);

  struct vector *struct_v = NULL;

  initialize_vector(&struct_v, special_free, print_func_person, compare_func,
                    copy);

  struct person toadd_person1 = {.age = 20, .name = "nikos"};
  struct person toadd_person2 = {.age = 32, .name = "ella"};
  struct person toadd_person3 = {.age = 36, .name = "lllll"};
  struct person toadd_person4 = {.age = 56, .name = "front"};
  struct_v->append(struct_v, &toadd_person1, sizeof(struct person));
  struct_v->append(struct_v, &toadd_person2, sizeof(struct person));
  struct_v->insert(struct_v, 1, &toadd_person2, sizeof(struct person));
  struct_v->insert(struct_v, 2, &toadd_person3, sizeof(struct person));
  struct_v->append(struct_v, &toadd_person2, sizeof(struct person));
  struct_v->append(struct_v, &toadd_person4, sizeof(struct person));

  int exists =
      struct_v->exists(struct_v, &toadd_person4, sizeof(struct person));

  printf("exists at position %d\n", exists);

  // struct_v->delete_at(struct_v, 2);

  struct_v->print_vector(struct_v);

  struct_v->free_vector(struct_v);

  return 0;
}
