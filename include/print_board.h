#ifndef PRINT_BOARD_H
#define PRINT_BOARD_H
#include <stdio.h>
#include <assert.h>
#include "ansi_codes.h"
#include "bitboard.h"
#include "term_draw.h"

char pb_get_piece_char(BBPieceType pt, int white)
{
	switch(pt) {
		case BB_T_KING:
			return	(white) ? 'K' : 'k' ;
		case BB_T_QUEEN:
			return	(white) ? 'Q' : 'q' ;
		case BB_T_ROOK:
			return	(white) ? 'R' : 'r' ;
		case BB_T_BISHOP:
			return	(white) ? 'B' : 'b' ;
		case BB_T_KNIGHT:
			return	(white) ? 'N' : 'n' ;
		case BB_T_PAWN:
			return	(white) ? 'P' : 'p' ;
		default:
			return	' ';
	}
}

char* pb_get_piece_char_unicode(BBPieceType pt, int white)
{
	switch(pt) {
		case BB_T_KING:
			return	(white) ? "\xE2\x99\x94" : "\xE2\x99\x9A" ;
		case BB_T_QUEEN:
			return	(white) ? "\xE2\x99\x95" : "\xE2\x99\x9B" ;
		case BB_T_ROOK:
			return	(white) ? "\xE2\x99\x96" : "\xE2\x99\x9C" ;
		case BB_T_BISHOP:
			return	(white) ? "\xE2\x99\x97" : "\xE2\x99\x9D" ;
		case BB_T_KNIGHT:
			return	(white) ? "\xE2\x99\x98" : "\xE2\x99\x9E" ;
		case BB_T_PAWN:
			return	(white) ? "\xE2\x99\x99" : "\xE2\x99\x9F" ;
		default:
			return	"";
	}
}

/* will get the basic str representation for easy printing
eg rnbqkbnr/pppppppp/        /        /        /        /PPPPPPPP/RNBQKBNR
input char* must be at least len 65
does not check validity of boardstate, if multiple pieces are on the same square only the final one will be shown */
int pb_get_board_str(struct BBBoardState bs, char* s, size_t len_s){
        assert(len_s >= 65);
        /* intialise the whole str to " " */
        int i, j;
        for (i = 0; i < 64; i++){
                s[i] = ' ';
        }
        s[64] = '\0';

        /* loop through all the white and black pieces and set their piece chars in the board string */
        size_t len_indices = 64;
        int indices[len_indices];
	BBPieceType t;
	for(t = BB_T_PAWN; t < BB_T_COUNT; t++){
                int num_indices = bb_get_piece_indices(bs.white_pieces[t], indices, len_indices);
                for (i = 0; i < num_indices; i++){
                        s[indices[i]] = pb_get_piece_char(t, 1);
                }
                num_indices = bb_get_piece_indices(bs.black_pieces[t], indices, len_indices);
                for (i = 0; i < num_indices; i++){
                        s[indices[i]] = pb_get_piece_char(t, 0);
                }
	}

        /* compress the str into a proper FEN str */
        char c;
        int count;
        for (i = 0; i < 8; i++){
                count = 0;
                for (j = 0; j < 8; j++){
                        c = s[i * 8 + j];
                }
        }
                        
        return 0;
}

void pb_print_board(struct BBBoardState bs)
{
        size_t len_board_str = 65;
        char board_str[len_board_str];
        pb_get_board_str(bs, board_str, len_board_str);
        td_reset_colour();

        size_t len_tmp_buff = 20;
        char tmp_buff[len_tmp_buff];
        int i, j;
	for(i = 0; i < 8; i++){
                /* format and print the rank number */
                sprintf(tmp_buff, "%i  ", 8-i);
                td_puts(tmp_buff, FG_WHITE, BG_BLACK);
                for(j = 0; j < 8; j++){
                        char c = board_str[i * 8 + j];
                        if (c == ' '){
                                c = '.';
                        }
                        sprintf(tmp_buff, "%c ", c);
                        td_puts(tmp_buff, FG_WHITE, BG_BLACK);
                }
                putchar('\n');
	}
        td_puts( "\n   A B C D E F G H\n", FG_WHITE, BG_BLACK);
        td_reset_colour();
}

/* this doesn't actually print the whole fancy board yet */
void pb_print_board_fancy(struct BBBoardState bs)
{
        size_t len_tmp_buff = 20;
        char tmp_buff[len_tmp_buff];
        BBPieceType pt = BB_T_KNIGHT;
        uint64_t bb = bs.white_pieces[pt];
        int turn_white = 1;
        int i, j;
	for(i = 7; i > -1; i--){
                /* format and print the rank number */ 
                sprintf(tmp_buff, "%i  ", i+1);
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
                        char *p = (bb & mask) ? pb_get_piece_char_unicode(pt, turn_white) : "  ";
                        td_puts(p, fg, bg);
                }
                td_reset_colour();
                putchar('\n');
	}
        td_puts( "   A B C D E F G H\n", FG_WHITE, BG_BLACK);
        td_reset_colour();
}
#endif /*PRINT_BOARD_H*/
