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
	BB_T_COUNT
} BBPieceType;

struct BBBoardState {
        uint64_t white_pieces[BB_T_COUNT];
        uint64_t black_pieces[BB_T_COUNT];
        int turn_white;
};

void bb_init_player_pieces(uint64_t* pieces)
{
	pieces[BB_T_PAWN] 	= 0xFF << 8; 	/*0b1111111100000000*/
	pieces[BB_T_KNIGHT] 	= 0x42; 	/*0b01000010*/
	pieces[BB_T_BISHOP] 	= 0x24; 	/*0b00100100*/
	pieces[BB_T_ROOK] 	= 0x81; 	/*0b10000001*/
	pieces[BB_T_QUEEN] 	= 0x08; 	/*0b00001000*/
	pieces[BB_T_KING] 	= 0x08; 	/*0b00010000*/
};

struct BBBoardState bb_init_board_state(void)
{
        struct BBBoardState bs;
        bb_init_player_pieces(bs.white_pieces);
        bb_init_player_pieces(bs.black_pieces);
        bs.turn_white = 1;
        return bs;
}

uint64_t bb_rotate(uint64_t bb)
{
        return 0;
}

#endif /*BITBOARD_H*/
