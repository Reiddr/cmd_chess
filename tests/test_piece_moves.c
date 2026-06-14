#include "test.h"
#include "piece_moves.h"

int main(void)
{
        ASSERT(1, "pass");
        ASSERT(0, "fail");
        return any_test_failed();
}
