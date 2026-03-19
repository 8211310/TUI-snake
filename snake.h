#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include "String.h"


extern int Menu();
extern int Snake();
extern void Help();
extern void Info();

static inline void initColorPairs();

static inline void initAll(){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	initColorPairs();
	curs_set(0);
	refresh();
}

static inline void initColorPairs(){
	init_pair(0,0,COLOR_BLACK);
	init_pair(1,1,COLOR_BLACK);
	init_pair(2,2,COLOR_BLACK);
	init_pair(3,3,COLOR_BLACK);
	init_pair(4,4,COLOR_BLACK);
	init_pair(5,5,COLOR_BLACK);
	init_pair(6,6,COLOR_BLACK);
	init_pair(7,7,COLOR_BLACK);
}

#ifdef DEBUG 
#define DEBUG_MAIN(func) \
int main(){ \
	initAll(); \
	func(); \
	endwin(); \
	return 0; \
} 
#else
#define DEBUG_MAIN(func)
#endif
