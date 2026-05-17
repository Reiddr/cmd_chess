#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

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
	pieces[BB_T_PAWN] 	= 0x000000000000FF00; 	/*0b1111111100000000*/
	pieces[BB_T_KNIGHT] 	= 0x0000000000000042; 	/*0b01000010*/
	pieces[BB_T_BISHOP] 	= 0x0000000000000024; 	/*0b00100100*/
	pieces[BB_T_ROOK] 	= 0x0000000000000081; 	/*0b10000001*/
	pieces[BB_T_QUEEN] 	= 0x0000000000000010; 	/*0b00010000*/
	pieces[BB_T_KING] 	= 0x0000000000000008; 	/*0b00001000*/
};

struct BBBoardState bb_init_board_state(void)
{
        struct BBBoardState bs;
        bb_init_player_pieces(bs.white_pieces);
        bb_init_player_pieces(bs.black_pieces);
        bs.turn_white = 1;
        return bs;
}

void bb_print_binary(const uint64_t bb){
        printf("Bitboard hex: %016" PRIX64 "\n", bb);
        int i, j;
        for(i = 7; i > -1; i--){
                for(j = 7; j > -1; j--){
                        uint64_t mask = 1ULL << (i * 8 + j);
                        putchar((bb & mask) ? '1' : '0');
                }
                putchar('\n');
        }
}

uint64_t bb_rotate(uint64_t bb)
{
        return 0;
}

#endif /*BITBOARD_H*/
