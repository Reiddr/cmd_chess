#ifndef PRINT_BOARD_H
#define PRINT_BOARD_H
#include <stdio.h>
#include "ansi_codes.h"
#include "bitboard.h"
#include "term_draw.h"

char* pb_get_piece_char(BBPieceType pt, int white)
{
	switch(pt) {
		case BB_T_KING:
			return	(white) ? "\u{2654} " : "\u{265A} " ;
		case BB_T_QUEEN:
			return	(white) ? "\u{2655} " : "\u{265B} " ;
		case BB_T_ROOK:
			return	(white) ? "\u{2656} " : "\u{265C} " ;
		case BB_T_BISHOP:
			return	(white) ? "\u{2657} " : "\u{265D} " ;
		case BB_T_KNIGHT:
			return	(white) ? "\u{2658} " : "\u{265E} " ;
		case BB_T_PAWN:
			return	(white) ? "\u{2659} " : "\u{265F} " ;
		default:
			return	"";
	}
}

void pb_print_board(struct BBBoardState bs)
{
        size_t len_tmp_buff = 20;
        char tmp_buff[len_tmp_buff];
        BBPieceType pt = BB_T_KNIGHT;
        uint64_t bb = bs.white_pieces[pt];
        int turn_white = 1;
        int i, j;
	for(i = 7; i > -1; i--){
                //format and print the rank number
                snprintf(tmp_buff, len_tmp_buff, "%i  ", i+1);
                td_puts(tmp_buff, FG_WHITE, BG_BLACK);
                for(j = 7; j > -1; j--){
                        if(j >= 3){
                                turn_white = 0;
                        } else {
                                turn_white = 1;
                        }
                        char *fg = FG_BLACK;
                        char *bg = ((i + j) % 2) ? BG_BROWN : BG_CREAM;
                        uint64_t mask = 1ULL << (i * 8 + j);
                        char *p = (bb & mask) ? pb_get_piece_char(pt, turn_white) : "  ";
                        td_puts(p, fg, bg);
                }
                td_reset_colour();
                putchar('\n');
	}
        td_puts( "   A B C D E F G H\n", FG_WHITE, BG_BLACK);
        td_reset_colour();
}
#endif /*PRINT_BOARD_H*/
