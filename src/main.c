#include <stdio.h>
#include <stdint.h>
#include "print_board.h"
#include "bitboard.h"
#include "player_moves.h"

int main(){
	struct BBBoardState bs = bb_init_board_state();

        size_t len_buff = 89;
        char buff[len_buff];
        pb_get_fen(bs, buff, len_buff);
        printf("FEN str: %s\n\n", buff);

        bb_print_binary(bs.black_pieces[BB_T_KNIGHT]);

        pb_print_board(bs);
        printf("\n");
        pb_print_board_fancy(bs);

        char input[50];
        int win = 0;
        while (!win){
                printf("Enter move: ");
                scanf("%49s", input);
                /* check valid input */
                int valid = pm_check_move_str(input);
                if (valid != 0) {
                        printf("Error: check move returned: %i\n", valid);
                        printf("You didn't enter a move on the board. Your move: %s\n", input);
                        printf("Moves must be of the form [start_file][start_rank][end_file][end_rank]\n");
                        printf("Example: 'e2e4'\n");
                        continue;
                }
                BBPieceType type;
                int white;
                uint64_t start_square;
                valid = pm_find_piece(bs, input, &start_square, &type, &white);
                if (valid !=0) {
                        printf("Did not find a piece on starting square. Your move %s\n", input);
                }
                printf("Piece type: %d\n", type);
                printf("Piece is white: %d\n", white);
                printf("Starting square: \n");
                bb_print_binary(pm_get_square(input));
                /* check valid move */
                /* play move */
                /* check for win */
        }

	return 0;
}
