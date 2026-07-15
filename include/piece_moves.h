#ifndef PIECE_MOVES_H
#define PIECE_MOVES_H 

#include <stdint.h>
#include "bitboard.h"

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

typedef enum {
        PM_MAX_MOVES_DEFAULT = 0, /* used for special cases */
        PM_MAX_MOVES_PAWN = 12, /* 3 * 4 because pawns can also promote to 4 different pieces, but normally 3 */
        PM_MAX_MOVES_KNIGHT = 8,
        PM_MAX_MOVES_BISHOP = 13,
        PM_MAX_MOVES_ROOK = 14,
        PM_MAX_MOVES_QUEEN = 27,
        PM_MAX_MOVES_KING = 10 /* +2 because a king can also castle */
} PMMaxMoves;

/* function to slide a piece a single move in a direction defined by PMDirection */
uint64_t pm_slide_piece(const uint64_t bb, const PMDirection d);

/* function to slide a piece and stop when it hits an obstruction
 * puts all the valid squares into moves
 * will include the first obstruction square
 * returns 0 on success
 * returns positive on fail
 */
int pm_slide_piece_until_blocked(uint64_t bb, const PMDirection d, const uint64_t obstructions, uint64_t *moves);

/* function to get max moves depending on the piece type */
PMMaxMoves pm_get_max_moves(BBPieceType pt);

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

/* The following functions get piece moves with respect to the board
 * The output will still be a bitboard
 * They take into account pieces on the board
 * but do not differentiate between allies and enemies
 * this is to ensure that ally pieces are 'covered'
 * and enemy pieces are threatened
 * sliding pieces will be blocked by pieces 
 * pawns will take into account en passant but not promotion
 * there is no king or knight versions as their moves don't change in this regard
 * Return values:
 *      0 if all good
 *      positive integer on fail
 */
int pm_get_pawn_moves_with_pieces(const uint64_t bb, const uint64_t pieces, const int white, uint64_t* moves);
int pm_get_rook_moves_with_pieces(const uint64_t bb, const uint64_t pieces, uint64_t *moves);
int pm_get_bishop_moves_with_pieces(const uint64_t bb, const uint64_t pieces, uint64_t *moves);
int pm_get_queen_moves_with_pieces(const uint64_t bb, const uint64_t pieces, uint64_t *moves);

#endif /*PIECE_MOVES_H*/
