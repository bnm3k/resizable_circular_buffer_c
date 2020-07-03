# Circular buffer
Simple, resizable circular buffer, currently only holds ints but will be made more generic in future. Not thread-safe.

## Tests
The tests use [unity](http://www.throwtheswitch.org/unity). To run the tests, run:
```bash
    make test
```

## Overview
The interface is pretty much straightforward. It's listed in `list.h`
```C
List *new_list();
void delete_list(List *l);
void list_push_to_front(List *l, int v);
void list_push_to_back(List *l, int v);
int list_pop_from_front(List *l);
int list_pop_from_back(List *l);
int list_get_head(List *l);
```
There are two additional 'functions' for iteration without mutation:
* list_foreach
* list_foreach_reverse  
  
They aren't function's per se, rather they are macros which abstract away the nitty-gritties of iteration. Credits go to attractivechaos's [khash](github.com/attractivechaos/klib/blob/master/khash.h) from where I got the idea of using macros in this way rather than taking in a function pointer, or returning an OOP-like iterator object. For example, the `list_foreach` is defined as follows:
```C
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
```
The internals don't matter. `list_foreach` is then used as follows:
```C
int main(){
    // setup list
    List *l = new_list();
    for (int i = 0; i < 100; i++) {
        list_push_to_back(l, i);
    }

    // iterate
    list_foreach(l, curr_list_elem, {
        printf("n = %d", curr_list_elem)
    });

    // cleanup list
    delete_list(l);
}
```