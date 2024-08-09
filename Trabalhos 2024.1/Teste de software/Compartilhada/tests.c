#include "tests.h"
#include "lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define ASSERT_CC_ERR_ALLOC(x) ASSERT_EQ(x, CC_ERR_ALLOC)
#define ASSERT_CC_ERR_INVALID_CAPACITY(x) ASSERT_EQ(x, CC_ERR_INVALID_CAPACITY)
#define ASSERT_CC_ERR_INVALID_RANGE(x) ASSERT_EQ(x, CC_ERR_INVALID_RANGE)
#define ASSERT_CC_ERR_MAX_CAPACITY(x) ASSERT_EQ(x, CC_ERR_MAX_CAPACITY)
#define ASSERT_CC_ERR_KEY_NOT_FOUND(x) ASSERT_EQ(x, CC_ERR_KEY_NOT_FOUND)
#define ASSERT_CC_ERR_VALUE_NOT_FOUND(x) ASSERT_EQ(x, CC_ERR_VALUE_NOT_FOUND)
#define ASSERT_CC_ERR_OUT_OF_RANGE(x) ASSERT_EQ(x, CC_ERR_OUT_OF_RANGE)
#define ASSERT_CC_ITER_END(x) ASSERT_EQ(x, CC_ITER_END)

bool test_add() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 4]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 5))
    ASSERT_EQ(5, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 6))
    ASSERT_EQ(6, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5, 6]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 7))
    ASSERT_EQ(7, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5, 6, 7]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 8))
    ASSERT_EQ(8, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5, 6, 7, 8]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 9))
    ASSERT_EQ(9, cc_array_size(arr))
    ASSERT_EQ(16, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5, 6, 7, 8, 9]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(10, cc_array_size(arr))
    ASSERT_EQ(16, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 11))
    ASSERT_EQ(11, cc_array_size(arr))
    ASSERT_EQ(16, cc_array_capacity(arr))
    //[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(4, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 4, &get_result))
    ASSERT_EQ(5, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 5, &get_result))
    ASSERT_EQ(6, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 6, &get_result))
    ASSERT_EQ(7, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 7, &get_result))
    ASSERT_EQ(8, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 8, &get_result))
    ASSERT_EQ(9, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 9, &get_result))
    ASSERT_EQ(10, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 10, &get_result))
    ASSERT_EQ(11, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_add_at() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_add_at(arr, (void*) 1, -1))
    ASSERT_EQ(0, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_add_at(arr, (void*) 1, 1))
    ASSERT_EQ(0, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 1, 0))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_add_at(arr, (void*) 2, 2))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 2, 1))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 3, 0))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[3, 1, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 4, 0))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[4, 3, 1, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 5, 1))
    ASSERT_EQ(5, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[4, 5, 3, 1, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 6, 4))
    ASSERT_EQ(6, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[4, 5, 3, 1, 6, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 7, 3))
    ASSERT_EQ(7, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[4, 5, 3, 7, 1, 6, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 8, 2))
    ASSERT_EQ(8, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[4, 5, 8, 3, 7, 1, 6, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 9, 5))
    ASSERT_EQ(9, cc_array_size(arr))
    ASSERT_EQ(16, cc_array_capacity(arr))
    //[4, 5, 8, 3, 7, 9, 1, 6, 2]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 10, 9))
    ASSERT_EQ(10, cc_array_size(arr))
    ASSERT_EQ(16, cc_array_capacity(arr))
    //[4, 5, 8, 3, 7, 9, 1, 6, 2, 10]

    ASSERT_CC_OK(cc_array_add_at(arr, (void*) 11, 3))
    ASSERT_EQ(11, cc_array_size(arr))
    ASSERT_EQ(16, cc_array_capacity(arr))
    //[4, 5, 8, 11, 3, 7, 9, 1, 6, 2, 10]

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(4, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(5, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(8, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(11, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 4, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 5, &get_result))
    ASSERT_EQ(7, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 6, &get_result))
    ASSERT_EQ(9, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 7, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 8, &get_result))
    ASSERT_EQ(6, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 9, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 10, &get_result))
    ASSERT_EQ(10, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_replace_at() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    void* get_result;
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_replace_at(arr, (void*) 1, 0, &get_result))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_replace_at(arr, (void*) 1, 1, &get_result))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_replace_at(arr, (void*) 1, 4, &get_result))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_replace_at(arr, (void*) 1, 5, &get_result))

    ASSERT_CC_OK(cc_array_replace_at(arr, (void*) 5, 2, NULL)) //[1, 2, 5, 4]
    ASSERT_CC_OK(cc_array_replace_at(arr, (void*) 6, 0, &get_result)) //[6, 2, 5, 4]
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_replace_at(arr, (void*) 7, 3, NULL)) //[6, 2, 5, 7]

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(6, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(5, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(7, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_swap_at() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 3, 4))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 3, 5))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 4, 3))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 4, 4))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 4, 5))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 5, 3))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 5, 4))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_swap_at(arr, 5, 5))

    ASSERT_CC_OK(cc_array_swap_at(arr, 0, 3)) //[4, 2, 3, 1]
    ASSERT_CC_OK(cc_array_swap_at(arr, 1, 2)) //[4, 3, 2, 1]
    ASSERT_CC_OK(cc_array_swap_at(arr, 3, 2)) //[4, 1, 3, 2]
    ASSERT_CC_OK(cc_array_swap_at(arr, 2, 0)) //[3, 1, 4, 2]

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(4, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(2, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_remove() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_remove(arr, (void*) 0, NULL))
    ASSERT_EQ(0, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    void* get_result;
    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_remove(arr, (void*) 5, &get_result))
    ASSERT_EQ(4, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_remove(arr, (void*) 2, NULL)) //[1, 3, 4]
    ASSERT_EQ(3, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(4, (int) get_result)

    ASSERT_CC_OK(cc_array_remove(arr, (void*) 4, &get_result)) //[1, 3]
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(4, (int) get_result)

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(3, (int) get_result)

    ASSERT_CC_OK(cc_array_remove(arr, (void*) 1, &get_result)) //[3]
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(1, (int) get_result)

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(3, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_remove_at() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_remove_at(arr, 0, NULL))
    ASSERT_EQ(0, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    void* get_result;
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_remove_at(arr, 4, NULL))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_remove_at(arr, 5, &get_result))
    ASSERT_EQ(4, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_remove_at(arr, 1, NULL)) //[1, 3, 4]
    ASSERT_EQ(3, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(4, (int) get_result)

    ASSERT_CC_OK(cc_array_remove_at(arr, 2, &get_result)) //[1, 3]
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(4, (int) get_result)


    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_last(arr, &get_result))
    ASSERT_EQ(3, (int) get_result)


    ASSERT_CC_OK(cc_array_remove_at(arr, 0, &get_result)) //[3]
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(1, (int) get_result)

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(3, (int) get_result)


    cc_array_destroy(arr);
    return true;
}

