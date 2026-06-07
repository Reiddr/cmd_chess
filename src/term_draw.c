#include <asm-generic/ioctls.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "term_draw.h"
#include "ansi_codes.h"


/* place the cursor at x,y  0,0 is top left*/
int td_cursor(uint16_t x, uint16_t y){
	printf("\033[%u;%uH", x, y);
	return 0;
}

/* move cursor UP n lines */
int td_cursor_up(uint16_t n){
	printf("\033[%uA", n);
	return 0;
}

/* move cursor DOWN n lines */
int td_cursor_down(uint16_t n){
	printf("\033[%uB", n);
	return 0;
}

/* move cursor LEFT n lines */
int td_cursor_left(uint16_t n){
	printf("\033[%uD", n);
	return 0;
}

/* move cursor RIGHT n lines */
int td_cursor_right(uint16_t n){
	printf("\033[%uC", n);
	return 0;
}

/* reset the terminal colours */
int td_reset_colour(void){
	printf(RESET);
	return 0;
}

/* print a string with a foreground and background colour */
int td_puts(char* s, char* fg, char* bg){
	printf("%s%s%s", fg, bg, s);
	return 0;
}

/* clear the screen */
int td_clear_screen(void){
	printf(CLEAR_SCREEN);
	return 0;
}

/* clear the line the cursor is on */
int td_clear_line(void){
	printf(CLEAR_LINE);
	return 0;
}

int td_get_term_size(uint16_t* x, uint16_t* y){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *x = w.ws_col;
    *y = w.ws_row;

    printf("Lines: %d\n", *y);
    printf("Columns: %d\n", *x);
    return 0;
}

