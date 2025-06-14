#ifndef PRINT_BOARD_H
#define PRINT_BOARD_H
#include <stdio.h>
#include <ansi_codes.h>
#include <bitboard.h>

int byte_print(uint8_t byte, char space, char* colour){
	int i = 0;
	printf("%s%c", colour, space);
	uint8_t bit;
	for(i=0; i<8; i++){
		bit = (byte >> i) && 0x01;
		printf(" %u |", bit);
	}
	printf("\n" RESET);
}

int bitboard_print(uint64_t bb){
	uint8_t rank;
	int i;
	for(i = 0; i<8; i++){
		rank = bb >> (i*8);
		byte_print(rank, '|', YELLOW);
	}
}
#endif /*PRINT_BOARD_H*/
