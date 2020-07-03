#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

#define PRINT_INT(n) printf("%s = %d\n", #n, n)

typedef struct List {
    int *elements;
    int capacity, curr_size;
    int first, last;
} List;

List *new_list();
void delete_list(List *l);
void list_push_to_front(List *l, int v);
void list_push_to_back(List *l, int v);
int list_pop_from_front(List *l);
int list_pop_from_back(List *l);
int list_get_head(List *l);

#define MOD(a, n) a < 0 ? n - 1 : (a) % n

#define list_foreach(list, elem_var, code)      \
    {                                           \
        int pos = list->first;                  \
        while (1) {                             \
            elem_var = list->elements[pos];     \
            code;                               \
            if (pos == list->last) break;       \
            pos = MOD(pos + 1, list->capacity); \
        }                                       \
    }

#define list_foreach_reverse(list, elem_var, code) \
    {                                              \
        int pos = list->last;                      \
        while (1) {                                \
            elem_var = list->elements[pos];        \
            code;                                  \
            if (pos == list->first) break;         \
            pos = MOD(pos - 1, list->capacity);    \
        }                                          \
    }

#define list_get_count(list) list->curr_size

#endif
