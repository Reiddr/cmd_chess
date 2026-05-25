#ifndef PLAYER_MOVES_H
#define PLAYER_MOVES_H

#include <stdint.h>

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
uint64_t pm_get_start_square(const char* s){
        int file = s[0] - 'a';
        int rank = s[1] - '1';
        uint64_t r = 1ULL << (rank * 8 + (8 - file)); /* 8 - file because we're shifting starting from the right */
        return r;
}


#endif /*PLAYER_MOVES_H*/
