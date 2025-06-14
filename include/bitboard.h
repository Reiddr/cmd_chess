#ifndef BITBOARD_H
#define BITBOARD_H

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

char bb_get_piece_char(BBPieceType pt){
	switch(pt) {
		case BB_T_PAWN:
			return	'P';
		case BB_T_KNIGHT:
			return 	'N';
		case BB_T_BISHOP:
			return 	'B';
		case BB_T_ROOK:
			return 	'R';
		case BB_T_QUEEN:
			return 	'Q';
		case BB_T_KING:
			return	'K';
		case default:
			return	' ';
	}
}

int bb_populate_pieces(uint64_t* pieces){
	pieces[BB_T_PAWN] 	= 0xFF << 8; 	/*0b11111111*/
	pieces[BB_T_KNIGHT] 	= 0x42; 	/*0b01000010*/
	pieces[BB_T_BISHOP] 	= 0x24; 	/*0b00100100*/
	pieces[BB_T_ROOK] 	= 0x81; 	/*0b10000001*/
	pieces[BB_T_QUEEN] 	= 0x08; 	/*0b00001000*/
	pieces[BB_T_KING] 	= 0x08; 	/*0b00010000*/
	return 0;
};

/*
struct bitboard {
	 type;
	uint64_t loc;
}; */

#endif /*BITBOARD_H*/
