#ifndef FISHING_H
#define FISHING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define NUM_ROWS 10
#define NUM_COLS 10

//Defines color codes
#define RED		"\x1B[31;1m"
#define BLUE	"\x1B[34;1m"
#define RESET	"\x1B[0m"

#define FISH_FRAMERATE 30
#define NUM_FISH_TYPES 13
#define STARTING_SPEED 1
#define MAX_FISH_SPEED 4
#define FISH_QUOTIENT 50

#define TITLE "FISHING WITH DAD!"
#define STR_SEA_CUCUMBER "You caught a sea cucumber! Your dad tells you to hope to God that it's lubricated"
#define STR_BOOT "You caught a boot. Your dad picks it up and raises it over his head!"
#define STR_TROUT "You caught a trout! Your dad tells you to bend over"
#define STR_DEAD_BODY "You caught a dead body. You can tell it's your dad's handiwork. Uh oh"
#define STR_RAINBOW "You caught a rainbow fish! The floodwaters are rising. The water is up to your ankles"
#define STR_GOLDFISH "You caught a goldfish with your pet goldfish's nametag from childhood. You hear your dad crack his belt"
#define STR_FLYING_FISH "A flying fish jumps into the boat! Your dad raises it near your windpipe with his cramming arm"
#define STR_RESEMBLES_SANDERS "You caught a fish resembling Colonel Sanders! Your dad raises the point of his Reagan Bush '84 pin above his head"
#define STR_ANGLER "You caught an angler! Your dad perceives the light as a message fromm God and sacrifices you without a second thought"
#define STR_DAD_CLONE "You caught a clone of your dad! Your dad takes the opportunity to watch himself beat you from the 3rd person"
#define STR_ANCHOR "You caught an anchor. Before you even realize what's happened, you can feel your dad tie a rope around your ankle"
#define STR_FISH_PULL_YOU "The fish pulls too hard and you fall into the water. Your dad's dead eyes look on as you scream for help"
#define STR_SNAG_LOG "You snag the line on a log just as your dad's zipper snags on his jeans"
#define STR_WET_FOOT ""

//lol
typedef enum boolean
{
	FALSE, TRUE
} Bool;

typedef enum direction
{
	UP, DOWN, LEFT, RIGHT
} Dir;

typedef struct position
{
	int row;
	int column;
} Pos;

typedef struct cell
{
	Bool fish;
	Pos position;
} Cell;

//lol
typedef enum type
{
	SEA_CUCUMBER, BOOT, TROUT, DEAD_BODY, RAINBOW, GOLDFISH, FLYING_FISH, RESEMBLES_SANDERS, ANCHOR, ANGLER, DAD_CLONE, FISH_PULL_YOU, SNAG_LOG
} Type;

typedef struct fish
{
	Pos position;
	Bool caught;
	Dir direction;
	int speed;
	Type fishtype;
	int update_cnt;
} Fish;

void title_screen(void);
void init_board(Cell board[][NUM_COLS], int rows, int cols);
void print_board(Cell board[][NUM_COLS], int rows, int cols);
void print_blank_board(int rows, int cols);
void update(Cell board[][NUM_COLS], Fish *fish1, Fish *fish2, Fish *fish3);
Bool spawn_fish(Cell board[][NUM_COLS], Fish *fish);
void fish_update(Cell board[][NUM_COLS], Fish *fish);
void print_fish(int offset);
void fish_animation(void);
void fish(int *fish_col, int *fish_row);
void check_fish(int fish_row, int fish_col, Fish fish1, Fish fish2, Fish fish3);
void print_ending(Cell board[][NUM_COLS], Fish fish1, Fish fish2, Fish fish3, int fish_row, int fish_col);
void clear_buffer(void);
Bool play_again(void);

#endif FISHING_H
