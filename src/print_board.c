#include "print_board.h"
#include "ansi_codes.h"
#include "bitboard.h"
#include "term_draw.h"
#include <stdio.h>

char pb_get_piece_char(const BBPieceType pt, const int white)
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

char* pb_get_piece_unicode(const BBPieceType pt, const int white)
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
                return	(white) ? "\xE2\x99\x99" : "\xE2\x99\x9F\xEF\xB8\x8E" ; /* black pawn is longer because it must be forced to render as non emoji version */
        default:
                return	"";
	}
}

char* pb_get_piece_unicode_from_ascii(const char c)
{
	switch(c) {
        case 'K':
                return "\xE2\x99\x94";
        case 'Q':
                return "\xE2\x99\x95";
        case 'R':
                return "\xE2\x99\x96";
        case 'B':
                return "\xE2\x99\x97";
        case 'N':
                return "\xE2\x99\x98";
        case 'P':
                return "\xE2\x99\x99";
        case 'k':
                return "\xE2\x99\x9A";
        case 'q':
                return "\xE2\x99\x9B";
        case 'r':
                return "\xE2\x99\x9C";
        case 'b':
                return "\xE2\x99\x9D";
        case 'n':
                return "\xE2\x99\x9E";
        case 'p':
                return "\xE2\x99\x9F\xEF\xB8\x8E"; /* black pawn is longer because it must be forced to render as non emoji version */
        default:
                return	"";
	}
}

int pb_get_board_str(const struct BBBoardState bs, char* s, const size_t len_s)
{
        int i;
        enum {LEN_INDICES = 89};
        int indices[LEN_INDICES];
        BBPieceType t;

        if (len_s < 65)
                return 1;
        /* intialise the whole str to " " */
        for (i = 0; i < 64; i++){
                s[i] = ' ';
        }
        s[64] = '\0';

        /* loop through all the white and black pieces and set their piece chars in the board string */
	for(t = BB_T_PAWN; t < BB_T_COUNT; t++){
                int num_indices = bb_get_piece_indices(bs.white_pieces[t], indices, LEN_INDICES);
                for (i = 0; i < num_indices; i++){
                        s[indices[i]] = pb_get_piece_char(t, 1);
                }
                num_indices = bb_get_piece_indices(bs.black_pieces[t], indices, LEN_INDICES);
                for (i = 0; i < num_indices; i++){
                        s[indices[i]] = pb_get_piece_char(t, 0);
                }
	}
        return 0;
}

int pb_get_fen(const struct BBBoardState bs, char* s, const size_t len_s)
{
        enum {LEN_BUFF = 65};
        char tmp[LEN_BUFF];
        int count = 0;
        int index = 0;
        int i;

        if (len_s < 89)
                return -1;
        pb_get_board_str(bs, tmp, LEN_BUFF); /* should probably check error here */

        for (i = 0; i < 64; i++){
                if ((i > 0) && (i % 8 == 0)) {
                        if (count > 0) {
                                s[index++] = '0' + count; /* convert int to ascii char, '0' is decimal 48, count should never be over 8 */
                                count = 0;
                        }
                        s[index++] = '/';
                }
                if (tmp[i] == ' ') {
                        count++;
                } else {
                        if (count > 0) {
                                s[index++] = '0' + count; /* convert int to ascii char, '0' is decimal 48, count should never be over 8 */
                                count = 0;
                        }
                        s[index++] = tmp[i];
                }
        }

        s[index++] = ' ';
        s[index++] = bs.turn_white ? 'w' : 'b';
        s[index++] = ' ';

        count = index;
        if (bs.castling_white_king_side)
                s[index++] = 'K';
        if (bs.castling_white_queen_side)
                s[index++] = 'Q';
        if (bs.castling_black_king_side)
                s[index++] = 'k';
        if (bs.castling_black_queen_side)
                s[index++] = 'q';
        if (count == index)
                s[index++] = '-';
        s[index++] = ' ';

        if (bs.en_passant_square == BB_0) {
                s[index++] = '-';
        } else {
                char square_str[3];
                int valid;
                valid = bb_get_square_str(bs.en_passant_square, square_str, 3);
                if (valid < 0)
                        return -1;
                s[index++] = square_str[0];
                s[index++] = square_str[1];
        }
        s[index++] = ' ';

        if (bs.halfmove_clock > 50)
                return -1;

        sprintf(tmp, "%d", bs.halfmove_clock);
        i = 0;
        while (tmp[i]) 
                s[index++] = tmp[i++];
        s[index++] = ' ';

        if (bs.halfmove_clock > 1000)
                return -1;

        sprintf(tmp, "%d", bs.fullmove_clock);
        i = 0;
        while (tmp[i]) 
                s[index++] = tmp[i++];

        s[index++] = '\0';

        if ((size_t)index > len_s)
                return -1;

        return index;
}

void pb_print_board(const struct BBBoardState bs)
{
        enum {LEN_BOARD_STR = 65};
        enum {LEN_BUFF = 20};
        char board_str[LEN_BOARD_STR];
        char tmp_buff[LEN_BUFF];
        int i, j;

        pb_get_board_str(bs, board_str, LEN_BOARD_STR);
        td_reset_colour();

	for(i = 0; i < 8; i++){
                /* format and print the rank number */
                sprintf(tmp_buff, "%i  ", 8-i);
                td_puts(tmp_buff, FG_WHITE, BG_BLACK);
                for(j = 0; j < 8; j++){
                        char c = board_str[i * 8 + j];
                        if (c == ' ') {
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

void pb_print_board_fancy(const struct BBBoardState bs)
{
        enum {LEN_BOARD_STR = 65};
        enum {LEN_BUFF = 20};
        char board_str[LEN_BOARD_STR];
        char tmp_buff[LEN_BUFF];
        int i, j;

        pb_get_board_str(bs, board_str, LEN_BOARD_STR);
        td_reset_colour();

	for(i = 0; i < 8; i++){
                /* format and print the rank number */ 
                sprintf(tmp_buff, "%i  ", 8-i);
                td_puts(tmp_buff, FG_WHITE, BG_BLACK);

                for(j = 0; j < 8; j++){
                        char *fg = FG_BLACK;
                        char *bg = ((i + j) % 2) ? BG_BROWN : BG_CREAM;
                        char c = board_str[i * 8 + j];
                        char *p = pb_get_piece_unicode_from_ascii(c);
                        if (c == ' ')
                                td_puts(" ", fg, bg);
                        else
                                td_puts(p, fg, bg);
                        td_puts(" ", fg, bg);
                }
                td_reset_colour();
                putchar('\n');
	}
        td_puts( "   A B C D E F G H\n", FG_WHITE, BG_BLACK);
        td_reset_colour();
}
