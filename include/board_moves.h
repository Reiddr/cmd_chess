#ifndef BOARD_MOVES_H
#define BOARD_MOVES_H 

#include <stdint.h>
#include <stddef.h>
#include "bitboard.h"

struct PMMove {
        uint64_t start;
        uint64_t end;
};

struct _move_info; /* internal struct, defined in source, created to pack common move info */

/* gets all the valid moves for a valid board state
 * iterates through all the pieces of the current players turn and creates a list of PMMove
 * this will include if pieces are pinned or moving into check, castling etc
 * returns the number of valid moves populated
 * or negative on fail
 */
int bm_get_valid_moves(const struct BBBoardState bs, struct PMMove *moves, const size_t len_moves);

/* The next set of functions will get the moves for each piece with 
 * respect to the state of the game,
 * returns the number of moves allocated
 * or a negative number if fail
 * these functions will not check for checks, pins, ect.
 */

int bm_get_valid_pawn_moves(const struct _move_info mi, const int white, const uint64_t en_passant_square, uint64_t *moves, const size_t len_moves);

#endif /*BOARD_MOVES_H*/
