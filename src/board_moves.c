#include "board_moves.h"
#include "bitboard.h"
#include "piece_moves.h"
#include <stdint.h>

struct _move_info {
        uint64_t start;
        uint64_t ally_pieces;
        uint64_t enemy_pieces;
};

int bm_get_valid_moves(const struct BBBoardState bs, struct PMMove *moves, const size_t len_moves)
{
        uint64_t ally_pieces = bb_get_mask((bs.turn_white ? bs.white_pieces : bs.black_pieces), BB_T_COUNT);
        uint64_t enemy_pieces = bb_get_mask((!bs.turn_white ? bs.white_pieces : bs.black_pieces), BB_T_COUNT);
        /* iterate through ally pieces and get valid moves for each piece */
        if (!(start & ally_pieces))
                return -1;
        return 0;
}

int bm_get_valid_pawn_moves(const struct _move_info mi, const int white, const uint64_t en_passant_square, uint64_t *moves, const size_t len_moves)
{
        uint64_t possible_captures, possible_moves;
        enum {LEN_INDICES = 64};
        int indices[LEN_INDICES];
        int valid, num_indices, i, num_moves;

        valid = pm_get_pawn_moves(mi.start, white, &possible_moves, &possible_captures);
        if (valid != 0)
                return -2;
        num_indices = bb_get_piece_indices(possible_moves, indices, LEN_INDICES);
        if (num_indices < 0)
                return -3;

        num_moves = 0;
        for (i = 0; i < num_indices; i++) {
                uint64_t bb = BB_1 << indices[i];
                if (!(bb & mi.ally_pieces))
                        if ((size_t)(num_moves + 1) > len_moves)
                                return -1;

                        moves[num_moves++] = bb;
        }

        

        return 0;
}
