#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stddef.h>

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

static const uint64_t BB_0 = 0x0000000000000000;
static const uint64_t BB_1 = 0x0000000000000001;

struct BBBoardState {
        uint64_t white_pieces[BB_T_COUNT];
        uint64_t black_pieces[BB_T_COUNT];
        int turn_white;
        /* castling bools, 1 if true, 0 if false */
        int castling_white_king_side;
        int castling_white_queen_side;
        int castling_black_king_side;
        int castling_black_queen_side;
        uint64_t en_passant_square; /* target square, example pawn moves e2e4, target square is e3 */
        int halfmove_clock; /* halfmoves since the last pawn move or piece capture (for 50 move rule) */
        int fullmove_clock; /* number of moves, increments on black's turn */
};

/* Initialises a bitboard to the start of a game
 */
struct BBBoardState bb_init_board_state(void);

/* Prints a bitboard, 
 * will first print the hex then print the bb in a 8x8 grid
 */
void bb_print_binary(const uint64_t bb);

/* Get a list of indices where the bitboard is true
obviously we can have max 1 everywhere so output len must be at least 64
returns the number of positive indices */
int bb_get_piece_indices(const uint64_t bb, int* indices, const size_t len_indices);

/* Given an index in the range [0 64)
 * get its rank and file
 * these are indices in the range [0 7]
 * where (0, 0) is bottom left of the board
 * returns 0 on pass and 1 on fail if index is out of bounds
 */
int bb_get_rank_file_from_index(const int i, int* rank, int* file);

/* Given an index that is within the range [0 64) 
 * add its square as a human readable string to the buffer
 * eg index 0 -> "a8", index 60 -> "e1"
 * length of the buffer must be at least 3
 * returns the number of chars used (including terminating null)
 */
int bb_get_square_str_from_index(const int i, char* s, const size_t len_s);

/* Given a bitboard return the square string of the first piece on it
 * returns a negative number on fail
 * returns the number of characters used in the buffer (usually 3)
*/
int bb_get_square_str(const uint64_t bb, char* s, const size_t len_s);

/* Given a bitboard count the number of pieces on it
 * returns the count of pieces, guaranteed to be between 0 and 64 inclusive
 */
int bb_get_num_pieces(uint64_t bb);

/* Get a list of masks for every piece on the bitboard
obviously we can have max 1 everywhere so output len must be at least 64
returns the number of masks created */
int bb_split_masks(const uint64_t bb, uint64_t* masks, const size_t len_masks);

/* A function to get a mask of all the pieces in a bitboard array
 * Essentially OR all masks in array
 * returns 0 on success, result is stored in bb
 */
int bb_merge_masks(uint64_t *bb, const uint64_t *masks, const size_t len_bb);

/* A function to take in the board state and a square return piece type and colour
 * will use the first result found, ie will not check the board state validity
 * returns 0 if allgood
 * positive if no piece is found
 */
int bb_find_piece(const struct BBBoardState *bs, const uint64_t start_square, BBPieceType* type, int* white);

#endif /*BITBOARD_H*/
