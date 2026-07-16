#include "test.h"
#include "piece_moves.h"

int main(void)
{
        uint64_t moves;
        uint64_t obstructions = 0xFF0000;

        ASSERT(pm_slide_piece_until_blocked(0x01, PM_DIR_N, obstructions, &moves) == 0, "slide BB_1 north until blocked");
        ASSERT(moves == 0x010100, "slide north valid");

        ASSERT(pm_get_pawn_moves_with_pieces(0x00, obstructions, 1, &moves) == 1, "pm_get_pawn_moves_with_pieces invalid");
        ASSERT(pm_get_pawn_moves_with_pieces(0x0200, obstructions, 1, &moves) == 0, "pm_get_pawn_moves_with_pieces");
        ASSERT(moves == 0x050000, "valid pawn moves");
        ASSERT(pm_get_pawn_moves_with_pieces(0x0200, 0xFF, 0, &moves) == 0, "pm_get_pawn_moves_with_pieces black");
        ASSERT(moves == 0x05, "valid black pawn moves");

        ASSERT(pm_get_bishop_moves_with_pieces(0x00, obstructions, &moves) == 1, "pm_get_bishop_moves_with_pieces invalid");
        ASSERT(pm_get_bishop_moves_with_pieces(0x0200, obstructions, &moves) == 0, "pm_get_bishop_moves_with_pieces");
        ASSERT(moves == 0x050005, "valid bishop moves");

        ASSERT(pm_get_rook_moves_with_pieces(0x00, obstructions, &moves) == 1, "pm_get_rook_moves_with_pieces invalid");
        ASSERT(pm_get_rook_moves_with_pieces(0x0200, obstructions, &moves) == 0, "pm_get_rook_moves_with_pieces");
        ASSERT(moves == 0x02FD02, "valid rook moves");
        
        ASSERT(pm_get_queen_moves_with_pieces(0x00, obstructions, &moves) == 1, "pm_get_queen_moves_with_pieces invalid");
        ASSERT(pm_get_queen_moves_with_pieces(0x0200, obstructions, &moves) == 0, "pm_get_queen_moves_with_pieces");
        ASSERT(moves == 0x07FD07, "valid queen moves");

        return any_test_failed();
}
