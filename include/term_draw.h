#ifndef TERM_DRAW_H
#define TERM_DRAW_H

#include <ansi_codes.h>
#include <types.h>

int td_puts(char* s, char* fg, char* bg);

int td_cursor_up(uint16 n);
int td_cursor_down(uint16 n);
int td_cursor_left(uint16 n);
int td_cursor_right(uint16 n);

int td_reset_colour(void);

int td_clear_screen(void);

int td_clear_line(void);

int td_get_term_size(uint16* x, uint16* y);

#endif /*TERM_DRAW_H*/