bool test_remove_last() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_remove_last(arr, NULL))
    ASSERT_EQ(0, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    void* get_result;
    ASSERT_CC_OK(cc_array_remove_last(arr, NULL)) //[1, 2, 3]
    ASSERT_EQ(3, cc_array_size(arr))

    ASSERT_CC_OK(cc_array_remove_last(arr, &get_result)) //[1, 2]
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(3, (int) get_result)

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_remove_all(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    //[1]

    cc_array_remove_all(arr);
    ASSERT_EQ(0, cc_array_size(arr))

    cc_array_destroy(arr);
    return true;
}

bool test_remove_all_free(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    //[1]

    cc_array_remove_all_free(arr);
    ASSERT_EQ(0, cc_array_size(arr))

    cc_array_destroy(arr);
    return true;
}

bool test_get_at(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    //[1, 2]

    void* get_result;
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_get_at(arr, 2, &get_result))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_get_at(arr, 3, &get_result))

    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_get_last(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    void* get_result;
    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_get_last(arr, &get_result))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1)) //[1]

    ASSERT_CC_OK(cc_array_get_last(arr, &get_result))
    ASSERT_EQ(1, (int) get_result)

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2)) //[1, 2]

    ASSERT_CC_OK(cc_array_get_last(arr, &get_result))
    ASSERT_EQ(2, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_subarray(){
    CC_Array* arr;
    CC_Array* subarr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 3, 2, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 3, 4, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 3, 5, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 4, 3, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 4, 4, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 4, 5, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 5, 3, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 5, 4, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 5, 5, &subarr))
    ASSERT_CC_ERR_INVALID_RANGE(cc_array_subarray(arr, 6, 5, &subarr))

    ASSERT_CC_OK(cc_array_subarray(arr, 2, 3, &subarr)) //[3, 4]
    ASSERT_EQ(2, cc_array_size(subarr))
    ASSERT_EQ(2, cc_array_capacity(subarr))

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(subarr, 0, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(subarr, 1, &get_result))
    ASSERT_EQ(4, (int) get_result)

    ASSERT_CC_OK(cc_array_subarray(arr, 1, 1, &subarr)) //[2]
    ASSERT_EQ(1, cc_array_size(subarr))
    ASSERT_EQ(1, cc_array_capacity(subarr))

    ASSERT_CC_OK(cc_array_get_at(subarr, 0, &get_result))
    ASSERT_EQ(2, (int) get_result)

    ASSERT_CC_OK(cc_array_subarray(arr, 3, 3, &subarr)) //[4]
    ASSERT_EQ(1, cc_array_size(subarr))
    ASSERT_EQ(1, cc_array_capacity(subarr))

    ASSERT_CC_OK(cc_array_get_at(subarr, 0, &get_result))
    ASSERT_EQ(4, (int) get_result)

    ASSERT_CC_OK(cc_array_subarray(arr, 0, 3, &subarr)) //[1, 2, 3, 4]
    ASSERT_EQ(4, cc_array_size(subarr))
    ASSERT_EQ(4, cc_array_capacity(subarr))

    ASSERT_CC_OK(cc_array_get_at(subarr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(subarr, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(subarr, 2, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(subarr, 3, &get_result))
    ASSERT_EQ(4, (int) get_result)


    cc_array_destroy(arr);
    return true;
}

bool test_copy_shallow(){
    CC_Array* arr;
    CC_Array* copy;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_OK(cc_array_copy_shallow(arr, &copy)) //[1, 2, 3, 4]
    ASSERT_EQ(4, cc_array_size(copy))
    ASSERT_EQ(8, cc_array_capacity(copy))

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(copy, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(copy, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(copy, 2, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(copy, 3, &get_result))
    ASSERT_EQ(4, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

void* copy_func(void* element){
    return (void*) ((unsigned long long) element << 1);
}

bool test_copy_deep(){
    CC_Array* arr;
    CC_Array* copy;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_OK(cc_array_copy_deep(arr, copy_func, &copy)) //[2, 4, 6, 8]
    ASSERT_EQ(4, cc_array_size(copy))
    ASSERT_EQ(8, cc_array_capacity(copy))

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(copy, 0, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(copy, 1, &get_result))
    ASSERT_EQ(4, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(copy, 2, &get_result))
    ASSERT_EQ(6, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(copy, 3, &get_result))
    ASSERT_EQ(8, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_reverse(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    cc_array_reverse(arr);
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    cc_array_reverse(arr); //[4, 3, 2, 1]

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(4, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(1, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_trim_capacity(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    cc_array_reverse(arr);
    //[]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_OK(cc_array_trim_capacity(arr))
    ASSERT_EQ(4, cc_array_capacity(arr))

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(4, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_contains(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    size_t result = cc_array_contains(arr, (void*) 1);
    ASSERT_EQ(0, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    // 1: 4x | 2: 3x | 3: 2x | 4: 1x
    //[1, 2, 1, 3, 1, 1, 2, 3, 4, 2]

    result = cc_array_contains(arr, (void*) 0);
    ASSERT_EQ(0, result);
    result = cc_array_contains(arr, (void*) 1);
    ASSERT_EQ(4, result);
    result = cc_array_contains(arr, (void*) 2);
    ASSERT_EQ(3, result);
    result = cc_array_contains(arr, (void*) 3);
    ASSERT_EQ(2, result);
    result = cc_array_contains(arr, (void*) 4);
    ASSERT_EQ(1, result);
    result = cc_array_contains(arr, (void*) 5);
    ASSERT_EQ(0, result);

    cc_array_destroy(arr);
    return true;
}

int contains_value_comp(const void* element, const void* value){
    return ((int) element * 2) + 1 != (int) value;
}

bool test_contains_value(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    size_t result = cc_array_contains_value(arr, (void*) 1, contains_value_comp);
    ASSERT_EQ(0, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    // 1: 4x | 2: 3x | 3: 2x | 4: 1x
    //[1, 2, 1, 3, 1, 1, 2, 3, 4, 2]

    result = cc_array_contains_value(arr, (void*) 1, contains_value_comp);
    ASSERT_EQ(0, result);
    result = cc_array_contains_value(arr, (void*) 3, contains_value_comp);
    ASSERT_EQ(4, result);
    result = cc_array_contains_value(arr, (void*) 5, contains_value_comp);
    ASSERT_EQ(3, result);
    result = cc_array_contains_value(arr, (void*) 7, contains_value_comp);
    ASSERT_EQ(2, result);
    result = cc_array_contains_value(arr, (void*) 9, contains_value_comp);
    ASSERT_EQ(1, result);
    result = cc_array_contains_value(arr, (void*) 11, contains_value_comp);
    ASSERT_EQ(0, result);

    cc_array_destroy(arr);
    return true;
}

bool test_index_of(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    size_t get_result;
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_index_of(arr, (void*) 1, &get_result))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    //[1, 2, 3, 4]

    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_index_of(arr, (void*) 0, &get_result))
    ASSERT_CC_OK(cc_array_index_of(arr, (void*) 1, &get_result))
    ASSERT_EQ(0, get_result)
    ASSERT_CC_OK(cc_array_index_of(arr, (void*) 2, &get_result))
    ASSERT_EQ(1, get_result)
    ASSERT_CC_OK(cc_array_index_of(arr, (void*) 3, &get_result))
    ASSERT_EQ(2, get_result)
    ASSERT_CC_OK(cc_array_index_of(arr, (void*) 4, &get_result))
    ASSERT_EQ(3, get_result)
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_index_of(arr, (void*) 5, &get_result))

    cc_array_destroy(arr);
    return true;
}

int sort_comp(const void* lhs, const void* rhs){
    return *(int*) lhs - *(int*) rhs;
}

bool test_sort(){
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]

    size_t result = cc_array_contains(arr, (void*) 1);
    ASSERT_EQ(0, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    // 1: 3x | 2: 1x | 3: 2x | 4: 1x
    //[2, 1, 4, 3, 1, 1, 3, 2]

    cc_array_sort(arr, sort_comp);
    //[1, 1, 1, 2, 3, 3, 4]

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(arr, 0, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 1, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 2, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 3, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 4, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 5, &get_result))
    ASSERT_EQ(3, (int) get_result)
    ASSERT_CC_OK(cc_array_get_at(arr, 6, &get_result))
    ASSERT_EQ(4, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

void sum(void *a, void *b, void *result) {
    if(b == NULL) {
        *(int*)result = (int) a;
    } else if(a == result) { //Verifica se *a deve ser tratado como um valor do array ou se deve ser tratado como o ponteiro (*result)
        *(int*)result = (*(int*)a + (int)b);
    } else {
        *(int*)result = ((int) a + (int) b);
    }
    *(int*)result = *(int*)result + 1;
}

bool test_reduce() {
    CC_Array* arr;
    int result = 0;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]
    cc_array_reduce(arr, &sum, (void *) &result);
    ASSERT_EQ(0, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]
    cc_array_reduce(arr, &sum, (void *) &result);
    ASSERT_EQ(2, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]
    result = 0;
    cc_array_reduce(arr, &sum, (void *) &result);
    ASSERT_EQ(4, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]
    result = 0;
    cc_array_reduce(arr, &sum, (void *) &result);
    ASSERT_EQ(8, result);

    ASSERT_CC_OK(cc_array_add(arr, (void*) 4))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 4]
    result = 0;
    cc_array_reduce(arr, &sum, (void *) &result);
    ASSERT_EQ(13, result);

    cc_array_destroy(arr);
    return true;
}

bool inList(const void *a) {
    for(int i = 0; i < 10; i++) {
        if((int) a == i) {
            return true;
        }
    }

    return false;
}

bool test_filter_mut() {
    CC_Array* arr;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_filter_mut(arr, &inList))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 10]

    ASSERT_CC_OK(cc_array_filter_mut(arr, &inList))
    ASSERT_EQ(3, cc_array_size(arr))

    cc_array_destroy(arr);
    return true;
}

bool test_filter() {
    CC_Array* arr, *ar2;

    ASSERT_CC_OK(cc_array_new(&arr))
    //[]
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_filter(arr, &inList, &ar2))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 10]

    ASSERT_CC_OK(cc_array_filter(arr, &inList, &ar2))
    ASSERT_EQ(3, cc_array_size(ar2))
    ASSERT_EQ(4, cc_array_size(arr))

    cc_array_destroy(arr);
    return true;
}

bool test_iter_init() {
    CC_Array* arr;
    CC_ArrayIter ariter;

    ASSERT_CC_OK(cc_array_new(&arr))
    cc_array_iter_init(&ariter, arr);
    ASSERT_EQ(-1, (int) cc_array_iter_index(&ariter))

    cc_array_destroy(arr);
    return true;
}

bool test_iter_next() {
    CC_Array* arr;
    CC_ArrayIter ariter;

    ASSERT_CC_OK(cc_array_new(&arr))
    cc_array_iter_init(&ariter, arr);

    void* get_result;
    ASSERT_CC_ITER_END(cc_array_iter_next(&ariter, &get_result));

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 10]

    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(1, (int) get_result);
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(2, (int) get_result);
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(3, (int) get_result);
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(10, (int) get_result);

    cc_array_destroy(arr);
    return true;
}

bool test_iter_remove() {
    CC_Array* arr;
    CC_ArrayIter ariter;

    ASSERT_CC_OK(cc_array_new(&arr))
    cc_array_iter_init(&ariter, arr);

    void* get_result;
    ASSERT_CC_ITER_END(cc_array_iter_next(&ariter, &get_result))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 10]

    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(2, (int) get_result)

    ASSERT_CC_OK(cc_array_iter_remove(&ariter, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_iter_remove(&ariter, &get_result))

    cc_array_destroy(arr);
    return true;
}

bool test_iter_add() {
    CC_Array* arr;
    CC_ArrayIter ariter;

    ASSERT_CC_OK(cc_array_new(&arr))
    cc_array_iter_init(&ariter, arr);

    void* get_result;
    ASSERT_CC_ITER_END(cc_array_iter_next(&ariter, &get_result))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 10]

    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(2, (int) get_result)

    ASSERT_CC_OK(cc_array_iter_add(&ariter, (void *) 5))

    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(3, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_iter_replace() {
    CC_Array* arr;
    CC_ArrayIter ariter;

    ASSERT_CC_OK(cc_array_new(&arr))
    cc_array_iter_init(&ariter, arr);

    void* get_result;
    ASSERT_CC_ITER_END(cc_array_iter_next(&ariter, &get_result))

    ASSERT_CC_OK(cc_array_add(arr, (void*) 1))
    ASSERT_EQ(1, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 2))
    ASSERT_EQ(2, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 3))
    ASSERT_EQ(3, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3]

    ASSERT_CC_OK(cc_array_add(arr, (void*) 10))
    ASSERT_EQ(4, cc_array_size(arr))
    ASSERT_EQ(8, cc_array_capacity(arr))
    //[1, 2, 3, 10]

    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(1, (int) get_result)
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(2, (int) get_result)
    ASSERT_CC_OK(cc_array_iter_next(&ariter, &get_result))
    ASSERT_EQ(3, (int) get_result)

    ASSERT_CC_OK(cc_array_iter_replace(&ariter, (void *) 5, &get_result))
    ASSERT_EQ(3, (int) get_result)

    cc_array_destroy(arr);
    return true;
}

bool test_zip_iter_init() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter arzip;

    ASSERT_CC_OK(cc_array_new(&ar1))
    ASSERT_CC_OK(cc_array_new(&ar2))

    cc_array_zip_iter_init(&arzip, ar1, ar2);
    ASSERT_EQ(-1, (int) cc_array_zip_iter_index(&arzip))

    cc_array_destroy(ar1);
    cc_array_destroy(ar2);
    return true;
}

bool test_zip_iter_next() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter arzip;

    ASSERT_CC_OK(cc_array_new(&ar1))
    ASSERT_CC_OK(cc_array_new(&ar2))

    cc_array_zip_iter_init(&arzip, ar1, ar2);
    ASSERT_EQ(-1, (int) cc_array_zip_iter_index(&arzip))

    void *r1, *r2;
    ASSERT_CC_ITER_END(cc_array_zip_iter_next(&arzip, &r1, &r2))

    ASSERT_CC_OK(cc_array_add(ar1, (void*) 1))
    ASSERT_EQ(1, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 2))
    ASSERT_EQ(2, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 3))
    ASSERT_EQ(3, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2, 3]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 4))
    ASSERT_EQ(4, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2, 3, 4]

    ASSERT_CC_ITER_END(cc_array_zip_iter_next(&arzip, &r1, &r2))

    ASSERT_CC_OK(cc_array_add(ar2, (void*) 2))
    ASSERT_EQ(1, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 3))
    ASSERT_EQ(2, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 4))
    ASSERT_EQ(3, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 5))
    ASSERT_EQ(4, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4, 5]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 6))
    ASSERT_EQ(5, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4, 5, 6]

    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(1, (int) r1)
    ASSERT_EQ(2, (int) r2)
    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(2, (int) r1)
    ASSERT_EQ(3, (int) r2)
    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(3, (int) r1)
    ASSERT_EQ(4, (int) r2)
    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(4, (int) r1)
    ASSERT_EQ(5, (int) r2)
    ASSERT_CC_ITER_END(cc_array_zip_iter_next(&arzip, &r1, &r2))

    cc_array_destroy(ar1);
    cc_array_destroy(ar2);
    return true;
}

