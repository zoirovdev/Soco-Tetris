#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#define WALL 	"="
#define CELL 	"#"
#define EMPTY 	" "
#define HEIGHT 	30
#define WIDTH 	60


char * board[HEIGHT][WIDTH];



void put_walls(){
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			if(i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
				board[i][j] = WALL;
			} else { 
				board[i][j] = EMPTY;
			}
		}
	}
}


void put_cells(){
	int i = 1;
	int j = rand() % WIDTH;

	board[i][j] = CELL;
}


void auto_move(){
	int cell_x = 0;
	int cell_y = 0;
	int a = 0;
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			if(strcmp(board[i][j],CELL) == 0){
				cell_x = j;
				cell_y = i;
				a = 1;
				break;
			}
		}
		if(a == 1) break;
	}

	if(cell_y+1 < HEIGHT){
		strcpy(board[cell_y][cell_x], EMPTY);
		strcpy(board[cell_y+1][cell_x], CELL);
	}
}


void printboard(){
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	int start_row = rows/2 - 15;
	int start_col = cols/2 - 30;

	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			mvprintw(start_row+i, start_col+j , "%s", board[i][j]);
		}
		printw("\n");
	}
}


void play(){
	initscr();

	printboard();		

	refresh();
	getch();
	endwin();
}


int main(){
	put_walls();
	put_cells();

	while(1){
		play();
		auto_move();
		sleep(1 % 1000);
	}
	return 0;
}
