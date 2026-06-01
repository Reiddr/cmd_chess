#ifndef PIECE_MOVES_H
#define PIECE_MOVES_H 

#include <stdint.h>
#include "bitboard.h"

typedef enum {
        PM_DIR_NW,
        PM_DIR_N,
        PM_DIR_NE,
        PM_DIR_E,
        PM_DIR_SE,
        PM_DIR_S,
        PM_DIR_SW,
        PM_DIR_W,
        PM_DIR_COUNT,
} PMDirection;

/* function to slide a piece a single move in a direction defined by PMDirection */
uint64_t pm_slide_piece(const uint64_t bb, const PMDirection d)
{
        switch (d) {
        case PM_DIR_NW:
                return bb << 9;
        case PM_DIR_N:
                return bb << 8;
        case PM_DIR_NE:
                return bb << 7;
        case PM_DIR_E:
                return bb >> 1;
        case PM_DIR_SE:
                return bb >> 9;
        case PM_DIR_S:
                return bb >> 8;
        case PM_DIR_SW:
                return bb >> 7;
        case PM_DIR_W:
                return bb << 1;
        default:
                return BB_0;
        }
}

/* The following functions will get the possible moves of the pieces
 * as if they are the only one on the board
 * ie, these functions will not take into account board state
 */

/* Pawns can move forward a single space, 
 * take diagonally forwards a single space,
 * and move 2 spaces if they are on the second or eighth rank for white or black respectively
 * as pawns are special the captures are returned in a separate bitboard
 */
uint64_t pm_get_pawn_moves(const uint64_t bb, const int white, uint64_t* captures)
{
        assert(bb_get_num_pieces(bb) == 1);

        uint64_t rank_mask = 0xFF00ULL;  
        if (!white)
                rank_mask = rank_mask << (5 * 8);
        uint64_t left_mask  = 0x8080808080808080;
        uint64_t right_mask = 0x0101010101010101;

        /* advance the pawn */
        uint64_t moves = (white) ? bb << 8 : bb >> 8;

        /* add the diagonal moves only if we aren't on an edge */
        if (!(moves & left_mask))
                *captures = moves << 1;
        if (!(moves & right_mask))
                *captures = *captures | (moves >> 1);

        /* shift another rank if we were on a starting square */
        if (rank_mask & bb) 
                moves = moves | ((white) ? moves << 8 : moves >> 8);

        return moves;
}

/* Knights moves in an L, 2 files, 1 rank, or vice versa
 */
uint64_t pm_get_knight_moves(const uint64_t bb) 
{
        int indices[64];
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        assert(num_indices == 1);
        int rank, file;
        bb_get_rank_file_from_index(indices[0], &rank, &file);

        /* go around knight moves clockwise starting in top left */
        uint64_t moves = BB_0;
        if (rank < 6 && file > 0)
                moves |= bb << 17;
        if (rank < 6 && file < 7)
                moves |= bb << 15;
        if (rank < 7 && file < 6)
                moves |= bb << 6;
        if (rank > 0 && file < 6)
                moves |= bb >> 10;
        if (rank > 1 && file < 7)
                moves |= bb >> 17;
        if (rank > 1 && file > 0)
                moves |= bb >> 15;
        if (rank > 0 && file > 1)
                moves |= bb >> 6;
        if (rank < 7 && file > 1)
                moves |= bb << 10;
        return moves;
}

/* Rook moves, all along a rank or file
 */
uint64_t pm_get_rook_moves(const uint64_t bb) 
{
        int indices[64];
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        assert(num_indices == 1);
        int rank, file;
        bb_get_rank_file_from_index(indices[0], &rank, &file);

        uint64_t left_mask  = 0x8080808080808080;
        uint64_t bottom_mask  = 0x00000000000000FF;

        uint64_t moves = BB_0;
        moves |= left_mask >> file;
        moves ^= bottom_mask << (rank * 8); /* xor to remove starting square */
        return moves;
}

/* Bishop moves, all along the intersecting diagonals
 */
uint64_t pm_get_bishop_moves(const uint64_t bb) 
{
        int indices[64];
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        assert(num_indices == 1);
        int rank, file;
        bb_get_rank_file_from_index(indices[0], &rank, &file);

        printf("Rank: %d, File: %d\n", rank, file);
        /* go through the quadrants clockwise starting top left */
        uint64_t moves = BB_0;
        int squares_to_move, i;
        squares_to_move = (7 - rank > file) ? file : 7 - rank;
        printf("Squares top left: %d\n", squares_to_move);
        for (i = 1; i <= squares_to_move; i++)
                        moves |= bb << 9 * i;
        squares_to_move = (rank > file) ? 7 - rank : 7 - file;
        printf("Squares top right: %d\n", squares_to_move);
        for (i = 1; i <= squares_to_move; i++)
                        moves |= bb << 7 * i;
        squares_to_move = (rank > 7 - file) ? 7 - file : rank;
        printf("Squares bottom right: %d\n", squares_to_move);
        for (i = 1; i <= squares_to_move; i++)
                        moves |= bb >> 9 * i;
        squares_to_move = (7 - rank > 7 - file) ? rank : file;
        printf("Squares bottom left: %d\n", squares_to_move);
        for (i = 1; i <= squares_to_move; i++)
                        moves |= bb >> 7 * i;
        return moves;
}

/* Queen moves, combination of bishop and rook
 */
uint64_t pm_get_queen_moves(const uint64_t bb)
{
        uint64_t moves = pm_get_rook_moves(bb);
        moves |= pm_get_bishop_moves(bb);
        return moves;
}

/* King moves, all directions a single square 
 */
uint64_t pm_get_king_moves(const uint64_t bb)
{
        const uint64_t left_mask  = 0x8080808080808080;
        const uint64_t right_mask = 0x0101010101010101;
        uint64_t moves = BB_0;
        /* both N and S slides will bit shift off the board but the E and W slides will wrap */
        moves |= pm_slide_piece(bb, PM_DIR_N);
        moves |= pm_slide_piece(bb, PM_DIR_S);
        if (!(bb & right_mask)) {
                moves |= pm_slide_piece(bb, PM_DIR_NE);
                moves |= pm_slide_piece(bb, PM_DIR_E);
                moves |= pm_slide_piece(bb, PM_DIR_SE);
        }
        if (!(bb & left_mask)) {
                moves |= pm_slide_piece(bb, PM_DIR_NW);
                moves |= pm_slide_piece(bb, PM_DIR_W);
                moves |= pm_slide_piece(bb, PM_DIR_SW);
        }
        return moves;
}

#endif /*PIECE_MOVES_H*/
