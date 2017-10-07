#include "fishing.h"

//Prints title screen and waits for input before continuing
void title_screen(void)
{
	fish_animation();
	clear_buffer();
	system("cls");
}

//Initializes all board squares in array to empty
void init_board(Cell board[][NUM_COLS], int rows, int cols)
{
	int row_index = 0, col_index = 0;

	for (; row_index < rows; ++row_index)
	{
		for (col_index = 0; col_index < cols; ++col_index)
		{
			board[row_index][col_index].fish = FALSE;
			board[row_index][col_index].position.row = row_index;
			board[row_index][col_index].position.column = col_index;
		}
	}
}

void print_board(Cell board[][NUM_COLS], int rows, int cols)
{
	int row_index = 0, col_index = 0;
	printf("  1 2 3 4 5 6 7 8 9 0\n");
	for (; row_index < rows; ++row_index)
	{
		if (row_index != 9)
			printf("%d ", row_index + 1);
		else
			printf("0 ");

		for (col_index = 0; col_index < cols; ++col_index)
		{
			if (board[row_index][col_index].fish == TRUE)
				printf(RED "F " RESET);
			else
				printf(BLUE "~ " RESET);
		}
		printf("\n");
	}
}

void print_blank_board(int rows, int cols)
{
	int row_index = 0, col_index = 0;

	system("cls");
	printf(TITLE"\n");
	printf("  1 2 3 4 5 6 7 8 9 0\n");
	for (; row_index < rows; ++row_index)
	{
		if (row_index != 9)
			printf("%d ", row_index + 1);
		else
			printf("0 ");

		for (col_index = 0; col_index < cols; ++col_index)
		{
				printf(BLUE "~ " RESET);
		}
		printf("\n");
	}
	printf("You can't see through the ripples in the water! Your dad is watching your next move closely\n");
}

void fish_animation()
{
	while (!_kbhit(NULL))
	{
		print_fish(1);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(2);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(3);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(4);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(5);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(4);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(3);
		_sleep(FISH_FRAMERATE);
		system("cls");
		print_fish(2);
		_sleep(FISH_FRAMERATE);
		system("cls");
	}
}

void update(Cell board[][NUM_COLS], Fish *fish1, Fish *fish2, Fish *fish3)
{
	fish_update(board, fish1);
	fish_update(board, fish2);
	fish_update(board, fish3);
	printf(TITLE"\n");
	print_board(board, NUM_ROWS, NUM_COLS);
	_sleep(400);
	system("cls");
}

void print_fish(int offset)
{
	printf(TITLE"\n");
	switch (offset)
	{
	case 1:
		printf(RED "   _.-=-._     .-,\n .\'       \"-.,' / \n(          _.  <\n `=.____.=\"  `._\\\n		\n");
		break;
	case 2:
		printf(RED "    _.-=-._     .-,\n  .\'       \"-.,' /   \n (          _.  <\n  `=.____.=\"  `._\\\n 		\n");
		break;
	case 3: 
		printf(RED "     _.-=-._     .-,\n   .\'       \"-.,' /   \n  (          _.  <\n   `=.____.=\"  `._\\\n  		\n");
		break;
	case 4:
		printf(RED "      _.-=-._     .-,\n    .\'       \"-.,' /   \n   (          _.  <\n    `=.____.=\"  `._\\\n   		\n");
		break;
	case 5:
		printf(RED "       _.-=-._     .-,\n     .\'       \"-.,' /     \n    (          _.  <\n     `=.____.=\"  `._\\\n    		\n");
		break;
	}
	printf(RESET "Press any key to start playing!\n");
}

Bool spawn_fish(Cell board[][NUM_COLS], Fish *fish)
{
	int dest_row = 0, dest_col = 0;
	dest_row = rand() % 10;
	dest_col = rand() % 10;

	if (board[dest_row][dest_col].fish == FALSE)
	{
		board[dest_row][dest_col].fish = TRUE;
		fish->caught = FALSE;
		fish->direction = UP;
		fish->fishtype = rand() % NUM_FISH_TYPES;
		fish->position.row = dest_row;
		fish->position.column = dest_col;
		fish->speed = 1;
		fish->update_cnt = STARTING_SPEED;
		return TRUE;
	}
	else
		return FALSE;
}

