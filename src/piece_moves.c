#include "piece_moves.h"
#include "bitboard.h"
#include <stdint.h>

uint64_t pm_slide_piece(const uint64_t bb, const PMDirection d)
{
        /* note no north or south mask needed as the bb will over or under flow */
        uint64_t west_mask  = 0x8080808080808080;
        uint64_t east_mask  = 0x0101010101010101;
        switch (d) {
        case PM_DIR_NW:
                if (bb & west_mask)
                        return BB_0;
                return bb << 9;
        case PM_DIR_N:
                return bb << 8;
        case PM_DIR_NE:
                if (bb & east_mask)
                        return BB_0;
                return bb << 7;
        case PM_DIR_E:
                if (bb & east_mask)
                        return BB_0;
                return bb >> 1;
        case PM_DIR_SE:
                if (bb & east_mask)
                        return BB_0;
                return bb >> 9;
        case PM_DIR_S:
                return bb >> 8;
        case PM_DIR_SW:
                if (bb & west_mask)
                        return BB_0;
                return bb >> 7;
        case PM_DIR_W:
                if (bb & west_mask)
                        return BB_0;
                return bb << 1;
        default:
                return BB_0;
        }
}

int pm_slide_piece_until_blocked(uint64_t bb, const PMDirection d, const uint64_t obstructions, uint64_t *moves)
{
        *moves = BB_0;
        while (bb) { /* as long as we don't slide off the board */
                bb = pm_slide_piece(bb, d);
                *moves |= bb;
                if (bb & obstructions)
                        return 0;
        }
        return 0;
}

PMMaxMoves pm_get_max_moves(BBPieceType pt)
{
        switch (pt) {
        case BB_T_PAWN:
                return PM_MAX_MOVES_PAWN;
        case BB_T_KNIGHT:
                return PM_MAX_MOVES_KNIGHT;
        case BB_T_BISHOP:
                return PM_MAX_MOVES_BISHOP;
        case BB_T_ROOK:
                return PM_MAX_MOVES_ROOK;
        case BB_T_QUEEN:
                return PM_MAX_MOVES_QUEEN;
        case BB_T_KING:
                return PM_MAX_MOVES_KING;
        default:
                return 0;
        }
}

int pm_get_pawn_moves(const uint64_t bb, const int white, uint64_t* moves, uint64_t* captures)
{
        uint64_t rank_mask  = 0xFF00;
        uint64_t left_mask  = 0x8080808080808080;
        uint64_t right_mask = 0x0101010101010101;

        if (bb_get_num_pieces(bb) != 1)
                return 1;

        if (!white)
                rank_mask = rank_mask << (5 * 8);

        /* advance the pawn */
        *moves = (white) ? bb << 8 : bb >> 8;

        /* reset captures in case it has existing data */
        *captures = BB_0;

        /* add the diagonal moves only if we aren't on an edge */
        if (!(*moves & left_mask))
                *captures = *moves << 1;
        if (!(*moves & right_mask))
                *captures |= (*moves >> 1);

        /* shift another rank if we were on a starting square */
        if (rank_mask & bb) 
                *moves |= ((white) ? *moves << 8 : *moves >> 8);

        return 0;
}

int pm_get_knight_moves(const uint64_t bb, uint64_t *moves) 
{
        int indices[64];
        int rank, file, valid;
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices != 1)
                return 1;

        valid = bb_get_rank_file_from_index(indices[0], &rank, &file);
        if (valid == 1)
                return 2;

        /* go around knight moves clockwise starting in top left */
        *moves = BB_0;
        if (rank < 6 && file > 0)
                *moves |= bb << 17;
        if (rank < 6 && file < 7)
                *moves |= bb << 15;
        if (rank < 7 && file < 6)
                *moves |= bb << 6;
        if (rank > 0 && file < 6)
                *moves |= bb >> 10;
        if (rank > 1 && file < 7)
                *moves |= bb >> 17;
        if (rank > 1 && file > 0)
                *moves |= bb >> 15;
        if (rank > 0 && file > 1)
                *moves |= bb >> 6;
        if (rank < 7 && file > 1)
                *moves |= bb << 10;
        return 0;
}

int pm_get_rook_moves(const uint64_t bb, uint64_t *moves) 
{
        int indices[64];
        int rank, file, valid;
        uint64_t left_mask  = 0x8080808080808080;
        uint64_t bottom_mask  = 0x00000000000000FF;

        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices != 1)
                return 1;
        valid = bb_get_rank_file_from_index(indices[0], &rank, &file);
        if (valid == 1)
                return 2;

        *moves = BB_0;
        *moves |= left_mask >> file;
        *moves ^= bottom_mask << (rank * 8); /* xor to remove starting square */
        return 0;
}

