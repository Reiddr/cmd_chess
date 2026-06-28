#include "board_moves.h"
#include "bitboard.h"
#include "piece_moves.h"
#include <stdint.h>

struct _move_info {
        uint64_t ally_pieces;
        uint64_t enemy_pieces;
        uint64_t start;
};

int bm_get_valid_moves(const struct BBBoardState bs, const uint64_t start, uint64_t *moves, const size_t len_moves)
{
        uint64_t ally_pieces = bb_get_mask((bs.turn_white ? bs.white_pieces : bs.black_pieces), BB_T_COUNT);
        uint64_t enemy_pieces = bb_get_mask((!bs.turn_white ? bs.white_pieces : bs.black_pieces), BB_T_COUNT);
        return 0;
}

int bm_get_valid_pawn_moves(const struct _move_info mi, const uint64_t en_passant_square, uint64_t *moves, const size_t len_moves)
{
        return 0;
}