bool test_zip_iter_remove() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter arzip;

    ASSERT_CC_OK(cc_array_new(&ar1))
    ASSERT_CC_OK(cc_array_new(&ar2))

    cc_array_zip_iter_init(&arzip, ar1, ar2);
    ASSERT_EQ(-1, (int) cc_array_zip_iter_index(&arzip))

    void *r1, *r2;

    ASSERT_CC_OK(cc_array_add(ar1, (void*) 1))
    ASSERT_EQ(1, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 2))
    ASSERT_EQ(2, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 3))
    ASSERT_EQ(3, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2, 3]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 4))
    ASSERT_EQ(4, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2, 3, 4]

    ASSERT_CC_OK(cc_array_add(ar2, (void*) 2))
    ASSERT_EQ(1, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 3))
    ASSERT_EQ(2, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 4))
    ASSERT_EQ(3, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 5))
    ASSERT_EQ(4, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4, 5]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 6))
    ASSERT_EQ(5, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4, 5, 6]

    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(1, (int) r1)
    ASSERT_EQ(2, (int) r2)

    ASSERT_CC_OK(cc_array_zip_iter_remove(&arzip, &r1, &r2))
    ASSERT_EQ(1, (int) r1)
    ASSERT_EQ(2, (int) r2)
    //[2, 3, 4]
    //    ^
    //[3, 4, 5, 6]
    //    ^

    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(3, (int) r1)
    ASSERT_EQ(4, (int) r2)
    //[2, 3, 4]
    //       ^
    //[3, 4, 5, 6]
    //       ^

    ASSERT_CC_OK(cc_array_zip_iter_remove(&arzip, &r1, &r2))
    ASSERT_EQ(3, (int) r1)
    ASSERT_EQ(4, (int) r2)
    //[2, 4]
    //       ^
    //[3, 5, 6]
    //       ^

    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[4]
    //       ^
    //[3, 5, 6]
    //       ^

    ASSERT_CC_OK(cc_array_remove_at(ar2, 1, NULL))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[4]
    //       ^
    //[3, 6]
    //       ^

    ASSERT_CC_OK(cc_array_remove_at(ar2, 1, NULL))
    //[4]
    //       ^
    //[3]
    //       ^
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))

    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[]
    //       ^
    //[]
    //       ^
    ASSERT_CC_OK(cc_array_add(ar1, (void *) 1))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1, 2]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1, 2]
    //       ^
    //[2]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 3))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1, 2, 3]
    //       ^
    //[2]
    //       ^
    ASSERT_CC_OK(cc_array_add(ar2, (void *) 3))
    //[1, 2, 3]
    //       ^
    //[2, 3]
    //       ^
    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_zip_iter_remove(&arzip, &r1, &r2))

    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 1))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1, 2]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1, 2]
    //       ^
    //[2]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 3))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_remove(&arzip, NULL, NULL))
    //[1, 2, 3]
    //       ^
    //[2]
    //       ^
    ASSERT_CC_OK(cc_array_add(ar1, (void *) 3))
    //[1, 2, 3]
    //       ^
    //[2, 3]
    //       ^
    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_zip_iter_remove(&arzip, &r1, &r2))

    cc_array_destroy(ar1);
    cc_array_destroy(ar2);
    return true;
}

