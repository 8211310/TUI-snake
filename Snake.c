#include "snake.h"



void errorMessage(char * input){
	/*Yes, if you want to debug, just write 
	 * this function, It will print debug
	 * info to the middle of the screen and
	 * wait for your response.
	 * Just like printf. Genius idea.*/


	titleString title = createString("Error!");
	titleString message = createString(input);
	attron(COLOR_PAIR(COLOR_RED));
	mvprintw(LINES/2-1, (COLS - title.len)/2,"%s", title.str);
	mvprintw(LINES/2, (COLS - message.len)/2,"%s", message.str);
	attroff(COLOR_PAIR(COLOR_RED));
	refresh();
	getch();
}











typedef struct structWindow{
	int height;
	int width;
	int startx;
	int starty;
	int color;	/*The color is theme color.*/ 
	WINDOW *win;	/*Main window part.*/
}window;

void initWindowParameters(window *mainGame, window *menu){
	/*fixed width*/
	menu->width = 40;


	menu->height = mainGame->height = LINES - 2*2;
	mainGame->width = COLS - 3*2 - menu->width;
	
	mainGame->startx = mainGame->starty = 3;
	
	menu->startx = mainGame->startx;
	menu->starty = mainGame->starty+mainGame->width;

	/*theme*/
	mainGame->color = COLOR_YELLOW;
	menu->color = COLOR_GREEN;
}

void createWindow(window *param){
	param->win = newwin(param->height, param->width, param->startx, param->starty);
}


void drawWindow(window *param, char* title){ 

	wattron(param->win, COLOR_PAIR(param->color));
	box(param->win,0,0);
	mvwprintw(param->win, 0, 2, "%s", title);
	wattroff(param->win, COLOR_PAIR(param->color));
	wrefresh(param->win);	

}




/*snake part*/

typedef struct snakeNode{
	int x;
	int y;
	struct snakeNode *next;
}node;


typedef struct structSnake{

	char body;
	
	int head_color;
	int body_color;

	int length;

	node *head;
	node *tail;
}snake;

void createSnake(snake* param, window *mainGame);
void initDrawSnake(snake* param, window *mainGame);

void initSnakeParam(snake* param, window *mainGame){
	param -> body = '@';

	param -> head_color = COLOR_RED;
	param -> body_color = COLOR_CYAN;

	param -> length = 9;

	/*Check if the set is valid*/
	if(param->length > mainGame->width -2){
		errorMessage("init_length is longer than the width of screen.");
#ifdef EXIT_WITH_ERRORS
		exit(1);
#endif
	}

	createSnake(param, mainGame);
	initDrawSnake(param, mainGame);


}


void createSnake(snake* param, window *mainGame){

	/*Creating Snake*/
	node* tmp_head = malloc(sizeof (node));
	if (!tmp_head){
		errorMessage("malloc head node failed!");
	}
	tmp_head->x = mainGame->height /2;
	tmp_head->y = mainGame->width /2 + param->length/2;
	node *tmp_last = tmp_head;
	for(int i = 1; i < param->length ; i++){
		node *tmp_node = malloc(sizeof (node));
		if(!tmp_node){
			errorMessage("malloc body node failed!");
		}
		tmp_node -> x = tmp_head ->x;
		tmp_node -> y = tmp_head ->y - i;
		tmp_last -> next = tmp_node;
		tmp_last = tmp_node;
	}
	tmp_last -> next = NULL;

	param->head = tmp_head;
	param->tail = tmp_last;
}

void initDrawSnake(snake* param, window *mainGame){

	node *tmp_last = param->head;
	int if_head = 1;
	while(1){
		if(if_head) wattron(mainGame->win, COLOR_PAIR(param->head_color));
		else wattron(mainGame->win, COLOR_PAIR(param->body_color));
		mvwprintw(mainGame->win, tmp_last->x,tmp_last->y, "%c", param->body);
		if(if_head){
			wattroff(mainGame->win, COLOR_PAIR(param->head_color));
			if_head = 0;
		}
		else wattroff(mainGame->win, COLOR_PAIR(param->body_color));
		if(tmp_last -> next){
			tmp_last = tmp_last -> next;
		}else{
			break;
		}
	}

}


void initCreateMenu(titleString *menuList, int listNum){
	menuList[0] = createString("Snake Length:");
	menuList[1] = createString("Level ");
	menuList[2] = createString("Time using:");
}

void initDrawMenu(titleString *menuList, int listNum, window *menu, snake *mainSnake){
	wattron(menu->win, COLOR_PAIR(menu->color));
	wmove(menu->win,3,0);
	for(int i =0; i < menu->height/6; i++){
		wprintw(menu->win, "\n");
	}

	int menu_list_width = 2;
	for(int i = 0; i < listNum; i++){
		wprintw(menu->win, "%s\n", menuList[i].str);
		for(int j = 0; j < menu_list_width; j++){
			wprintw(menu->win, "\n");
		}
	}

	wattroff(menu->win, COLOR_PAIR(menu->color));

	wrefresh(menu->win);
}
void refreshMenuParam(titleString *menuList, int listNum, window *menu, snake *mainSnake){
	
	int color_of_length = COLOR_RED;
	wattron(menu->win, COLOR_PAIR(color_of_length));
	mvwprintw(menu->win, 2+menu->height/6, menuList[0].len, "%d", mainSnake->length);
	wattroff(menu->win, COLOR_PAIR(color_of_length));

	int color_of_level = COLOR_YELLOW;
	wattron(menu->win, COLOR_PAIR(color_of_level));
	mvwprintw(menu->win, 3+2+menu->height/6, menuList[1].len, "%d", 1);
	wattroff(menu->win, COLOR_PAIR(color_of_level));

	int color_of_time = COLOR_BLUE;
	wattron(menu->win, COLOR_PAIR(color_of_time));
	//mvwprintw(menu->win,3+3+2+height/6, menuList[2].len, "%d:%d", time->min, time->sec);
	wattroff(menu->win, COLOR_PAIR(color_of_time));
}


int Snake(){


	/*Define Window*/
	window mainGameEntity;
	window *mainGame = &mainGameEntity;
	window menuEntity;
	window *menu = &menuEntity;

	initWindowParameters(mainGame, menu);
	

	createWindow(mainGame);
	drawWindow(mainGame, "Snake Game");
	createWindow(menu);
	drawWindow(menu, "Score");



	snake *mainSnake = malloc(sizeof (snake));
	initSnakeParam(mainSnake, mainGame);


	/*Create Menu*/
	int listNum = 3;
	titleString menuList[listNum];
	initCreateMenu(menuList, listNum);
	initDrawMenu(menuList, listNum, menu, mainSnake);
	//refreshMenuParam(menuList, listNum, menu, mainSnake);


	/*Draw Menu*/
	/*Draw Snake*/

	/*Draw How to play*/
	wattron(mainGame->win, COLOR_PAIR(mainGame->color));
	titleString help= createString("Use w,a,s,d as directions to play");
	mvwprintw(mainGame->win, mainGame->height*2/3, (mainGame->width - help.len)/2, "%s", help.str);
	wattroff(mainGame->win, COLOR_PAIR(mainGame->color));
	wrefresh(mainGame->win);
	getch();


	/*Main game*/
	char directions[4] = {'w','a','s','d'};
	char direction = 'd';
	int delay = 300;
	/*
	while(1){
		timeout(delay);
		switch(getch()){
			case direction:
	*/			
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
