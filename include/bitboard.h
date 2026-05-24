#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

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
        int castling_white_king_side;
        int castling_white_queen_side;
        int castling_black_king_side;
        int castling_black_queen_side;
        char en_passant_square[3]; /* target square, example pawn moves e2e4, target square is e3 */
        int halfmove_clock; /* halfmoves since the last pawn move or piece capture (for 50 move rule) */
        int fullmove_clock; /* number of moves, increments on black's turn */
};

struct BBBoardState bb_init_board_state(void)
{
        struct BBBoardState bs;
        bs.turn_white = 1;
        bs.castling_white_king_side = 1;
        bs.castling_white_queen_side = 1;
        bs.castling_black_king_side = 1;
        bs.castling_black_queen_side = 1;
        bs.en_passant_square[0] = '-';
        bs.en_passant_square[1] = '\0';
        bs.halfmove_clock = 0;
        bs.fullmove_clock = 0;

	bs.white_pieces[BB_T_PAWN] 	= 0x000000000000FF00; 	/*0b1111111100000000*/
	bs.white_pieces[BB_T_KNIGHT] 	= 0x0000000000000042; 	/*0b01000010*/
	bs.white_pieces[BB_T_BISHOP] 	= 0x0000000000000024; 	/*0b00100100*/
	bs.white_pieces[BB_T_ROOK] 	= 0x0000000000000081; 	/*0b10000001*/
	bs.white_pieces[BB_T_QUEEN] 	= 0x0000000000000010; 	/*0b00010000*/
	bs.white_pieces[BB_T_KING] 	= 0x0000000000000008; 	/*0b00001000*/

	bs.black_pieces[BB_T_PAWN] 	= 0x00FF000000000000;	
	bs.black_pieces[BB_T_KNIGHT] 	= 0x4200000000000000;
	bs.black_pieces[BB_T_BISHOP] 	= 0x2400000000000000;
	bs.black_pieces[BB_T_ROOK] 	= 0x8100000000000000;
	bs.black_pieces[BB_T_QUEEN] 	= 0x0800000000000000;
	bs.black_pieces[BB_T_KING] 	= 0x1000000000000000;

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

/* get a list of indices where the bitboard is true
obviously we can have max 1 everywhere so output len must be at least 64
returns the number of positive indices */
int bb_get_piece_indices(uint64_t bb, int* indices, size_t len_indices){
        assert(len_indices >= 64);
        int index = 0;
        int i;
        for (i = 0; i < 64; i++){
                uint64_t mask = 1ULL << i;
                if (bb & mask) {
                        indices[index++] = 63 - i; /* flip the index, as I want it to be from left to right as you look at a uint64_t */
                }
        }
        return index;
}

#endif /*BITBOARD_H*/