void fish_update(Cell board[][NUM_COLS], Fish *fish)
{
	if (fish->update_cnt == 0)
	{
		board[fish->position.row][fish->position.column].fish = FALSE;
		if (fish->direction == UP)
		{
			if (fish->position.row != NUM_ROWS - 1)
				fish->position.row += 1;
			else
				fish->position.row -= 1;
		}
		if (fish->direction == DOWN)
		{
			if (fish->position.row != 0)
				fish->position.row -= 1;
			else
				fish->position.row += 1;
		}
		if (fish->direction == LEFT)
		{
			if (fish->position.column != NUM_COLS - 1)
				fish->position.column += 1;
			else
				fish->position.column -= 1;
		}
		if (fish->direction == RIGHT)
		{
			if (fish->position.column != 0)
				fish->position.column -= 1;
			else
				fish->position.column += 1;
		}
		fish->direction = rand() % 4;
		fish->speed = rand() % MAX_FISH_SPEED + 200;
		fish->update_cnt = FISH_QUOTIENT / (int)fish->speed;
		board[fish->position.row][fish->position.column].fish = TRUE;
	}
	else
		fish->update_cnt -= 1;
}

void fish(int *fish_col, int *fish_row)
{
	clear_buffer();
	printf("Enter column number: ");
	do {
		scanf(" %u", fish_col);
	} while (*fish_col > NUM_COLS + 1);
	printf("Enter row number: ");
	do {
		scanf(" %u", fish_row);
	} while (*fish_row > NUM_ROWS + 1);
	if (*fish_col == 0)
		*fish_col = 10;
	if (*fish_row == 0)
		*fish_row = 10;
	*fish_col -= 1;
	*fish_row -= 1;
}

void check_fish(int fish_row, int fish_col, Fish fish1, Fish fish2, Fish fish3)
{
	Type fishtype;
	if (fish1.position.column == fish_col && fish1.position.row == fish_row)
		fishtype = fish1.fishtype;
	else if (fish2.position.column == fish_col && fish2.position.row == fish_row)
		fishtype = fish2.fishtype;
	else if (fish3.position.column == fish_col && fish3.position.row == fish_row)
		fishtype = fish3.fishtype;

	switch (fishtype)
	{
		case SEA_CUCUMBER:
			printf(STR_SEA_CUCUMBER"\n");
			break;
		case BOOT:
			printf(STR_BOOT"\n");
			break;
		case TROUT:
			printf(STR_TROUT"\n");
			break;
		case DEAD_BODY:
			printf(STR_DEAD_BODY"\n");
			break;
		case RAINBOW:
			printf(STR_RAINBOW"\n");
			break;
		case GOLDFISH:
			printf(STR_GOLDFISH"\n");
			break;
		case FLYING_FISH:
			printf(STR_FLYING_FISH"\n");
			break;
		case RESEMBLES_SANDERS:
			printf(STR_RESEMBLES_SANDERS"\n");
			break;
		case ANCHOR: 
			printf(STR_ANCHOR"\n");
			break;
		case ANGLER: 
			printf(STR_ANGLER"\n");
			break;
		case DAD_CLONE:
			printf(STR_DAD_CLONE"\n");
			break;
		case FISH_PULL_YOU:
			printf(STR_FISH_PULL_YOU"\n");
			break;
		case SNAG_LOG:
			printf(STR_SNAG_LOG"\n");
			break;
	}
}

void print_ending(Cell board[][NUM_COLS], Fish fish1, Fish fish2, Fish fish3, int fish_row, int fish_col)
{
	if (board[fish_row][fish_col].fish == TRUE)
		check_fish(fish_row, fish_col, fish1, fish2, fish3);
	else
		printf("You really screwed up this time! Your dad's hands wrap around your neck as your vision fades to black...\nThanks for playing!\n");
}

Bool play_again(void)
{
	char play_again;
	_sleep(1000);
	printf("Enter Y to play again\n");
	scanf(" %c", &play_again);
	clear_buffer();
	system("cls");
	if (play_again == 'Y' || play_again == 'y')
		return TRUE;
	else
		return FALSE;
}

void clear_buffer(void)
{
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}