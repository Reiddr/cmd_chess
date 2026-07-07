#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

/* array data type
 * meant to add some simple convenience functions for index and error checking
 * For now it is a uint64_t although maybe it get wrapped into a macro in the future
 * There is no memory allocation
 * this is purposeful so that memory allocation is handled by the caller
 * Ideally I would like this type defined in the c source. But that requires all the functions
 * including the create fucntion to only interact with it via pointers. Ie even less optimisation
 * Therefore the struct definition will be here in the header
 * this allows all things that use it to be fully aware of its size in bytes and optimise appropriately
 */
struct array {
        uint64_t *data;
        size_t length; /* I'd like for this to be const, but it must then be a compile time const, and cannot be initialise via param in a function (unless we do a yucky memcpy) */
        size_t index; /* index of last set element in the array (past this index is garbage) */
};


/* Set up the array struct
 * it is assumed the memory has already been allocated with length elements
 */
struct array array_create(uint64_t *data, size_t length);

/* Append a single element to the array
 * returns non zero on fail
 */
int array_append(struct array *self, const uint64_t value);

/* Gets a single value from array at index
 * returns non zero on fail
 */
int array_get(const struct array *self, uint64_t *value, const size_t index);

/* Sets all of the arrray to value
 * will reset index of the array to 0 (ie appends will start at 0)
 * returns non zero on fail
 */
int array_set(struct array *self, const uint64_t value);

/* Copies number_of_elements from a into self starting from index_start
 * performs length and index checks
 * returns non zero on fail
 */
int array_copy(struct array *self, const struct array *a, const size_t index_self_start, const size_t index_a_start, const size_t number_of_elements);

#endif /*ARRAY_H*/
