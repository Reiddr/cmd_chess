#ifndef BOARD_MOVES_H
#define BOARD_MOVES_H 

#include <stdint.h>
#include <stddef.h>
#include "bitboard.h"

struct BMMove {
        uint64_t start;
        uint64_t end;
        BBPieceType promotion_piece; /* if piece is a promoting pawn, this is the piece it is promoting to */
};

/* gets all the valid moves for a valid board state
 * iterates through all the pieces of the current players turn and creates a list of BMMove
 * this will include if pieces are pinned or moving into check, castling etc
 * returns the number of valid moves populated
 * or negative on fail
 */
int bm_get_valid_moves_board(const struct BBBoardState *bs, struct BMMove *moves, const size_t len_moves);

/* Gets the valid moves for a single piece
 * does not handle checks and pins or castling.
 * does handle en_passant
 * returns the number of moves set
 * or negative number on fail
 */
int bm_get_valid_moves_piece(const struct BBBoardState *bs, const uint64_t start, struct BMMove *moves, const size_t len_moves);

/* Function to apply a move to the board,
 * will alter the board state
 * removes castling rights
 * checks enpassant square
 * switches the turn
 * and increments the move clocks
 */
int make_move(struct BBBoardState *bs, const struct BMMove *bm);

/* Function to see if the possible moves put the enemy king in check
 * possible moves is all the moves possible 
 * returns 0 if not in check
 * returns 1 if in check
 */
int in_check(const struct BBBoardState *bs, const uint64_t possible_moves);

/* Checks if the current board state is valid
 * that there are no overlapping pieces
 * that there can only be one king for each side
 * that there can never be more than 8 pawns for each side
 * that the turn int is either 0 or 1
 * that neither side can have more that 16 pieces total
 * returns 0 if okay
 * returns positve if not
 */
int valid_board_state(const struct BBBoardState *bs);

#endif /*BOARD_MOVES_H*/