bool test_zip_iter_add() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter arzip;

    ASSERT_CC_OK(cc_array_new(&ar1))
    ASSERT_CC_OK(cc_array_new(&ar2))

    cc_array_zip_iter_init(&arzip, ar1, ar2);
    ASSERT_EQ(-1, (int) cc_array_zip_iter_index(&arzip))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 1, (void *) 10))
    ASSERT_EQ(0, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(1, cc_array_size(ar1))
    ASSERT_EQ(1, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))


    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 2, (void *) 9))
    ASSERT_EQ(1, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(2, cc_array_size(ar1))
    ASSERT_EQ(2, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 3, (void *) 8))
    ASSERT_EQ(2, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(3, cc_array_size(ar1))
    ASSERT_EQ(3, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 4, (void *) 7))
    ASSERT_EQ(3, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(4, cc_array_size(ar1))
    ASSERT_EQ(4, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 5, (void *) 6))
    ASSERT_EQ(4, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(5, cc_array_size(ar1))
    ASSERT_EQ(5, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 6, (void *) 5))
    ASSERT_EQ(5, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(6, cc_array_size(ar1))
    ASSERT_EQ(6, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 7, (void *) 4))
    ASSERT_EQ(6, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(7, cc_array_size(ar1))
    ASSERT_EQ(7, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 8, (void *) 3))
    ASSERT_EQ(7, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(8, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 9, (void *) 2))
    ASSERT_EQ(8, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(9, cc_array_size(ar1))
    ASSERT_EQ(9, cc_array_size(ar2))
    ASSERT_EQ(16, cc_array_capacity(ar1))
    ASSERT_EQ(16, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 10, (void *) 1))
    ASSERT_EQ(9, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(10, cc_array_size(ar1))
    ASSERT_EQ(10, cc_array_size(ar2))
    ASSERT_EQ(16, cc_array_capacity(ar1))
    ASSERT_EQ(16, cc_array_capacity(ar2))

    ASSERT_CC_OK(cc_array_zip_iter_add(&arzip, (void *) 11, (void *) 0))
    ASSERT_EQ(10, cc_array_zip_iter_index(&arzip))
    ASSERT_EQ(11, cc_array_size(ar1))
    ASSERT_EQ(11, cc_array_size(ar2))
    ASSERT_EQ(16, cc_array_capacity(ar1))
    ASSERT_EQ(16, cc_array_capacity(ar2))
    //[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
    //                                    ^
    //[10, 9, 8, 7, 6, 5, 4, 3, 2, 1,  0]
    //                                    ^

    cc_array_destroy(ar1);
    cc_array_destroy(ar2);
    return true;
}

