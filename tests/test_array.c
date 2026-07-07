#include "test.h"
#include "array.h"

int main(void)
{
        enum {ARRAY_LEN = 64};
        uint64_t uint64_array[ARRAY_LEN];
        struct array a;
        a = array_create(uint64_array, ARRAY_LEN);

        ASSERT(array_set(&a, 0) == 0, "Setting array to 0");
        return any_test_failed();
}
