#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

/* A bitboard will be a uint64_t where each bit is a square on the chessboard
 * The bits will read left to right top to bottom, as if reading the squares out
 * The MSB will be A8, the LSB will be H1
 */


typedef enum {
	BB_T_PAWN,
	BB_T_KNIGHT,
	BB_T_BISHOP,
	BB_T_ROOK,
	BB_T_QUEEN,
	BB_T_KING,
	BB_T_COUNT
} BBPieceType;

const uint64_t BB_0 = 0x0000000000000000;
const uint64_t BB_1 = 0x0000000000000001;

struct BBBoardState {
        uint64_t white_pieces[BB_T_COUNT];
        uint64_t black_pieces[BB_T_COUNT];
        int turn_white;
        int castling_white_king_side;
        int castling_white_queen_side;
        int castling_black_king_side;
        int castling_black_queen_side;
        uint64_t en_passant_square; /* target square, example pawn moves e2e4, target square is e3 */
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
        bs.en_passant_square = BB_0;
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

void bb_print_binary(const uint64_t bb)
{
        printf("Bitboard hex: %016" PRIX64 "\n", bb);
        int rank, file;
        for(rank = 7; rank > -1; rank--){
                for(file = 7; file > -1; file--){
                        uint64_t mask = BB_1 << (rank * 8 + file);
                        putchar((bb & mask) ? '1' : '0');
                }
                putchar('\n');
        }
}

/* get a list of indices where the bitboard is true
obviously we can have max 1 everywhere so output len must be at least 64
returns the number of positive indices */
int bb_get_piece_indices(const uint64_t bb, int* indices, const size_t len_indices)
{
        assert(len_indices >= 64);
        int index = 0;
        int i;
        for (i = 0; i < 64; i++){
                uint64_t mask = BB_1 << i;
                if (bb & mask) {
                        indices[index++] = 63 - i; /* flip the index, as I want it to be from left to right as you look at a uint64_t */
                }
        }
        return index;
}

/* Given an index that is within the range [0 64) 
 * add its square as a human readable string to the buffer
 * eg index 0 -> "a8", index 60 -> "e1"
 * length of the buffer must be at least 3
 * returns the number of chars used (including terminating null)
 */
int bb_get_sqaure_chars(const int i, char* s, const size_t len_s)
{
        assert(len_s > 2);
        int rank = 7 - i / 8;
        int file = i % 8;
        s[0] = file + 'a';
        s[1] = rank + '1';
        s[2] = '\0';
        return 3;

}
#endif /*BITBOARD_H*/
