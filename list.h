#ifndef TITLED_LIST_H
#define TITLED_LIST_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MISSING_INDEX (-1)
#define OK 0
#define ERR_INDEX_OUT_OF_RANGE 1

typedef struct Node {
  struct Node *prev;
  struct Node *next;
  void *content;
} node;

typedef struct List {
  node *head;
  node *tail;
  int length;
} list;

node *__init(void *data, size_t size);
list *init_lst();
void append(list *lst, void *data, size_t size);
void list_print(list *lst, void (*prnt)(void *));
void insert(list *lst, void *data, int index, size_t size);
node *__find(list *lst, int index);
void delete_element(list *lst, int index);
void destroy(list *lst);
void *atIndex(list *lst, int index);

#endif
