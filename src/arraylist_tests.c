#include "arraylist_tests.h"

int test_create() {
    arraylist_t *arraylist = create_arraylist(0);
    if (arraylist != NULL) {
        fprintf(stderr, "TEST_CREATE failed. Capacity of 0 should not be allowed");
        return FAILURE;
    } else {
        free(arraylist);
    }

    arraylist_t *arraylist2 = create_arraylist(4);
    if (arraylist2 == NULL) {
        fprintf(stderr, "TEST_CREATE failed. An array list of a correct capacity could not be created");
        return FAILURE;
    } else if (arraylist2->backing_array == NULL){
        fprintf(stderr, "TEST_CREATE failed. An array list of a correct capacity could not be created");
        free(arraylist2);
        return FAILURE;
    } else {
        free(arraylist2->backing_array);
        free(arraylist2);
    }

    return SUCCESS;
}

int test_append()
{
    arraylist_t *arraylist = create_arraylist(1);
    for (int i = 0; i < 100; i++)
    {
        char *buff = (char *)malloc(sizeof(char) * 4);
        sprintf(buff, "%d", i);
        append(arraylist, buff);
        if (atoi(arraylist->backing_array[i]) != i)
        {
            fprintf(stderr, "TEST_APPEND failed. Element appended is incorrect");
            return FAILURE;
        }
    }
    for (int i = 0; i < 100; i++)
    {
        free(arraylist->backing_array[i]);
    }
    destroy(arraylist);
    return SUCCESS;
}

int test_add_at_index()
{
    arraylist_t *arraylist = create_arraylist(1);

    // Same as test_append to create an arraylist
    for (int i = 0; i < 100; i++)
    {
        char *buff = (char *)malloc(sizeof(char) * 4);
        sprintf(buff, "%d", i);
        append(arraylist, buff);
        if (atoi(arraylist->backing_array[i]) != i)
        {
            fprintf(stderr, "TEST_ADD_AT_INDEX failed. Check append method");
            return FAILURE;
        }
    }
    for (int i = 0; i < 100; i += 2)
    {
        char *buff = (char *)malloc(sizeof(char) * 4);
        sprintf(buff, "%d", i);
        add_at_index(arraylist, buff, i);
        if (atoi(arraylist->backing_array[i]) != i)
        {
            fprintf(stderr, "TEST_ADD_AT_INDEX failed. Check add_at_index method. Element at index is incorrect");
            return FAILURE;
        }
    }

    if (arraylist->size != 150)
    {
        fprintf(stderr, "TEST_ADD_AT_INDEX failed. Check add_at_index method. List is the wrond size");
        return FAILURE;
    }

    for (int i = 0; i < 150; i++) // fixed memory leak
    {
        free(arraylist->backing_array[i]);
    }
    destroy(arraylist);
    return SUCCESS;
}
int test_remove_from_index()
{
    // Builds new lists
    arraylist_t *arraylist = create_arraylist(1);
    for (int i = 0; i < 100; i++)
    {
        char *buff = (char *)malloc(sizeof(char) * 4);
        sprintf(buff, "%d", i);
        append(arraylist, buff);
        if (atoi(arraylist->backing_array[i]) != i)
        {
            fprintf(stderr, "TEST_REMOVE failed. Element appended is incorrect");
            return FAILURE;
        }
    }

    // Removes elements systematically from list
    for (int i = 0; i < 100; i += 2)
    {

        int rolling_i = (i % arraylist->size);

        char *expected_remove = arraylist->backing_array[rolling_i];
        free(arraylist->backing_array[rolling_i]);
        char *removed_val = remove_from_index(arraylist, rolling_i);
        if (expected_remove != removed_val) // Checks if the pointers to the elements are the same
        {
            fprintf(stderr, "TEST_REMOVE_FROM_INDEX failed. Incorrect element removed from list\n");
            fprintf(stderr, "Expected: %s (at %p), Actual: %s (at %p)\n", expected_remove, expected_remove, removed_val, removed_val);
            return FAILURE;
        }
    }

    if (arraylist->size != 50)
    {
        fprintf(stderr, "TEST_REMOVE_FROM_INDEX failed. Check add_at_index method. List is the wrong size");
        return FAILURE;
    }

    // destroys the list
    for (int i = 0; i < 50; i++)
    {
        free(arraylist->backing_array[i]);
    }
    destroy(arraylist);
    return SUCCESS;
}

int run_tests()
{
    int count = 0;
    if (test_create() == 1)
    {
        printf("TEST_CREATE passes! Congratulations!\n");
        count++;
    }

    if (test_append() == 1)
    {
        printf("TEST_APPENDS passes! Congratulations!\n");
        count++;
    }

    if (test_add_at_index() == 1)
    {
        printf("TEST_ADD_AT_INDEX passes! Congratulations!\n");
        count++;
    }

    if (test_remove_from_index() == 1)
    {
        printf("TEST_REMOVE_FROM_INDEX passes! Congratulations!\n");
        count++;
    }

    if (count == NUM_TESTS)
    {
        printf("ALL TESTS PASS! Congratulations\n");
    }

    printf("Please note, these tests are sanity checks. They are not guarantees that your implementation may have bugs in the next step.\n");

    return 0;
}