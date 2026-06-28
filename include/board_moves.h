#ifndef BOARD_MOVES_H
#define BOARD_MOVES_H 

#include <stdint.h>
#include <stddef.h>
#include "bitboard.h"

/* gets all the valid moves for a valid starting_square 
 * will check the start square is of the right colour piece
 * populates the list of valid moves that the piece on the start square can move to
 * this will include if pieces are pinned or moving into check
 * returns the number of valid moves populated
 * or negative on fail
 */
int bm_get_valid_moves(const struct BBBoardState bs, const uint64_t start, uint64_t *moves, const size_t len_moves);

/* The next set of functions will get the moves for each piece with 
 * respect to the state of the game,
 * they will all take the same form
 * input board state and array of PMMoves of length len_m
 * the first element of PMMove must contain a valid starting square
 * the given square will be checked for a piece type and the array
 * of moves filled out with all the valid moves
 * returns the number of PMMoves allocated
 * or a negative number if fail
 * these functions will not check for checks, pins, ect.
 */

struct _move_info; /* internal struct, defined in source, created to pack common move info */

int bm_get_valid_pawn_moves(const struct _move_info mi, const uint64_t en_passant_square, uint64_t *moves, const size_t len_moves);

#endif /*BOARD_MOVES_H*/
