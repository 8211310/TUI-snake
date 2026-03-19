#include "snake.h"


void errorMessage(char * input){
	titleString title = createString("Error!");
	titleString message = createString(input);
	attron(COLOR_PAIR(COLOR_RED));
	mvprintw(LINES/2-1, (COLS - title.len)/2,"%s", title.str);
	mvprintw(LINES/2, (COLS - message.len)/2,"%s", message.str);
	attroff(COLOR_PAIR(COLOR_RED));
	refresh();
	getch();
}









typedef struct snakeNode{
	int x;
	int y;
	struct snakeNode *next;
}node;


typedef struct structWindow{
	int height;
	int width;
	int startx;
	int starty;
	WINDOW *win;
}window;

void initWindowParameters(window *mainGame, window *menu){
	menu->width = 40;
	mainGame->height = LINES - 2*2;
	mainGame->width = COLS - 3*2 - menu_width;
	mainGame->startx = mainGame->starty = 3;
}

void createWindow(window *param){
	param->win = newwin(param->height, param->width, param->startx, param->starty);
}



int Snake(){


	/*Define Window*/
	window mainGameEntity;
	window *mainGame = &mainGameEntity;
	window menuEntity;
	window *menu = &menuEntity;

	initWindowParameters(&mainGame, &menu);
	

	createWindow(mainGame);
	createWindow(menu);


	int theme_color = COLOR_YELLOW;
	wattron(mainGame, COLOR_PAIR(theme_color));
	box(mainGame,0,0);
	mvwprintw(mainGame, 0, 2, "Snake Game");
	wattroff(mainGame, COLOR_PAIR(theme_color));
	wrefresh(mainGame);	
	

	/*Define Menu*/
	WINDOW* menu = newwin(height, menu_width, startx, starty+width+1);
	int menu_color = COLOR_GREEN;




	/*Basic set of snake*/
	char Snake_body = '@';
	
	int Snake_head_color = COLOR_RED;
	int Snake_body_color = COLOR_CYAN;

	int init_length = 9;


	/*Check if the set is valid*/
	if(init_length > width -2){
		errorMessage("init_length is longer than the width of screen.");
#ifdef EXIT_WITH_ERRORS
		exit(1);
#endif
	}


	/*Draw Menu*/
	wattron(menu, COLOR_PAIR(menu_color));
	wmove(menu,2,0);
	wprintw(menu,"Score Board");
	for(int i =0; i < height/6; i++){
		wprintw(menu, "\n");
	}
	titleString snakeLength = createString("Snake Length:");
	titleString level = createString("Level ");
	wprintw(menu, "%s", snakeLength.str);
	int menu_list_width = 2;
	for(int i = 0; i < menu_list_width; i++){
		wprintw(menu, "\n");
	}
	wattroff(menu, COLOR_PAIR(menu_color));

	wattron(menu, COLOR_PAIR(COLOR_RED));
	mvwprintw(menu, 2+height/6, snakeLength.len, "%d", init_length);
	wattroff(menu, COLOR_PAIR(COLOR_RED));

	wrefresh(menu);
	/*Creating Snake*/
	node *head = malloc(sizeof (node));
	head->x = height /2;
	head->y = width /2 + init_length/2;
	node *tmp_last = head;
	for(int i = 1; i < init_length ; i++){
		node *tmp_node = malloc(sizeof (node));
		tmp_node -> x = head ->x;
		tmp_node -> y = head ->y - i;
		tmp_last -> next = tmp_node;
		tmp_last = tmp_node;
	}
	tmp_last -> next = NULL;

	/*Draw Snake*/
	tmp_last = head;
	int if_head = 1;
	while(1){
		if(if_head) wattron(mainGame, COLOR_PAIR(Snake_head_color));
		else wattron(mainGame, COLOR_PAIR(Snake_body_color));
		mvwprintw(mainGame, tmp_last->x,tmp_last->y, "%c", Snake_body);
		if(if_head){
			wattroff(mainGame, COLOR_PAIR(Snake_head_color));
			if_head = 0;
		}
		else wattroff(mainGame, COLOR_PAIR(Snake_body_color));
		if(tmp_last -> next){
			tmp_last = tmp_last -> next;
		}else{
			break;
		}
	}
	node *tail = tmp_last;

	/*Draw How to play*/
	wattron(mainGame, COLOR_PAIR(theme_color));
	titleString help= createString("Use w,a,s,d as directions to play");
	mvwprintw(mainGame, height*2/3, (width - help.len)/2, "%s", help.str);
	wattroff(mainGame, COLOR_PAIR(theme_color));
	wrefresh(mainGame);
	getch();


	/*Main game*/
	char directions[4] = {'w','a','s','d'};
	char direction = 'd'
	int delay = 300;
	while(1){
		timeout(delay);
		switch(getch()){
			case direction:
				
	return 0;
}

/*
#ifdef DEBUG
int main(){
	initAll();
	Snake();
}
#endif
*/
DEBUG_MAIN(Snake);
