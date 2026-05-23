#include <stdio.h>
#include <stdint.h>
#include "print_board.h"
#include "bitboard.h"

int main(){
	struct BBBoardState bs = bb_init_board_state();
	// BBPieceType i;
	// for(i=BB_T_PAWN; i<BB_T_COUNT; i++){
	// 	printf("%s\n", pb_get_piece_char(i, bs.turn_white));
	// 	// pb_print_board(bs); 
	//                bb_print_binary(bs.white_pieces[i]);
	// }
        char s[65];
        pb_get_board_str(bs, s, 65);
        printf("Board string: '%s'\n", s);
        pb_print_board(bs);

	return 0;
}
