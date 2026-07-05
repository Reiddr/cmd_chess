#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

/* array data type
 * it is meant to be wrapped and passed to the array_* functions below.
 * This could be explicitly or through a macro
 * There is no array_create and array_destory function
 * this is purposeful so that memory allocation is handled by the caller
 */
struct array {
        void *data;
        const size_t length;
        const size_t element_length;
};

/* Append a single element to the array
 * element_length bytes from addres 'data' will be appended to the array
 * returns 0 on success, 1 if the allocation runs over the bounds of the allocated length
 */
int array_append(struct array *self, const void *data);

int array_clear(struct array *self);

int array_set(struct array *self, const void *data, const size_t index_start, const size_t number_of_elements);

int array_get(struct array *self, void *data, const size_t index_start, const size_t number_of_elements);

#endif /*ARRAY_H*/
