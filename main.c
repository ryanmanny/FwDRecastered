#include "fishing.h"

int main(void)
{
	Cell board[NUM_ROWS][NUM_COLS];
	Fish fish1, fish2, fish3;
	char ch;
	unsigned int fish_col, fish_row;

	srand((unsigned int)time(NULL));

	title_screen();

	do {
		init_board(board, NUM_ROWS, NUM_COLS);

		while (!spawn_fish(board, &fish1));
		while (!spawn_fish(board, &fish2));
		while (!spawn_fish(board, &fish3));

		while (!_kbhit(NULL))
			update(board, &fish1, &fish2, &fish3);

		print_blank_board(NUM_ROWS, NUM_COLS);
		fish(&fish_col, &fish_row);

		print_ending(board, fish1, fish2, fish3, fish_row, fish_col);

	} while (play_again());
}