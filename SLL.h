#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  void *data;
  struct node *next_node;
};

struct list {
  struct node *head;
  struct node *tail;
  struct node *(*create_node)(struct list *list, size_t data_size, void *data);
  void (*addNode)(struct list *list, size_t data_size, void *data);
  void (*print)(struct list *list);
  void (*free_list)(struct list *list);
  int (*get_size)(struct list *list);
  void (*insert_node)(struct list *list, int index, void *data,
                      size_t data_size);
  int (*delete_node_at_index)(struct list *list, int index);
  int (*pop_front)(struct list *list);
  int (*pop_back)(struct list *list);
  void (*add_front)(struct list *list, void *data, size_t size);
  void *(*copy)(struct list *list, void *data);
  void (*free_special)(void *data);
  bool (*compare)(struct list *list, void *data, void *data2, size_t data_size);
  bool (*node_exists)(struct list *list, void *data, size_t data_size);
};

/**
 * @brief frees node and its data
 *
 * This function frees node and its data
 *
 * @param a node to free
 * @return void.
 */
void free_node(struct list *list, struct node *node);
/**
 * @brief removes tail node
 *
 * This function frees the tail node and frees its memory
 *
 * @param a pointer to the struct list
 * @return 0 on success -1 on failure.
 */
int pop_back(struct list *list);
/**
 * @brief removes head node
 *
 * This function frees the head node and frees its memory
 *
 * @param a pointer to the struct list
 * @return 0 on success -1 on failure.
 */
int pop_front(struct list *list);
/**
 * @brief removes a node at index
 *
 * This function deletes a node at the index specified
 *
 * @param a pointer to the struct list
 * @param b integer index
 * @return 0 on success -1 on failure.
 */
int delete_node(struct list *list, int index);
/**
 * @brief creates a node
 *
 * This function creates a node for int, double, char except for char*
 *
 * @param size of the data to add
 * @param b void * to the data
 * @return a pointer to the node created
 */
struct node *create_node(struct list *list, size_t data_size, void *data);
void addNode(struct list *list, size_t data_size, void *data);
void free_list(struct list *list);
int get_size(struct list *list);
void add_front(struct list *list, void *data, size_t data_size);
void insert_node(struct list *list, int index, void *data, size_t data_size);
void initialize_list(struct list **list, void *print_data, void *create_node,
                     void *deep_copy, void *special_free, void *compare_func);
struct node *create_node_str(struct list *list, size_t data_size, void *data);
bool node_exists(struct list *list, void *data, size_t data_size);
