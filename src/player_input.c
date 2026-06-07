#include "player_input.h"
#include "bitboard.h"
#include <stdint.h>

int pi_check_move_str(const char* s)
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

uint64_t pi_get_square(const char* s)
{
        int file = s[0] - 'a';
        int rank = s[1] - '1';
        uint64_t r = BB_1 << (rank * 8 + (7 - file)); /* 8 - file because we're shifting starting from the right */
        return r;
}

int pi_find_piece(const struct BBBoardState bs, const char* s, uint64_t* start_square, BBPieceType* type, int* white)
{
        *start_square = pi_get_square(s);
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
