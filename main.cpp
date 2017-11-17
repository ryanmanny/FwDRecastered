//#include "fishing.h"

#include "ReFishing.h"
#include "Board.h"
#include "Textbox.h"

int main(void)
{
	initscr();
	keypad(stdscr, true);
	nonl();
	cbreak();
	noecho();
	leaveok(stdscr, true);

	// Board<Fish> board;
	// board.print();

	Textbox t(20,10);
	//Example command with syntax and all of the commands. Maybe consider putting a / between words or something...
	t.callBox("Here's an awesome string [P1000]that if it [S200]doesn't work you go[R]nna die a horrible death [L]Watch out for danger it could be anywhere");
	//Words that are too long will newline but spill out of the side. That is fine
	//t.callBox("Here's a word that'stoolong");
	getch();

	endwin();
}

// int main(void)
// {
// 	Cell board[NUM_ROWS][NUM_COLS];
// 	Fish fish1, fish2, fish3;
// 	char ch;
// 	unsigned int fish_col, fish_row;
//
// 	srand((unsigned int)time(NULL));
//
// 	title_screen();
//
// 	do {
// 		init_board(board, NUM_ROWS, NUM_COLS);
//
// 		while (!spawn_fish(board, &fish1));
// 		while (!spawn_fish(board, &fish2));
// 		while (!spawn_fish(board, &fish3));
//
// 		while (!_kbhit(NULL))
// 			update(board, &fish1, &fish2, &fish3);
//
// 		print_blank_board(NUM_ROWS, NUM_COLS);
// 		fish(&fish_col, &fish_row);
//
// 		print_ending(board, fish1, fish2, fish3, fish_row, fish_col);
//
// 	} while (play_again());
// }
