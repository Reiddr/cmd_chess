#include "board_moves.h"
#include "bitboard.h"
#include "piece_moves.h"
#include <stdint.h>

int bm_get_valid_moves_board(const struct BBBoardState *bs, struct BMMove *moves, const size_t len_moves)
{
        uint64_t ally_pieces, enemy_pieces;
        int masks_allocated;
        masks_allocated = bb_merge_masks(&ally_pieces, (bs->turn_white ? bs->white_pieces : bs->black_pieces), BB_T_COUNT);
        masks_allocated = bb_merge_masks(&enemy_pieces, (!bs->turn_white ? bs->white_pieces : bs->black_pieces), BB_T_COUNT);
        /* iterate through ally pieces and get valid moves for each piece */
        if (!(start & ally_pieces))
                return -1;
        return 0;
}

int bm_get_valid_moves_piece(const struct BBBoardState *bs, const uint64_t start, struct BMMove *moves, const size_t len_moves)
{
        uint64_t possible_captures, possible_moves, ally_pieces, enemy_pieces;
        int valid, num_masks, white;
        BBPieceType pt;

        valid = bb_merge_masks(&ally_pieces, (bs->turn_white ? bs->white_pieces : bs->black_pieces), BB_T_COUNT);
        if (valid != 0)
                return -1;
        valid = bb_merge_masks(&enemy_pieces, (!bs->turn_white ? bs->white_pieces : bs->black_pieces), BB_T_COUNT);
        if (valid != 0)
                return -2;

        valid = bb_find_piece(bs, start, &pt, &white);
        if (valid != 0)
                return -3;

        switch(pt) {
        case (BB_T_PAWN):
                valid = pm_get_pawn_moves(start, bs->turn_white, &possible_moves, &possible_captures);
                /* need to handle special case of pawns capturing diagonally only if an enemy piece is present or enpassant */
                possible_captures &= (enemy_pieces | bs->en_passant_square);
                possible_moves |= possible_captures;
                break;
        case (BB_T_KNIGHT):
                valid = pm_get_knight_moves(start, &possible_moves);
                break;
        case (BB_T_BISHOP):
                valid = pm_get_bishop_moves(start, &possible_moves);
                break;
        case (BB_T_ROOK):
                valid = pm_get_rook_moves(start, &possible_moves);
                break;
        case (BB_T_QUEEN):
                valid = pm_get_queen_moves(start, &possible_moves);
                break;
        case (BB_T_KING):
                valid = pm_get_king_moves(start, &possible_moves);
                break;
        default:
                return -1;
        }

        if (valid != 0)
                return -2;

        possible_moves &= (possible_moves ^ ally_pieces); /* can't move to spaces occupied by ally pieces */

        num_masks = bb_split_masks(possible_moves, moves, len_moves);
        if (num_masks < 0)
                return -3;

        return num_masks;
}

int make_move(struct BBBoardState *bs, const struct BMMove *bm)
{
        return 0;
}

int in_check(const struct BBBoardState *bs, const uint64_t possible_moves)
{
        if (possible_moves & (!bs->turn_white ? bs->white_pieces[BB_T_KING] : bs->black_pieces[BB_T_KING]))
                return 1;
        else
                return 0;
}

int valid_board_state(const struct BBBoardState *bs)
{
        return 0;
}
