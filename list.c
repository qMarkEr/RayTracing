#include "list.h"

node *__init(void *data, size_t size) {
  node *new = (node *)malloc(sizeof(node));
  new->content = malloc(size);
  memcpy(new->content, data, size);
  new->next = NULL;
  new->prev = NULL;
  return data ? new : NULL;
}

void append(list *lst, void *data, size_t size) {
  node *new = __init(data, size);
  if (lst->head == NULL) {  // init
    lst->head = new;
    lst->tail = lst->head;

  } else {  // push back
    node *prev_tail = lst->tail;
    lst->tail = new;
    lst->tail->prev = prev_tail;
    prev_tail->next = lst->tail;
  }
  lst->length++;
}

void list_print(list *lst, void (*prnt)(void *)) {
  node *cur = lst->head;
  while (cur != NULL) {
    (*prnt)(cur->content);
    putchar('\n');
    cur = cur->next;
  }
}

list *init_lst() {
  list *lst = (list *)malloc(sizeof(list));
  lst->head = NULL;
  lst->tail = NULL;
  lst->length = 0;
  return lst;
}

void destroy(list *lst) {
  if (lst && lst->length > 0) {
    while (lst->head != lst->tail) delete_element(lst, 0);
    delete_element(lst, 0);
  }
  free(lst);
}

node *__find(list *lst, int index) {  // [] operator
  int flag = OK;
  node *cur = NULL;
  if (index < 0 || index >= lst->length) flag = ERR_INDEX_OUT_OF_RANGE;

  if (flag == OK && index > lst->length / 2) {  // index after the middle
    cur = lst->tail;
    int i = lst->length - 1;
    while (i-- != index) cur = cur->prev;

  } else if (flag == OK) {  // index before the middle
    cur = lst->head;
    int i = 0;
    while (i++ != index) cur = cur->next;
  }
  return cur;
}

void delete_element(list *lst, int index) {
  if (index < 0) index += lst->length;
  if (lst && index == 0) {  // head case
    node *temp_head = lst->head;
    lst->head = temp_head->next;
    if (temp_head->content) free(temp_head->content);
    free(temp_head);

  } else if (lst && index == lst->length - 1) {  // tail case
    node *temp_tail = lst->tail;
    lst->tail = temp_tail->prev;
    if (temp_tail->content) free(temp_tail->content);
    free(temp_tail);

  } else if (lst && index > 0 && index < lst->length) {  // middle case
    node *cur = __find(lst, index);
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    if (cur->content) free(cur->content);
    free(cur);
  }
  lst->length--;
  if (lst->length == 0) lst->head = NULL, lst->tail = NULL;
}

void insert(list *lst, void *data, int index, size_t size) {
  if (lst && index == 0) {  // replace head
    node *new = __init(data, size);
    new->next = lst->head;
    lst->head->prev = new;
    lst->head = new;
    lst->length++;

  } else if (lst && index == lst->length - 1) {  // replace tail
    append(lst, data, size);
    lst->length++;

  } else if (lst && index > 0 && index < lst->length) {
    node *cur = __find(lst, index);
    node *new = __init(data, size);
    new->next = cur;
    new->prev = cur->prev;
    cur->prev->next = new;
    cur->prev = new;
    lst->length++;
  }
}

void *atIndex(list *lst, int index) {  // [] operator
  if (index < 0) index += lst->length;
  node *cur = __find(lst, index);
  return cur->content;
}
