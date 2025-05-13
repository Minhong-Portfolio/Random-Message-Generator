#include "arraylist.h"

arraylist_t *create_arraylist(uint capacity) {
    // If capacity is 0 (or some invalid scenario), return NULL
    if (capacity == 0) {
        return NULL;
    }

    // Allocate space for the arraylist_t structure
    arraylist_t *arraylist = (arraylist_t *) malloc(sizeof(arraylist_t));
    if (arraylist == NULL) {
        return NULL;
    }

    // Allocate space for the backing array
    char **temp_backing_array = (char **) malloc(sizeof(char *) * capacity);
    if (temp_backing_array == NULL) {
        free(arraylist);
        return NULL;
    }

    // Initialize fields
    arraylist->backing_array = temp_backing_array;
    arraylist->capacity = capacity;
    arraylist->size = 0;

    return arraylist;
}

void add_at_index(arraylist_t *arraylist, char *data, int index) {
    // Validate pointers and index range
    if (arraylist == NULL || data == NULL) {
        return;
    }
    if (index < 0 || index > arraylist->size) {
        return;
    }

    // Resize if needed
    if (arraylist->size == arraylist->capacity) {
        resize(arraylist);
    }

    // Shift elements to the right
    for (int i = arraylist->size; i > index; i--) {
        arraylist->backing_array[i] = arraylist->backing_array[i - 1];
    }

    // Insert new element
    arraylist->backing_array[index] = data;
    arraylist->size++;
}

void append(arraylist_t *arraylist, char *data) {
    // Append is just adding at the end
    add_at_index(arraylist, data, arraylist->size);
}

char *remove_from_index(arraylist_t *arraylist, int index) {
    // Check for null list or invalid index
    if (arraylist == NULL) {
        return NULL;
    }
    if (index < 0 || index >= arraylist->size) {
        return NULL;
    }

    // Store the removed element
    char *removed = arraylist->backing_array[index];

    // Shift left from 'index' to end
    for (int i = index; i < (int)arraylist->size - 1; i++) {
        arraylist->backing_array[i] = arraylist->backing_array[i + 1];
    }

    // Null out the last pointer (not strictly required but good practice)
    arraylist->backing_array[arraylist->size - 1] = NULL;

    // Decrement size
    arraylist->size--;
    return removed;
}

void resize(arraylist_t *arraylist) {
    // If arraylist is null, nothing to resize
    if (arraylist == NULL) {
        return;
    }

    // Double the current capacity
    uint new_capacity = arraylist->capacity * 2;

    // Reallocate
    char **temp_backing_array = (char **) realloc(
        arraylist->backing_array, new_capacity * sizeof(char *));
    if (temp_backing_array == NULL) {
        // If realloc fails, do nothing (or handle error)
        return;
    }

    // Update fields
    arraylist->backing_array = temp_backing_array;
    arraylist->capacity = new_capacity;
}

void destroy(arraylist_t *arraylist) {
    // If already null, nothing to do
    if (arraylist == NULL) {
        return;
    }

    // Free only the backing array if that's the design
    // (Some designs also free 'arraylist' itself.)
    free(arraylist->backing_array);
}