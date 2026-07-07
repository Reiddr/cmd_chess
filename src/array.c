#include "array.h"

struct array array_create(uint64_t *data, const size_t length)
{
        struct array a;
        a.data = data;
        a.length = length;
        a.index = 0;
        return a;
}

int array_append(struct array *self, const uint64_t value)
{
        if (self->index >=  self->length)
                return 1;
        self->data[self->index++] = value;
        return 0;
}

int array_get(const struct array *self, uint64_t *value, const size_t index)
{
        if (index > self->index)
                return 1;
        *value = self->data[index];
        return 0;
}

int array_set(struct array *self, const uint64_t value)
{
        size_t i;
        for (i = 0; i < self->length; i++)
                self->data[i] = value;
        self->index = 0;
        return 0;
}

/* Copies number_of_elements from a into self starting from index_start
 * performs length and index checks
 * returns non zero on fail
 */
int array_copy(struct array *self, const struct array *a, const size_t index_self_start, const size_t index_a_start, const size_t number_of_elements)
{
        size_t i;
        if (index_self_start + number_of_elements > self->length)
                return 1;
        if (index_self_start + number_of_elements >= self->index)
                return 2;
        if (index_a_start + number_of_elements > a->length)
                return 3;
        if (index_a_start + number_of_elements >= a->index)
                return 4;
        for (i = 0; i < number_of_elements; i++)
                self->data[i + index_self_start] = a->data[i + index_a_start];
        return 0;
}