int pm_get_bishop_moves(const uint64_t bb, uint64_t *moves) 
{
        int indices[64];
        int rank, file, valid;
        int squares_to_move, i;
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices != 1)
                return 1;
        valid = bb_get_rank_file_from_index(indices[0], &rank, &file);
        if (valid != 0)
                return 2;

        /* go through the quadrants clockwise starting top left */
        *moves = BB_0;
        squares_to_move = (7 - rank > file) ? file : 7 - rank;
        for (i = 1; i <= squares_to_move; i++)
                        *moves |= bb << 9 * i;
        squares_to_move = (rank > file) ? 7 - rank : 7 - file;
        for (i = 1; i <= squares_to_move; i++)
                        *moves |= bb << 7 * i;
        squares_to_move = (rank > 7 - file) ? 7 - file : rank;
        for (i = 1; i <= squares_to_move; i++)
                        *moves |= bb >> 9 * i;
        squares_to_move = (7 - rank > 7 - file) ? rank : file;
        for (i = 1; i <= squares_to_move; i++)
                        *moves |= bb >> 7 * i;
        return 0;
}

int pm_get_queen_moves(const uint64_t bb, uint64_t *moves)
{
        int valid;
        uint64_t bishop_moves;
        valid = pm_get_rook_moves(bb, moves);
        if (valid != 0)
                return valid;
        valid = pm_get_bishop_moves(bb, &bishop_moves);
        if (valid != 0)
                return valid;
        *moves |= bishop_moves;
        return 0;
}

int pm_get_king_moves(const uint64_t bb, uint64_t *moves)
{
        const uint64_t left_mask  = 0x8080808080808080;
        const uint64_t right_mask = 0x0101010101010101;
        int indices[64];
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices != 1)
                return 1;
        *moves = BB_0;
        /* both N and S slides will bit shift off the board but the E and W slides will wrap */
        *moves |= pm_slide_piece(bb, PM_DIR_N);
        *moves |= pm_slide_piece(bb, PM_DIR_S);
        if (!(bb & right_mask)) {
                *moves |= pm_slide_piece(bb, PM_DIR_NE);
                *moves |= pm_slide_piece(bb, PM_DIR_E);
                *moves |= pm_slide_piece(bb, PM_DIR_SE);
        }
        if (!(bb & left_mask)) {
                *moves |= pm_slide_piece(bb, PM_DIR_NW);
                *moves |= pm_slide_piece(bb, PM_DIR_W);
                *moves |= pm_slide_piece(bb, PM_DIR_SW);
        }
        return 0;
}

int pm_get_pawn_moves_with_pieces(const uint64_t bb, const uint64_t pieces, const int white, uint64_t* moves)
{
        uint64_t rank2_mask  = 0xFF00;
        uint64_t rank3_mask  = 0xFF0000;
        uint64_t rank4_mask  = 0xFF000000;
        uint64_t pawn_moves, pawn_captures;
        int valid;

        valid = pm_get_pawn_moves(bb, white, &pawn_moves, &pawn_captures);
        if (valid != 0)
                return valid;

        if (!white) {
                rank2_mask = rank2_mask << (5 * 8);
                rank3_mask = rank3_mask << (3 * 8);
                rank4_mask = rank4_mask << (1 * 8);
        }

        if (rank3_mask & pieces & pawn_moves) /* if there is a piece on the 3 rank in the pawns way */
                pawn_moves = BB_0; /* then the pawn has no moves */
        else
                pawn_moves &= ~pieces; /* remove pawn pushes that overlap with other pieces */

        *moves = pawn_moves | (pawn_captures & pieces);

        return 0;
}

int pm_get_rook_moves_with_pieces(const uint64_t bb, const uint64_t pieces, uint64_t *moves)
{
        uint64_t tmp;
        int indices[64];
        int valid;
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices != 1)
                return 1;

        *moves = BB_0;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_N, pieces, &tmp);
        *moves |= tmp;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_S, pieces, &tmp);
        *moves |= tmp;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_E, pieces, &tmp);
        *moves |= tmp;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_W, pieces, &tmp);
        *moves |= tmp;

        if (valid != 0)
                return 2;
        return 0;
}

int pm_get_bishop_moves_with_pieces(const uint64_t bb, const uint64_t pieces, uint64_t *moves)
{
        uint64_t tmp;
        int indices[64];
        int valid;
        int num_indices = bb_get_piece_indices(bb, indices, 64);
        if (num_indices != 1)
                return 1;

        *moves = BB_0;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_NE, pieces, &tmp);
        *moves |= tmp;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_NW, pieces, &tmp);
        *moves |= tmp;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_SE, pieces, &tmp);
        *moves |= tmp;
        valid = pm_slide_piece_until_blocked(bb, PM_DIR_SW, pieces, &tmp);
        *moves |= tmp;

        if (valid != 0)
                return 2;
        return 0;
}

int pm_get_queen_moves_with_pieces(const uint64_t bb, const uint64_t pieces, uint64_t *moves)
{
        int valid;
        uint64_t bishop_moves;
        valid = pm_get_rook_moves_with_pieces(bb, pieces, moves);
        if (valid != 0)
                return valid;
        valid = pm_get_bishop_moves_with_pieces(bb, pieces, &bishop_moves);
        if (valid != 0)
                return valid;
        *moves |= bishop_moves;
        return 0;
}
