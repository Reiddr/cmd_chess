#include <stdio.h>
#include <stdint.h>
#include "print_board.h"
#include "bitboard.h"
#include "player_input.h"
#include "piece_moves.h"

int main(){
	struct BBBoardState bs = bb_init_board_state();

        size_t len_buff = 89;
        char buff[len_buff];
        pb_get_fen(bs, buff, len_buff);
        printf("FEN str: %s\n\n", buff);

        int num_pawns = bb_get_num_pieces(bs.white_pieces[BB_T_PAWN]);
        printf("Number of white pawns: %d\n", num_pawns);

        pb_print_board(bs);
        printf("\n");
        pb_print_board_fancy(bs);

        char input[50];
        int win = 0;
        while (!win){
                printf("Enter move: ");
                scanf("%49s", input);

                /* check valid input */
                int valid = pi_check_move_str(input);
                if (valid != 0) {
                        printf("Error: check move returned: %i\n", valid);
                        printf("You didn't enter a move on the board. Your move: %s\n", input);
                        printf("Moves must be of the form [start_file][start_rank][end_file][end_rank]\n");
                        printf("Example: 'e2e4'\n");
                        continue;
                }

                /* get the piece type */
                BBPieceType type;
                int white;
                uint64_t start_square;
                valid = pi_find_piece(bs, input, &start_square, &type, &white);
                if (valid !=0) {
                        printf("Did not find a piece on starting square. Your move %s\n", input);
                }
                printf("Piece type: %d\n", type);
                printf("Piece is white: %d\n", white);
                printf("Starting square: \n");
                bb_print_binary(start_square);

                char start_square_english[5];
                bb_get_square_str(start_square, start_square_english, 5);
                printf("Starting square as string is: %s\n", start_square_english);

                /* get all moves the piece can make */
                uint64_t knight_moves = pm_get_knight_moves(start_square);
                printf("Knight moves: \n");
                bb_print_binary(knight_moves);
                /* check valid move */
                /* play move */
                /* check for win */
        }

	return 0;
}
