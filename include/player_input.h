#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "bitboard.h"
#include <stdint.h>

/* moves can be of the form a1b2 [start_square][end_square]
 * this function will check that both are actually on the board
 */
int pi_check_move_str(const char *s);

/* Assume input string is a 2 char string that is on the board
 * eg "a1" or "e5"
 * return a bitboard with the square set to 1
 */
uint64_t pi_get_square(const char *s);

/* A function to take in the move string and return its square, piece type, and colour
 * does not check validity of string or move
 * will use the first result found, ie will not check the board state validity
 * returns 0 if allgood
 * positive if no piece is found
 */
int pi_find_piece(const struct BBBoardState *bs, const char *s, uint64_t *start_square, BBPieceType *type, int *white);

#endif /*PLAYER_INPUT*/
