#include <stdio.h>
#include <stdint.h>
#include "print_board.h"
#include "bitboard.h"

int main(){
	struct BBBoardState bs = bb_init_board_state();
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
