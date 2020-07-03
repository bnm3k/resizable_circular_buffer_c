#include "../include/list.h"
#include "../include/unity.h"
#include <stdio.h>

void print_arr(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void setUp(void) {}
void tearDown(void) {}

void test_list_basics(void) {
    List *l = new_list();
    int capacity = l->capacity;
    TEST_ASSERT_EQUAL_INT(l->curr_size, 0);
    int arrA[] = {0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT_ARRAY(arrA, l->elements, capacity);

    /* insert first item from front */
    list_push_to_front(l, 100);
    TEST_ASSERT_EQUAL_INT(100, list_get_head(l));
    TEST_ASSERT_EQUAL_INT(1, l->curr_size);
    int arrB[] = {100, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT_ARRAY(arrB, l->elements, capacity);

    /* insert 2nd item from front */
    list_push_to_front(l, 200);
    TEST_ASSERT_EQUAL_INT(200, list_get_head(l));
    TEST_ASSERT_EQUAL_INT(2, l->curr_size);
    int arrC[] = {100, 0, 0, 0, 200};
    TEST_ASSERT_EQUAL_INT_ARRAY(arrC, l->elements, capacity);

    delete_list(l);
}

void test_list_basics_p2(void) {
    List *l = new_list();
    list_push_to_front(l, 200);
    list_push_to_back(l, 91);
    list_push_to_front(l, 300);
    list_push_to_back(l, 92);
    list_push_to_front(l, 400);
    list_push_to_back(l, 93);
    //   400-300-200-91-92-93
    int curr_list_elem = 0, i = 0;
    int arr[] = {400, 300, 200, 91, 92, 93};
    list_foreach(l, curr_list_elem, {
        TEST_ASSERT_EQUAL_INT(arr[i], curr_list_elem);
        i++;
    });
    delete_list(l);
}

void test_list_insert_100_items_from_back(void) {
    int *arr = malloc(sizeof(int) * 100);
    List *l = new_list();
    for (int i = 0; i < 100; i++) {
        list_push_to_back(l, i);
        arr[i] = i;
    }
    int curr_list_elem = 0, i = 0;
    list_foreach(l, curr_list_elem, {
        TEST_ASSERT_EQUAL_INT(arr[i], curr_list_elem);
        i++;
    });
    TEST_ASSERT_EQUAL_INT(100, l->curr_size);
    TEST_ASSERT_EQUAL_INT(0, list_get_head(l));
    free(arr);
    delete_list(l);
}

void test_list_insert_100_items_from_front(void) {
    int *arr = malloc(sizeof(int) * 100);
    List *l = new_list();
    for (int i = 0; i < 100; i++) {
        list_push_to_front(l, i);
        arr[i] = i;
    }

    int curr_list_elem = 0, i = 99;
    list_foreach(l, curr_list_elem, {
        TEST_ASSERT_EQUAL_INT(arr[i], curr_list_elem);
        i--;
    });

    i = 0;
    list_foreach_reverse(l, curr_list_elem, {
        TEST_ASSERT_EQUAL_INT(arr[i], curr_list_elem);
        i++;
    });
    TEST_ASSERT_EQUAL_INT(100, l->curr_size);
    TEST_ASSERT_EQUAL_INT(99, list_get_head(l));
    free(arr);
    delete_list(l);
}

void test_list_pop_items(void) {
    List *l = new_list();
    /* insert 20 items */
    for (int i = 1; i <= 20; i++) {
        list_push_to_back(l, i);
    }
    for (int i = 0; i < 10; i++)
        list_pop_from_back(l);
    TEST_ASSERT_EQUAL_INT(10, l->curr_size);
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int curr_elem, i = 0;
    list_foreach(l, curr_elem, {
        TEST_ASSERT_EQUAL_INT(arr1[i], curr_elem);
        i++;
    });

    for (int i = 0; i < 5; i++)
        list_pop_from_front(l);
    TEST_ASSERT_EQUAL_INT(5, l->curr_size);
    int arr2[] = {6, 7, 8, 9, 10};
    i = 0;
    list_foreach(l, curr_elem, {
        TEST_ASSERT_EQUAL_INT(arr2[i], curr_elem);
        i++;
    });

    delete_list(l);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_basics);
    RUN_TEST(test_list_basics_p2);
    RUN_TEST(test_list_insert_100_items_from_back);
    RUN_TEST(test_list_insert_100_items_from_front);
    RUN_TEST(test_list_pop_items);
    return UNITY_END();
}
