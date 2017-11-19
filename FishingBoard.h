#include <string>
#include <vector>
#include <random>
#include <chrono>

#include "ReFishing.h"

#define BOARDWIDTH 20
#define BOARDHEIGHT 10

using std::string;
using std::vector;

struct Pos
{
	unsigned int x;
	unsigned int y;
};

enum Dir
{
	NONE, UP, DOWN, LEFT, RIGHT
};

struct Fish
{
	Dir nextDir;
	string text;
};

struct Cell
{
	bool empty;
	Fish *fish; //most likely a fish
	char display;
};

//I think this will be a little incongruous with the overworld board
class Board
{
public:
	Board() : dirDist(0,4) , xDist(0,BOARDWIDTH - 1) , yDist(0, BOARDHEIGHT - 1)
	{
		rand.seed(std::chrono::system_clock::now().time_since_epoch().count());

		//resize row vector to BOARDHEIGHT
		board.resize(BOARDWIDTH);
		for (unsigned int i = 0; i < BOARDWIDTH; i++)
		{
			//resize column vectors to BOARDWIDTH
			board.at(i).resize(BOARDHEIGHT);
		}

		for (unsigned int i = 0; i < BOARDWIDTH ; i++)
		for (unsigned int j = 0; j < BOARDHEIGHT; j++)
		{
			board[i][j].empty 		= true;
			board[i][j].fish 		= nullptr;
			board[i][j].display		= '~';
		}
	}

	Fish *run()
	{
		int i = 0;

		//spawnFish(3,3);

		while (i++ < 3)
			spawnFish();

		print();

		while(true)
		{
			update();
			sleepms(500);
			print();
		}
	}

	//Spawns Fish in random location
	bool spawnFish()
	{
		return spawnFish(xDist(rand), yDist(rand));
	}

	bool spawnFish(const unsigned int x, const unsigned int y)
	{
		if (board[x][y].empty)
		{
			board[x][y].empty = false;
			board[x][y].fish = genFish();
			board[x][y].display = 'F';

			return true;
		}
		else
		{
			return false;
		}
	}

	//randomly generates the fish
	Fish *genFish()
	{
		Fish *newFish = new Fish; //DESTROY IN DESTRUCTOR DON'T FORGET OR YOU'RE THE WORST PROGRAMMER DROP OUT

		newFish->text = "Here's the text in the fish"; //always this string for now
		newFish->nextDir = Dir::NONE;

		return newFish;
	}

	//returns the fish you shoot so you can see what's inside
	Fish *check(unsigned int x, unsigned int y)
	{
		//if there is something in the cell
		if (board[x][y].fish != nullptr)
		{
			return board[x][y].fish;
		}
		else
		{
			//redundant
			return nullptr;
		}
	}

	//moves all of the Fish on the board by calling moveFish
	void update()
	{
		//actually update the board AFTER checking if the user is going to fish
		for (int i = 0; i < BOARDWIDTH; i++)
		{
			for (int j = 0; j < BOARDHEIGHT ; j++)
			{
				//there is a fish there, it needs to move
				if (!board[i][j].empty)
				{
					board[i][j].fish->nextDir = (Dir) dirDist(rand);
					moveFish(i,j);
				}
			}
		}
	}

	//swaps the cell with the Fish's next destination cell
	void moveFish(unsigned int x, unsigned int y)
	{
		Dir nextDir = board[x][y].fish->nextDir;
		Pos nextPos = {(unsigned int)x,(unsigned int)y};
		
		//calculates next position based on nextDir
		if (nextDir == Dir::UP)
			nextPos.y++;
		if (nextDir == Dir::DOWN)
			nextPos.y--;
		if (nextDir == Dir::RIGHT)
			nextPos.x++;
		if (nextDir == Dir::LEFT)
			nextPos.x--;
		
		//if nextPos is in the bounds of the board AND there isn't already a fish there
		if (nextPos.x >= 0 && nextPos.x < BOARDWIDTH && nextPos.y >= 0 && nextPos.y < BOARDHEIGHT && board[nextPos.x][nextPos.y].empty)
		{
			//swap the two cells. a BIT sloppy
			std::swap(board[x][y] , board[nextPos.x][nextPos.y]);
		}
	}

	//Precondition: screen is open
	void print() const
	{
		//prints letters along top row and along the side
		for (int i = 0; i < BOARDWIDTH ; i++)
			mvaddch(0,     (i + 1) * 2, (char) i + 'A'); //Letters along the top

		for (int j = 0; j < BOARDHEIGHT; j++)
			mvaddch(j + 1, 0,           (char) j + '0'); //Numbers along the right

		for (int i = 0; i < BOARDWIDTH; i++)
		{
			for (int j = 0; j < BOARDHEIGHT; j++)
			{
				mvaddch(j + 1, (i + 1) * 2, board[i][j].display);
			}
		}
		refresh();
	}

private:
	std::default_random_engine rand;
	std::uniform_int_distribution<int> dirDist, xDist, yDist;

	//upon further inspection I think it would be a better idea to use a 1D vector for this
	//OR create a matrix class... that's probably what I should do
	vector<vector<Cell>> board; //that's a lotta template arguments! it used to be more
};
