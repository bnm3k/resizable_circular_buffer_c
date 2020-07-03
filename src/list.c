#include "../include/list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 5
List *new_list() {
    List *l = malloc(sizeof(List));
    l->capacity = INIT_CAPACITY;
    l->curr_size = 0;
    l->elements = calloc(INIT_CAPACITY, sizeof(int));
    l->first = l->last = -1;
    return l;
}

void list_resize_up(List *l) {
    const int new_capacity = l->capacity * 2;
    int *new_elements = calloc(new_capacity, sizeof(int));
    int curr_elem, i = 0;
    list_foreach(l, curr_elem, {
        new_elements[i] = curr_elem;
        i++;
    });
    free(l->elements);
    l->first = 0;
    l->last = i - 1;
    l->capacity = new_capacity;
    l->elements = new_elements;
}

void delete_list(List *l) {
    free(l->elements);
    free(l);
}
void list_push_to_front(List *l, int v) {
    assert(l->curr_size <= l->capacity);
    /* check first if full */
    if (l->curr_size == l->capacity) list_resize_up(l);
    /* check if adding first item */
    if (l->curr_size == 0) {
        assert(l->first == -1);
        assert(l->last == -1);

        l->first = l->last = 0;
    } /* otherwise add as expected */
    else {
        l->first = MOD((l->first - 1), l->capacity);
    }
    assert(l->last >= 0);
    assert(l->first >= 0);
    l->curr_size++;
    l->elements[l->first] = v;
}
void list_push_to_back(List *l, int v) {
    assert(l->curr_size <= l->capacity);
    /* check first if full */
    if (l->curr_size == l->capacity) list_resize_up(l);
    /* check if adding first item */
    if (l->curr_size == 0) {
        assert(l->first == -1);
        assert(l->last == -1);
        l->first = l->last = 0;
    } /* otherwise add as expected */
    else {
        l->last = MOD((l->last + 1), l->capacity);
    }
    assert(l->last >= 0);
    assert(l->first >= 0);
    l->curr_size++;
    l->elements[l->last] = v;
}
int list_pop_from_front(List *l) {
    assert(l->curr_size <= l->capacity);
    int popped = l->elements[l->first];
    l->elements[l->first] = 0; /* clear pos. not necessary */
    l->first = MOD((l->first + 1), l->capacity);
    l->curr_size--;
    if (l->curr_size == 0) l->first = l->last = -1;
    return popped;
}
int list_pop_from_back(List *l) {
    assert(l->curr_size <= l->capacity);
    int popped = l->elements[l->last];
    l->elements[l->last] = 0; /* clear pos. not necessary */
    l->last = MOD((l->last - 1), l->capacity);
    l->curr_size--;
    if (l->curr_size == 0) l->first = l->last = -1;
    return popped;
}
int list_get_head(List *l) {
    return l->elements[l->first];
}
