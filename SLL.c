#include "SLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_list(const struct list *list) {
  if (!list) {
    return;
  }
  struct node *tmp = list->head;
  while (tmp) {
    list->print(tmp->data);
    tmp = tmp->next_node;
  }
}

bool compare(struct list *list, void *data, void *data2, size_t data_size) {
  return memcmp(data, data2, data_size) == 0;
}
bool node_exists(struct list *list, void *data, size_t data_size) {
  if (!list) {
    return false;
  }
  struct node *tmp_node = list->head;
  while (tmp_node) {

    if (list->compare(list, tmp_node->data, data, data_size)) {
      return true;
    }

    tmp_node = tmp_node->next_node;
  }
  return false;
}

void free_node(struct list *list, struct node *node) {
  if (node) {
    if (list->free_special != NULL) {
      list->free_special(node->data);
    } else {
      if (node->data) {
        free(node->data);
      }
    }
    free(node);
  }
}

int pop_back(struct list *list) {
  if (!list->tail) {
    return -1;
  }
  if (list->head == list->tail) {
    free_node(list, list->tail);
    list->head = list->tail = NULL;
    return 0;
  }
  struct node *tmp = list->head;
  struct node *prev = NULL;
  int index = 0;
  while (tmp) {

    if (tmp == list->tail && prev) {
      list->tail = prev;
      list->tail->next_node = NULL;
      free_node(list, tmp);
      break;
    }

    prev = tmp;
    tmp = tmp->next_node;
    index++;
  }

  return 0;
}

int pop_front(struct list *list) {
  if (!list->head) {
    return -1;
  }
  struct node *tmp = list->head;
  list->head = tmp->next_node;
  if (!list->head) {
    list->tail = NULL;
  }
  free_node(list, tmp);
  return 0;
}

int delete_node(struct list *list, int index) {
  if (index >= list->get_size(list) || index < 0) {
    return -1;
  }
  if (index == 0) {
    return pop_front(list);
  }
  if (index == list->get_size(list) - 1) {
    return pop_back(list);
  }
  struct node *tmp_node = list->head;
  int tmp_index = 0;
  struct node *prev = NULL;
  while (tmp_node) {

    if (index == tmp_index) {
      if (prev) {
        prev->next_node = tmp_node->next_node;
        // free(tmp_node->data);
        // free(tmp_node);
        free_node(list, tmp_node);
        return 0;
      }
    }

    tmp_index++;
    prev = tmp_node;
    tmp_node = tmp_node->next_node;
  }
  return -1;
}

struct node *create_node(struct list *list, size_t data_size, void *data) {

  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  if (!new_node) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  if (list->copy != NULL) {
    new_node->data = list->copy(list, data);
  } else {
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    if (!new_node->data) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  }

  new_node->next_node = NULL;

  return new_node;
}

void addNode(struct list *list, size_t data_size, void *data) {
  struct node *new_node = list->create_node(list, data_size, data);
  if (!list->head) {
    list->tail = new_node;
    list->head = new_node;
  } else {
    list->tail->next_node = new_node;
    list->tail = new_node;
    list->tail->next_node = NULL;
  }
}

void free_list(struct list *list) {

  while (list->head) {

    struct node *next_node = list->head->next_node;
    if (list->free_special != NULL) {
      list->free_special(list->head->data);
      free(list->head);
    } else {
      free(list->head->data);
      free(list->head);
    }
    list->head = next_node;
  }
  list->head = NULL;
  list->tail = NULL;
}

int get_size(struct list *list) {
  int size = 0;
  struct node *tmp_node = list->head;

  while (tmp_node) {
    size++;
    tmp_node = tmp_node->next_node;
  }

  return size;
}

void add_front(struct list *list, void *data, size_t data_size) {
  struct node *new_node = list->create_node(list, data_size, data);
  new_node->next_node = list->head;
  if (!list->head) {
    list->tail = new_node;
  }
  list->head = new_node;
}

void insert_node(struct list *list, int index, void *data, size_t data_size) {

  if (index > list->get_size(list) || !list || index < 0) {
    return;
  }

  if (index == list->get_size(list)) {
    addNode(list, data_size, data);
    return;
  }

  if (index == 0) {
    add_front(list, data, data_size);
    return;
  }

  struct node *new_node = list->create_node(list, data_size, data);

  struct node *tmp_node = list->head;
  struct node *prev = NULL;
  int tmp_index = 0;
  while (tmp_node) {

    if (index == tmp_index) {
      if (!prev) {
        list->head = new_node;
      } else {
        new_node->next_node = prev->next_node;
        prev->next_node = new_node;
      }
      break;
    }

    prev = tmp_node;

    tmp_node = tmp_node->next_node;
    tmp_index++;
  }
}
void initialize_list(struct list **list, void *print_data, void *create_node_fn,
                     void *deep_copy, void *special_free, void *compare_func) {
  *list = malloc(sizeof(struct list));

  if (!*list) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  memset(*list, 0, sizeof(struct list));
  (*list)->head = NULL;
  (*list)->tail = NULL;
  printf("initializing list\n");
  (*list)->addNode = &addNode;
  (*list)->free_list = &free_list;
  (*list)->add_front = &add_front;
  (*list)->get_size = &get_size;
  (*list)->insert_node = &insert_node;
  (*list)->print = print_data;
  (*list)->print_list = &print_list;
  if (create_node_fn != NULL) {
    (*list)->create_node = create_node_fn;
  } else {
    (*list)->create_node = &create_node;
  }
  if (compare_func != NULL) {
    (*list)->compare = compare_func;
  } else {
    (*list)->compare = &compare;
  }
  (*list)->node_exists = &node_exists;
  (*list)->delete_node_at_index = &delete_node;
  (*list)->pop_front = &pop_front;
  (*list)->pop_back = &pop_back;
  (*list)->copy = deep_copy;
  (*list)->free_special = special_free;
}
struct node *create_node_str(struct list *list, size_t data_size, void *data) {
  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  if (!new_node) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  char *new_str = (char *)malloc(data_size);
  if (!new_str) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  strncpy(new_str, data, data_size);
  new_str[data_size - 1] = '\0';

  new_node->data = new_str;

  new_node->next_node = NULL;

  return new_node;
}
