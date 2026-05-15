#ifndef TERM_DRAW_H
#define TERM_DRAW_H

#include <ansi_codes.h>
#include <stdint.h>

int td_puts(char* s, char* fg, char* bg);

int td_cursor_up(uint16_t n);
int td_cursor_down(uint16_t n);
int td_cursor_left(uint16_t n);
int td_cursor_right(uint16_t n);

int td_reset_colour(void);

int td_clear_screen(void);

int td_clear_line(void);

int td_get_term_size(uint16_t* x, uint16_t* y);

#endif /*TERM_DRAW_H*/
