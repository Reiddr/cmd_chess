#ifndef PLAYER_MOVES_H
#define PLAYER_MOVES_H

#include <stdint.h>
#include "bitboard.h"

/* moves can be of the form a1b2 [start_square][end_square]
 * this function will check that both are actually on the board
 */
int pm_check_move_str(const char* s)
{
        int i = 0;
        while (s[i++]) {
                if (i > 5)
                        return 1;
        }
        if (i != 5)
                return 1;
        if (s[0] < 'a' || s[0] > 'h')
                return 2;
        if (s[2] < 'a' || s[2] > 'h')
                return 2;
        if (s[1] < '1' || s[1] > '8')
                return 3;
        if (s[3] < '1' || s[3] > '8')
                return 3;
        return 0;
}

/* Assume input string is a 2 char string that is on the board
 * eg "a1" or "e5"
 * return a bitboard with the square set to 1
 */
uint64_t pm_get_square(const char* s){
        int file = s[0] - 'a';
        int rank = s[1] - '1';
        uint64_t r = 1ULL << (rank * 8 + (7 - file)); /* 8 - file because we're shifting starting from the right */
        return r;
}

/* A fucntion to take in the move string and return its starting square, piece type, and colour
 * does not check validity of string or move
 * will use the first result found, ie will not check the board state validity
 * returns 0 if allgood
 * positive if no piece is found
 */
int pm_find_piece(const struct BBBoardState bs, const char* s, uint64_t* start_square, BBPieceType* type, int* white){
        *start_square = pm_get_square(s);
        for (*type = BB_T_PAWN; *type < BB_T_COUNT; (*type)++) {
                if (bs.white_pieces[*type] & *start_square) {
                        *white = 1;
                        return 0;
                }
                if (bs.black_pieces[*type] & *start_square) {
                        *white = 0;
                        return 0;
                }
        }
        return 1;
}


#endif /*PLAYER_MOVES_H*/
