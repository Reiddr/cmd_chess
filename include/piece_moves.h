#ifndef PIECE_MOVES_H
#define PIECE_MOVES_H 

#include <stdint.h>

typedef enum {
        PM_DIR_NW,
        PM_DIR_N,
        PM_DIR_NE,
        PM_DIR_E,
        PM_DIR_SE,
        PM_DIR_S,
        PM_DIR_SW,
        PM_DIR_W,
        PM_DIR_COUNT
} PMDirection;

/* function to slide a piece a single move in a direction defined by PMDirection */
uint64_t pm_slide_piece(const uint64_t bb, const PMDirection d);

/* The following functions will get the possible moves of the pieces
 * as if they are the only one on the board
 * ie, these functions will not take into account board state
 */

/* Pawns can move forward a single space, 
 * take diagonally forwards a single space,
 * and move 2 spaces if they are on the second or eighth rank for white or black respectively
 * as pawns are special the captures are returned in a separate bitboard
 * returns 0 if all good
 * returns 1 on a fail
 */
int pm_get_pawn_moves(const uint64_t bb, const int white, uint64_t* moves, uint64_t* captures);

/* Knights moves in an L, 2 files, 1 rank, or vice versa
 * returns 0 if all good
 * returns positive integer on fail
 */
int pm_get_knight_moves(const uint64_t bb, uint64_t *moves);

/* Rook moves, all along a rank or file
 * returns 0 if all good
 * returns positive integer on fail
 */
int pm_get_rook_moves(const uint64_t bb, uint64_t *moves);

/* Bishop moves, all along the intersecting diagonals
 * returns 0 if all good
 * returns positive integer on fail
 */
int pm_get_bishop_moves(const uint64_t bb, uint64_t *moves);

/* Queen moves, combination of bishop and rook
 * returns 0 if all good
 * returns positive integer on fail
 */
int pm_get_queen_moves(const uint64_t bb, uint64_t *moves);

/* King moves, all directions a single square 
 * returns 0 if all good
 * returns positive integer on fail
 */
int pm_get_king_moves(const uint64_t bb, uint64_t *moves);

#endif /*PIECE_MOVES_H*/
