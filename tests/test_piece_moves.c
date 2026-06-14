#include "test.h"
#include "piece_moves.h"
#include "bitboard.h"

int main(void)
{
        uint64_t bb = BB_1;

        ASSERT(pm_slide_piece(bb, PM_DIR_N) == 0x0000000000000100, "slide BB_1 north");
        ASSERT(pm_slide_piece(bb, PM_DIR_NE) == BB_0, "slide BB_1 north east");
        ASSERT(pm_slide_piece(bb, PM_DIR_E) == BB_0, "slide BB_1 east");
        ASSERT(pm_slide_piece(bb, PM_DIR_SE) == BB_0, "slide BB_1 south east");
        ASSERT(pm_slide_piece(bb, PM_DIR_S) == BB_0, "slide BB_1 south");
        ASSERT(pm_slide_piece(bb, PM_DIR_SW) == BB_0, "slide BB_1 south west");
        ASSERT(pm_slide_piece(bb, PM_DIR_W) == 0x0000000000000002, "slide BB_1 west");
        ASSERT(pm_slide_piece(bb, PM_DIR_NW) == 0x0000000000000200, "slide BB_1 north west");

        bb = 0x0000000000020000;
        ASSERT(pm_slide_piece(bb, PM_DIR_N) == 0x0000000200000000, "slide piece north");
        ASSERT(pm_slide_piece(bb, PM_DIR_NE) == 0x0000000100000000, "slide piece north east");
        ASSERT(pm_slide_piece(bb, PM_DIR_E) == 0x0000000000010000, "slide piece east");
        ASSERT(pm_slide_piece(bb, PM_DIR_SE) == 0x0000000000000001, "slide piece south east");
        ASSERT(pm_slide_piece(bb, PM_DIR_S) == 0x0000000000000002, "slide piece south");
        ASSERT(pm_slide_piece(bb, PM_DIR_SW) == 0x0000000000000004, "slide piece south west");
        ASSERT(pm_slide_piece(bb, PM_DIR_W) == 0x0000000000040000, "slide piece west");
        ASSERT(pm_slide_piece(bb, PM_DIR_NW) == 0x0000000400000000, "slide piece north west");

        return any_test_failed();
}
