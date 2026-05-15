#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

typedef enum {
	BB_T_PAWN,
	BB_T_KNIGHT,
	BB_T_BISHOP,
	BB_T_ROOK,
	BB_T_QUEEN,
	BB_T_KING,
	BB_T_ALL,
	BB_T_COUNT
} BBPieceType;

char* bb_get_piece_char(BBPieceType pt, int white)
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

void bb_init_player_pieces(uint64_t* pieces)
{
	pieces[BB_T_PAWN] 	= 0xFF << 8; 	/*0b1111111100000000*/
	pieces[BB_T_KNIGHT] 	= 0x42; 	/*0b01000010*/
	pieces[BB_T_BISHOP] 	= 0x24; 	/*0b00100100*/
	pieces[BB_T_ROOK] 	= 0x81; 	/*0b10000001*/
	pieces[BB_T_QUEEN] 	= 0x08; 	/*0b00001000*/
	pieces[BB_T_KING] 	= 0x08; 	/*0b00010000*/
};

uint64_t _bb_rotate_piece(uint64_t bb)
{
        return 0;
}

struct bb_board_state {
        uint64_t white_pieces[BB_T_COUNT];
        uint64_t black_pieces[BB_T_COUNT];
        int turn_white;
};



#endif /*BITBOARD_H*/
