#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(void *element1, void *element2, size_t data_size) {
  if (!element1 || !element2) {
    return -1;
  }
  return memcmp(element1, element2, data_size);
}
int exists(struct vector *vec, void *element, size_t data_size) {
  if (!vec || !element) {
    return -1;
  }
  for (size_t i = 0; i < vec->size; i++) {
    if (vec->compare(vec->arr[i], element, data_size) == 0) {
      return i;
    }
  }
  return -1;
}
void free_el(struct vector *vec, void *data) {
  if (vec->special_free != NULL) {
    vec->special_free(data);
    return;
  }

  free(data);
}

int delete_at(struct vector *vec, int index) {
  if (index >= vec->size || index < 0) {
    return -1;
  }

  void *found_element = vec->arr[index];

  for (size_t i = index; i < vec->size - 1; i++) {
    vec->arr[i] = vec->arr[i + 1];
  }
  vec->size--;
  free_el(vec, found_element);

  return 0;
}

int insert(struct vector *vec, int index, void *data, size_t data_size) {
  if (!data) {
    return -1;
  }
  if (index >= vec->size || index < 0) {
    return -1;
  }

  if (index == 0) {
    vec->add_front(vec, data, data_size);
    return 0;
  }
  void *copied_data = NULL;
  if (vec->copy != NULL) {
    copied_data = vec->copy(vec, data, data_size);
  } else {
    copied_data = malloc(data_size);
    if (!copied_data) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    memcpy(copied_data, data, data_size);
  }

  vec->size++;
  for (size_t i = vec->size - 1; i >= index; i--) {
    vec->arr[i] = vec->arr[i - 1];
  }
  vec->arr[index] = copied_data;

  return 0;
}
size_t get_size(struct vector *vec) { return vec->size; }

int add_front(struct vector *vec, void *data, size_t data_size) {
  if (!vec || !data) {
    return -1;
  }
  if (vec->size == vec->capacity) {
    expand_capacity(vec);
  }
  void *copied_data = NULL;
  if (vec->copy != NULL) {
    copied_data = vec->copy(vec, data, data_size);
  } else {
    copied_data = malloc(data_size);
    if (!copied_data) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    memcpy(copied_data, data, data_size);
  }
  vec->size++;
  for (size_t i = vec->size - 1; i > 0; i--) {
    vec->arr[i] = vec->arr[i - 1];
  }
  vec->arr[0] = copied_data;
  return 0;
}

void free_vector(struct vector *vec) {
  for (size_t i = 0; i < vec->size; i++) {
    free_el(vec, vec->arr[i]);
  }
  free(vec->arr);
  free(vec);
}

void print_vector(struct vector *vec) {
  if (!vec) {
    return;
  }
  if (vec->print == NULL) {
    return;
  }
  size_t vector_size = vec->size;
  for (size_t i = 0; i < vector_size; i++) {
    vec->print(vec->arr[i]);
  }
}

void initialize_vector(struct vector **to_init, void *special_free, void *print,
                       void *compare_func, void *copy_func) {
  *to_init = (struct vector *)malloc(sizeof(struct vector));
  (*to_init)->capacity = 5;
  (*to_init)->size = 0;
  (*to_init)->arr = malloc((*to_init)->capacity * sizeof(void *));
  (*to_init)->append = &append;
  (*to_init)->special_free = special_free;
  (*to_init)->free_vector = &free_vector;
  (*to_init)->expand_capacity = &expand_capacity;
  (*to_init)->print = print;
  (*to_init)->add_front = &add_front;
  (*to_init)->print_vector = &print_vector;
  (*to_init)->get_size = &get_size;
  (*to_init)->insert = &insert;
  (*to_init)->delete_at = &delete_at;
  if (compare_func == NULL) {
    (*to_init)->compare = &compare;
  } else {
    (*to_init)->compare = compare_func;
  }
  (*to_init)->exists = &exists;
  (*to_init)->copy = copy_func;
}

int append(struct vector *vector, void *data, size_t data_size) {
  if (vector->size == vector->capacity) {
    vector->expand_capacity(vector);
  }
  void *copied_data = NULL;
  if (vector->copy) {
    copied_data = vector->copy(vector, data, data_size);
  } else {
    copied_data = malloc((data_size));
    memcpy(copied_data, data, data_size);
  }

  vector->arr[vector->size] = copied_data;

  vector->size++;

  return 0;
}

void expand_capacity(struct vector *vector) {
  printf("expanding...\n");
  void **new_vec = realloc(vector->arr, vector->capacity * 2 * sizeof(void *));
  for (int i = vector->capacity; i < vector->capacity * 2; i++) {
    new_vec[i] = 0x0;
  }
  vector->capacity *= 2;
  vector->arr = new_vec;
}
