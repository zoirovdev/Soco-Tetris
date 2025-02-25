#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#define WALL 	'='
#define CELL 	'#'
#define EMPTY 	' '
#define HEIGHT 	30
#define WIDTH 	30


char board[HEIGHT][WIDTH];
int score = 0;



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
	bool is_set = false;
	while(!is_set){
		int i = 1;
		int j = rand() % (WIDTH - 1);
	
		if(j > 0 && j < WIDTH - 1){
			board[i][j] = CELL;
			is_set = true;
		}
	}
}


bool is_end(){
	int cell_x = -1;
	int cell_y = -1;
	int is_broke = 0;
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			if(board[i][j] == CELL){
				cell_x = j;
				cell_y = i;
				is_broke = 1;
				break;
			}
		}

		if(is_broke) break;
	}

	if(cell_y == -1 && cell_x == -1) return false;

	if(board[cell_y+1][cell_x] == WALL || board[cell_y+1][cell_x] == CELL) return true;
	else return false;
}


void is_full(){
	for(int i=1; i<HEIGHT-1; i++){
		int count = 0;
		for(int j=1; j<WIDTH-1; j++){
			if(board[i][j] == CELL) count++;
		}

		if(count == WIDTH - 2){
			score += 5;
			for(int k=1; k<WIDTH-1; k++){
				board[i][k] = board[i-1][k];
				board[i-1][k] = EMPTY;
			}
		}
	}
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


void man_move(int x){
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
	int dest_y = cell_y;
	int dest_x = cell_x + x;
	if(dest_x > 0 && dest_x < WIDTH - 1){
		board[cell_y][cell_x] = EMPTY;
		board[dest_y][dest_x] = CELL;
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

	mvprintw(rows/2 + 15, cols/2 - 30, "Score: %d", score);
}



int main(){
	srand(time(NULL));

	put_walls();
	put_cells();

	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	while(1){
		clear();

		if(is_end()) put_cells();
		
		is_full(); 

		printboard();

		int ch;
		ch = getch();
		if(ch == KEY_LEFT)
			man_move(-1);
		else if(ch == KEY_RIGHT)
			man_move(1);
		else if(ch == KEY_DOWN)
			auto_move();
		else if(ch == 'q'){
			clear();
			int rows, cols;
			getmaxyx(stdscr, rows, cols);
			mvprintw(rows/2-10, cols/2-10, "Game is over!");
			break;
		}

		refresh();
		//sleep(2);
	}

	refresh();
	getch();
	endwin();
	return 0;
}
