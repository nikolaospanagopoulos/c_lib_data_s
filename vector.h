#pragma once
#include <stdio.h>

struct vector {
  size_t size;
  size_t capacity;
  void **arr;
  int (*append)(struct vector *vector, void *data, size_t data_size);
  void (*expand_capacity)(struct vector *vector);
  void (*free_vector)(struct vector *vec);
  void (*special_free)(void *data);
  void (*print)(const void *data);
  void (*print_vector)(struct vector *vec);
  int (*add_front)(struct vector *vec, void *data, size_t data_size);
  size_t (*get_size)(struct vector *vec);
  int (*insert)(struct vector *vec, int index, void *data, size_t data_size);
  int (*delete_at)(struct vector *vec, int index);
  int (*exists)(struct vector *vec, void *element, size_t data_size);
  int (*compare)(void *element1, void *element2, size_t data_size);
  void *(*copy)(struct vector *vec, void *element, size_t data_size);
};

int append(struct vector *vector, void *data, size_t data_size);
void initialize_vector(struct vector **to_init, void *special_free, void *print,
                       void *compare_func, void *copy_func);
void expand_capacity(struct vector *vector);
void free_vector_node(void *data);
void free_vector(struct vector *vec);
void print_vector(struct vector *vec);
int add_front(struct vector *vec, void *data, size_t data_size);
size_t get_size(struct vector *vec);
int insert(struct vector *vec, int index, void *data, size_t data_size);
int delete_at(struct vector *vec, int index);
int exists(struct vector *vec, void *element, size_t data_size);
