#include <stdio.h>
#include <stdint.h>
#include "print_board.h"
#include "bitboard.h"

int main(){
        uint64_t x = 0x0000000000FF00;
        printf("Bitboard hex: %016" PRIX64 "\n", x);
        printf("uint64_t len: %lu\n", sizeof(uint64_t));
        printf("unsigned long len: %lu\n", sizeof(unsigned long));
        printf("unsigned long long len: %lu\n", sizeof(unsigned long long));
	struct BBBoardState bs = bb_init_board_state();
	BBPieceType i;
	for(i=BB_T_PAWN; i<BB_T_COUNT; i++){
		printf("%s\n", pb_get_piece_char(i, bs.turn_white));
		// pb_print_board(bs); 
                bb_print_binary(bs.white_pieces[i]);
	}

	return 0;
}
