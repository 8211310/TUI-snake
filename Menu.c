#include "snake.h"
int Menu(){
	//Return the menu User want.
	/*
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	Used for init*/

	/* Adding text system
	typedef struct text{
		char* content;
		int length;
	}Text
	*/
	attron(COLOR_PAIR(COLOR_CYAN));
	titleString gameTitle = createString("Snake Game.")
	mvprintw(LINES/5,(COLS - gameTitle.len)/2,gameTitle.str);
	attroff(COLOR_PAIR(COLOR_CYAN));
	attron(COLOR_PAIR(COLOR_GREEN));
	mvprintw(LINES*2/5,(COLS - 11)/2,"Version 1.0");
	mvprintw(LINES*2/5+1,(COLS - 18)/2,"Designed By Xu8211");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_RED));
	mvprintw(LINES*3/5,(COLS - 23)/2, "Press any key to begin.");
	attroff(COLOR_PAIR(COLOR_RED));
	char n = getch();
	erase();
	return n;
}
//#define DEBUG // or -DDEBUG
#ifdef DEBUG
int main(){
	initAll();
	Menu();
}
#endif
