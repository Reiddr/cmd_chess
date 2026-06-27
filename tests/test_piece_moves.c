#include "test.h"
#include "piece_moves.h"
#include "bitboard.h"

int main(void)
{
        uint64_t bb = BB_1;
        uint64_t moves, captures;

        ASSERT(pm_slide_piece(bb, PM_DIR_N) == 0x0000000000000100, "slide BB_1 north");
        ASSERT(pm_slide_piece(bb, PM_DIR_NE) == BB_0, "slide BB_1 north east");
        ASSERT(pm_slide_piece(bb, PM_DIR_E) == BB_0, "slide BB_1 east");
        ASSERT(pm_slide_piece(bb, PM_DIR_SE) == BB_0, "slide BB_1 south east");
        ASSERT(pm_slide_piece(bb, PM_DIR_S) == BB_0, "slide BB_1 south");
        ASSERT(pm_slide_piece(bb, PM_DIR_SW) == BB_0, "slide BB_1 south west");
        ASSERT(pm_slide_piece(bb, PM_DIR_W) == 0x0000000000000002, "slide BB_1 west");
        ASSERT(pm_slide_piece(bb, PM_DIR_NW) == 0x0000000000000200, "slide BB_1 north west");
        bb = 0x0000000000800000;
        ASSERT(pm_slide_piece(bb, PM_DIR_SW) == BB_0, "slide south west off board");
        ASSERT(pm_slide_piece(bb, PM_DIR_W) == BB_0, "slide west off board");
        ASSERT(pm_slide_piece(bb, PM_DIR_NW) == BB_0, "slide north west off board");
        ASSERT(pm_slide_piece(BB_1, PM_DIR_COUNT) == BB_0, "slide default case");

        bb = 0x0000000000020000;
        ASSERT(pm_slide_piece(bb, PM_DIR_N) == 0x0000000002000000, "slide piece north");
        ASSERT(pm_slide_piece(bb, PM_DIR_NE) == 0x0000000001000000, "slide piece north east");
        ASSERT(pm_slide_piece(bb, PM_DIR_E) == 0x0000000000010000, "slide piece east");
        ASSERT(pm_slide_piece(bb, PM_DIR_SE) == 0x0000000000000100, "slide piece south east");
        ASSERT(pm_slide_piece(bb, PM_DIR_S) == 0x0000000000000200, "slide piece south");
        ASSERT(pm_slide_piece(bb, PM_DIR_SW) == 0x0000000000000400, "slide piece south west");
        ASSERT(pm_slide_piece(bb, PM_DIR_W) == 0x0000000000040000, "slide piece west");
        ASSERT(pm_slide_piece(bb, PM_DIR_NW) == 0x0000000004000000, "slide piece north west");

        ASSERT(pm_get_pawn_moves(bb, 0, &moves, &captures) == 0, "get black pawn moves and captures");
        ASSERT(moves == 0x0000000000000200, "black pawn moves");
        ASSERT(captures == 0x0000000000000500, "black pawn captures");
        ASSERT(pm_get_pawn_moves(bb, 1, &moves, &captures) == 0, "get white pawn moves and captures");
        ASSERT(moves == 0x0000000002000000, "white pawn moves");
        ASSERT(captures == 0x0000000005000000, "white pawn captures");
        bb = 0x0080000000000000;
        ASSERT(pm_get_pawn_moves(bb, 1, &moves, &captures) == 0, "get white pawn moves and captures on edge");
        ASSERT(moves == 0x8000000000000000, "white pawn moves up the board");
        ASSERT(captures == 0x4000000000000000, "white pawn captures on edge");
        ASSERT(pm_get_pawn_moves(bb, 0, &moves, &captures) == 0, "get black pawn moves and captures on edge");
        ASSERT(moves == 0x0000808000000000, "black pawn moves from start");
        ASSERT(captures == 0x0000400000000000, "black pawn captures on edge");

        ASSERT(pm_get_knight_moves(bb, &moves) == 0, "get knight moves in corner");
        ASSERT(moves == 0x2000204000000000, "knight moves in corner");
        bb = 0x0000000010000000;
        ASSERT(pm_get_knight_moves(bb, &moves) == 0, "get knight moves in middle");
        ASSERT(moves == 0x0000284400442800, "knight moves in middle");

        ASSERT(pm_get_rook_moves(bb, &moves) == 0, "get rook moves in middle");
        ASSERT(moves == 0x10101010EF101010, "rook moves in middle");
        bb = 0x8000000000000000;
        ASSERT(pm_get_rook_moves(bb, &moves) == 0, "get rook moves in corner");
        ASSERT(moves == 0x7F80808080808080, "rook moves in corner");

        ASSERT(pm_get_bishop_moves(bb, &moves) == 0, "get bishop moves in corner");
        ASSERT(moves == 0x0040201008040201, "bishop moves in corner");
        bb = 0x0000000200000000;
        ASSERT(pm_get_bishop_moves(bb, &moves) == 0, "get bishop moves in middle");
        ASSERT(moves == 0x1008050005081020, "bishop moves in middle");

        ASSERT(pm_get_queen_moves(bb, &moves) == 0, "get queen moves in middle");
        ASSERT(moves == 0x120A07FD070A1222, "queen moves in middle");
        
        ASSERT(pm_get_king_moves(bb, &moves) == 0, "get king moves in middle");
        ASSERT(moves == 0x0000070507000000, "king moves in middle");

        return any_test_failed();
}
