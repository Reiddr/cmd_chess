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
			return	(white) ? "\u{2654}" : "\u{265A}" ;
		case BB_T_QUEEN:
			return	(white) ? "\u{2655}" : "\u{265B}" ;
		case BB_T_ROOK:
			return	(white) ? "\u{2656}" : "\u{265C}" ;
		case BB_T_BISHOP:
			return	(white) ? "\u{2657}" : "\u{265D}" ;
		case BB_T_KNIGHT:
			return	(white) ? "\u{2658}" : "\u{265E}" ;
		case BB_T_PAWN:
			return	(white) ? "\u{2659}" : "\u{265F}" ;
		default:
			return	"";
	}
}

int pb_print_byte(uint8_t byte, char space, char* colour){
	int i = 0;
	printf("%s%c", colour, space);
	uint8_t bit;
	for(i=0; i<8; i++){
		bit = (byte >> i) && 0x01;
		printf(" %u |", bit);
	}
	printf("\n" RESET);
        return 0;
}

int pb_print_board(struct BBBoardState bs){
        size_t len_tmp_buff = 2;
        char tmp_buff[len_tmp_buff];
        int i;
	for(i = 7; i > -1; i--){
                //format and print the rank number
                snprintf(tmp_buff, len_tmp_buff, "%i", i+1);
                td_puts(tmp_buff, FG_WHITE, BG_BLACK);
                
                int j;
                for(j = 0; j < 8; j++){
                         
                }
		// rank = bs >> (i*8);
		// pb_print_byte(rank, '|', FG_YELLOW);
	}
        return 0;
}
#endif /*PRINT_BOARD_H*/
