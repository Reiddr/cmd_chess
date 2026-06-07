#ifndef ANSI_CODES_H
#define ANSI_CODES_H

#define CLEAR_SCREEN	"\033[2J"
#define CLEAR_LINE	"\033[2K"
#define RESET 		"\033[0m"

#define FG_BLACK   	"\033[30m"
#define FG_RED   	"\033[31m"
#define FG_GREEN 	"\033[32m"
#define FG_YELLOW	"\033[33m"
#define FG_BLUE 	"\033[34m"
#define FG_MAGENTA 	"\033[35m"
#define FG_CYAN 	"\033[36m"
#define FG_WHITE 	"\033[37m"
#define FG_DEFAULT 	"\033[39m"

#define BG_BLACK   	"\033[40m"
#define BG_RED   	"\033[41m"
#define BG_GREEN 	"\033[42m"
#define BG_YELLOW	"\033[43m"
#define BG_BLUE 	"\033[44m"
#define BG_MAGENTA 	"\033[45m"
#define BG_CYAN 	"\033[46m"
#define BG_WHITE 	"\033[47m"
#define BG_DEFAULT 	"\033[49m"

#define BG_CREAM 	"\033[48;5;230m"
#define BG_BROWN	"\033[48;5;95m"
#define FG_OFFWHITE	"\033[38;5;253m"
#define FG_OFFBLACK	"\033[38;5;234m"

#endif /*ANSI_CODES_H*/
