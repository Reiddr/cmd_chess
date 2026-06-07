#ifndef PRINT_BOARD_H
#define PRINT_BOARD_H

#include "bitboard.h"
#include <stdint.h>

char pb_get_piece_char(const BBPieceType pt, const int white);

char* pb_get_piece_unicode(const BBPieceType pt, const int white);

char* pb_get_piece_unicode_from_ascii(const char c);

/* will get the basic str representation for easy printing
eg rnbqkbnr/pppppppp/        /        /        /        /PPPPPPPP/RNBQKBNR
input char* must be at least len 65
does not check validity of boardstate, if multiple pieces are on the same square only the final one will be shown */
int pb_get_board_str(const struct BBBoardState bs, char* s, const size_t len_s);

/* will convert the board state to a FEN string
eg rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
input char* must be at least len 9 * 8 + 17 = 89
does not check validity of boardstate, if multiple pieces are on the same square only the final one will be shown */
int pb_get_fen(const struct BBBoardState bs, char* s, const size_t len_s);

void pb_print_board(const struct BBBoardState bs);

/* this doesn't actually print the whole fancy board yet */
void pb_print_board_fancy(const struct BBBoardState bs);

#endif /*PRINT_BOARD_H*/
