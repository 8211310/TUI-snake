#include "snake.h"
int main(){
	initAll();
	while(1){
		switch(Menu()){
			case '1':
				Help();
				break;
			case '2':
				Info();
				break;
			case 'q':
				endwin();
				return 0;
			default:
				Snake();
				break;
		}
	}
}

