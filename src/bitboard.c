#include "bitboard.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

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
        int rank, file;
        printf("Bitboard hex: %016" PRIX64 "\n", bb);
        for(rank = 7; rank > -1; rank--){
                for(file = 7; file > -1; file--){
                        uint64_t mask = BB_1 << (rank * 8 + file);
                        putchar((bb & mask) ? '1' : '0');
                }
                putchar('\n');
        }
}

int bb_get_piece_indices(const uint64_t bb, int* indices, const size_t len_indices)
{
        int index = 0;
        int i;
        if (len_indices < 64)
                return -1;
        for (i = 0; i < 64; i++){
                uint64_t mask = BB_1 << i;
                if (bb & mask) {
                        indices[index++] = 63 - i; /* flip the index, as I want it to be from left to right as you look at a uint64_t */
                }
        }
        return index;
}

int bb_get_rank_file_from_index(const int i, int* rank, int* file)
{
        if ((i < 0) || (i > 63))
                return 1;
        *rank = 7 - i / 8;
        *file = i % 8;
        return 0;
}

int bb_get_square_str_from_index(const int i, char* s, const size_t len_s)
{
        int rank, file, valid;
        if (len_s < 3)
                return -1;
        valid = bb_get_rank_file_from_index(i, &rank, &file);
        if (valid == 1)
                return -1;
        s[0] = file + 'a';
        s[1] = rank + '1';
        s[2] = '\0';
        return 3;
}

int bb_get_square_str(const uint64_t bb, char* s, const size_t len_s)
{
        int indices[64];
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices < 1)
                return num_indices;
        return bb_get_square_str_from_index(indices[0], s, len_s);
}

int bb_get_num_pieces(uint64_t bb)
{
        int count = 0;
        int i;
        for (i = 0; i < 64; i++) { 
                if (bb & BB_1)
                        count++;
                bb = bb >> 1;
        }
        return count;
}
