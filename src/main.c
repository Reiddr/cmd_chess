#include <stdio.h>
#include <stdint.h>
#include "print_board.h"
#include "bitboard.h"

int main(){
	struct BBBoardState bs = bb_init_board_state();

        size_t len_buff = 89;
        char buff[len_buff];
        pb_get_fen(bs, buff, len_buff);
        printf("FEN str: %s\n", buff);

        char input[50];
        int win = 0;
        while (!win){
                pb_print_board(bs);
                printf("Enter move: ");
                scanf("%49s", input);
                /* check valid input */
                /* check valid move */
                /* play move */
                /* check for win */
        }

	return 0;
}
