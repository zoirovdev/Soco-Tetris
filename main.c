#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>



#define WALL 	'='
#define CELL 	'#'
#define EMPTY 	' '
#define HEIGHT 	30
#define WIDTH 	60


char board[HEIGHT][WIDTH];



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
	int cell_x = -1;
	int cell_y = -1;
	int a = 0;
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			if(board[i][j] == CELL){
				cell_x = j;
				cell_y = i;
				a = 1;
				break;
			}
		}
		if(a == 1) break;
	}

	if(cell_y == -1 || cell_x == -1) return;
	else if(cell_y + 1 < HEIGHT - 1){
		board[cell_y][cell_x] = EMPTY;
		board[cell_y+1][cell_x] = CELL;
	}
}


void printboard(){
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	int start_row = rows/2 - 15;
	int start_col = cols/2 - 30;

	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			mvprintw(start_row+i, start_col+j , "%c", board[i][j]);
		}
		printw("\n");
	}
}



int main(){
	srand(time(NULL));

	put_walls();
	put_cells();

	initscr();

	while(1){
		clear();
		printboard();
		auto_move();
		refresh();
		sleep(2);
	}

	refresh();
	getch();
	endwin();
	return 0;
}
