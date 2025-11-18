#include <stdio.h>

#define ROWS 25
#define COLS 25
#define ALIVE '*'
#define DEAD '.'


int cell_to_index(int x, int y){
	if(x < 0){
		x = (-x) % COLS;
		x = COLS - x;
	}

	if(y < 0){
		y = (-y) % ROWS;
		y = ROWS - y;
	}

	if(x >= COLS) x = x % COLS;
	if(y >= ROWS) y = y % ROWS;

	return y * COLS + x;
}


void set_cell(char* grid, int x, int y, char state){
	grid[cell_to_index(x, y)] = state;
}

char get_cell(char* grid, int x, int y){
	return grid[cell_to_index(x, y)];
}

void print_grid(char* grid){
	for(int y = 0; y < ROWS; y++){
		for (int x = 0; x < COLS; x++){
			printf("%c", get_cell(grid, x, y));
		}
		printf("\n");
	}
}

void set_board(char* grid, char state){
	for(int y = 0; y < ROWS; y++){
		for (int x = 0; x < COLS; x++){
			set_cell(grid, x, y, state);
		}
	}
}

int get_alive_neighbours(char* grid, int x, int y){
	int n_alive = 0;
	for(int yo = -1; yo <= 1; yo++){
		for(int xo = -1; xo <= 1; xo++){
			if(xo == 0 && yo == 0) continue;
			if(get_cell(grid, x + xo, y + yo) == ALIVE)
				n_alive++;
		}
	}
	return n_alive;
	
}

void compute_grid(char* old, char* new){
	for(int x = 0; x < COLS; x++){
		for(int y = 0; y < ROWS; y++){
			char new_state = DEAD;
			if (get_cell(old, x, y) == ALIVE){
				new_state = (get_alive_neighbours(old, x, y) == 2 || get_alive_neighbours(old, x, y) == 3)? ALIVE : DEAD;
			}else{
				if (get_alive_neighbours(old, x, y) == 3) new_state = ALIVE; 
			}
			set_cell(new, x, y, new_state);
		}
	}	
}

int main(void){
	char grid[COLS * ROWS];
	char new_grid[COLS * ROWS];
	set_board(grid, DEAD);
	set_cell(grid, 10, 10, ALIVE);
	set_cell(grid, 10, 11, ALIVE);
	set_cell(grid, 10, 9, ALIVE);
	printf("%d\n", get_alive_neighbours(grid, 10, 10));
	print_grid(grid);
	compute_grid(grid, new_grid);
	printf("\n");
	print_grid(new_grid);


}
