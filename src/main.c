#include <stdio.h>
#include <stdint.h>
#include <print_board.h>
#include <bitboard.h>

int main(){
	uint64_t white_pieces[BB_T_COUNT]; 
	bb_populate_pieces(white_pieces);
	uint8_t i;
	for(i=BB_T_PAWN; i<BB_T_COUNT; i++){
		printf("%c\n", bb_get_piece_char(i));
		bitboard_print(white_pieces[i]); 
	}

	return 0;
}
