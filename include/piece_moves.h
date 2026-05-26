#ifndef PIECE_MOVES_H
#define PIECE_MOVES_H 

#include <stdint.h>

/* The following functions will get the possible moves of the pieces
 * as if they are the only one on the board
 * ie, these functions will not take into account board state
 */

/* Pawns can move forward a single space, 
 * take diagonally forwards a single space,
 * and move 2 spaces if they are on the second or eighth rank for white or black respectively
 * as pawns are special the captures are returned in a separate bitboard
 */
uint64_t pm_get_pawn_moves(const uint64_t bb, const int white, uint64_t* captures) {
        uint64_t rank_mask = 0xFF00ULL;  
        if (!white)
                rank_mask = rank_mask << (5 * 8);
        uint64_t left_mask  = 0x8080808080808080;
        uint64_t right_mask = 0x0101010101010101;

        /* advance the pawn */
        uint64_t moves = (white) ? bb << 8 : bb >> 8;

        /* add the diagonal moves only if we aren't on an edge */
        if (!(moves & left_mask))
                *captures = moves << 1;
        if (!(moves & right_mask))
                *captures = *captures | (moves >> 1);

        /* shift another rank if we were on a starting square */
        if (rank_mask & bb) 
                moves = moves | ((white) ? moves << 8 : moves >> 8);

        return moves;
}

#endif /*PIECE_MOVES_H*/