bool test_zip_iter_replace() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter arzip;

    ASSERT_CC_OK(cc_array_new(&ar1))
    ASSERT_CC_OK(cc_array_new(&ar2))

    cc_array_zip_iter_init(&arzip, ar1, ar2);
    ASSERT_EQ(-1, (int) cc_array_zip_iter_index(&arzip))

    void *r1, *r2;

    ASSERT_CC_OK(cc_array_add(ar1, (void*) 1))
    ASSERT_EQ(1, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 2))
    ASSERT_EQ(2, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 3))
    ASSERT_EQ(3, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2, 3]
    ASSERT_CC_OK(cc_array_add(ar1, (void*) 4))
    ASSERT_EQ(4, cc_array_size(ar1))
    ASSERT_EQ(8, cc_array_capacity(ar1))
    //[1, 2, 3, 4]

    ASSERT_CC_OK(cc_array_add(ar2, (void*) 2))
    ASSERT_EQ(1, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 3))
    ASSERT_EQ(2, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 4))
    ASSERT_EQ(3, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 5))
    ASSERT_EQ(4, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4, 5]
    ASSERT_CC_OK(cc_array_add(ar2, (void*) 6))
    ASSERT_EQ(5, cc_array_size(ar2))
    ASSERT_EQ(8, cc_array_capacity(ar2))
    //[2, 3, 4, 5, 6]

    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(1, (int) r1)
    ASSERT_EQ(2, (int) r2)

    ASSERT_CC_OK(cc_array_zip_iter_remove(&arzip, &r1, &r2))
    ASSERT_EQ(1, (int) r1)
    ASSERT_EQ(2, (int) r2)
    //[2, 3, 4]
    //    ^
    //[3, 4, 5, 6]
    //    ^

    ASSERT_CC_OK(cc_array_zip_iter_next(&arzip, &r1, &r2))
    ASSERT_EQ(3, (int) r1)
    ASSERT_EQ(4, (int) r2)
    //[2, 3, 4]
    //       ^
    //[3, 4, 5, 6]
    //       ^

    ASSERT_CC_OK(cc_array_zip_iter_remove(&arzip, &r1, &r2))
    ASSERT_EQ(3, (int) r1)
    ASSERT_EQ(4, (int) r2)
    //[3, 4]
    //       ^
    //[4, 5, 6]
    //       ^
    ASSERT_CC_OK(cc_array_zip_iter_replace(&arzip, (void *) 10, (void *) 11, &r1, &r2))
    ASSERT_EQ(4, (int) r1)
    ASSERT_EQ(5, (int) r2)

    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 1))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1, 2]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1, 2]
    //       ^
    //[2]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 3))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1, 2, 3]
    //       ^
    //[2]
    //       ^
    ASSERT_CC_OK(cc_array_add(ar2, (void *) 3))
    //[1, 2, 3]
    //       ^
    //[2, 3]
    //       ^
    ASSERT_CC_OK(cc_array_zip_iter_replace(&arzip, (void *) 3, (void *) 4, NULL, NULL))

    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar1, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))
    ASSERT_CC_OK(cc_array_remove_at(ar2, 0, NULL))

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 1))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1, 2]
    //       ^
    //[]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar1, (void *) 2))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1, 2]
    //       ^
    //[2]
    //       ^

    ASSERT_CC_OK(cc_array_add(ar2, (void *) 3))
    ASSERT_CC_ERR_OUT_OF_RANGE(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, NULL, NULL))
    //[1, 2, 3]
    //       ^
    //[2]
    //       ^
    ASSERT_CC_OK(cc_array_add(ar1, (void *) 3))
    //[1, 2, 3]
    //       ^
    //[2, 3]
    //       ^
    ASSERT_CC_ERR_VALUE_NOT_FOUND(cc_array_zip_iter_replace(&arzip, (void *) 1, (void *) 2, &r1, &r2))

    cc_array_destroy(ar1);
    cc_array_destroy(ar2);
    return true;
}

test_t TESTS[] = {
    &test_add,
    &test_add_at,
    &test_replace_at,
    &test_swap_at,
    &test_remove,
    &test_remove_at,
    &test_remove_last,
    &test_remove_all,
    &test_remove_all_free,
    &test_get_at,
    &test_get_last,
    &test_subarray,
    &test_copy_shallow,
    &test_copy_deep,
    &test_reverse,
    &test_trim_capacity,
    &test_contains,
    &test_contains_value,
    &test_index_of,
    &test_sort,
    &test_reduce,
    &test_filter_mut,
    &test_filter,
    &test_iter_init,
    &test_iter_next,
    &test_iter_remove,
    &test_iter_add,
    &test_iter_replace,
    &test_zip_iter_init,
    &test_zip_iter_next,
    &test_zip_iter_remove,
    &test_zip_iter_add,
    &test_zip_iter_replace,
    NULL
};
