#include <string>
#include <vector>
#include <random>
#include <chrono>

#include "ReFishing.h"

#define BOARDWIDTH 10
#define BOARDHEIGHT 10
#define NUMFISH 3

#define DEFAULTPAUSE 333 //333 Milliseconds, about 3 updates/sec. Changing this will change the difficulty of the board
#define DEFAULTSPEED 100 //Just an arbitrary number. Basically 100% speed, defined by a PAUSE of 500
#define INPUTPRECISION 20

#define NOINPUT -1 //when timeout is 0, getch() returns -1 when no input. Didn't know that was possible

using std::string;
using std::vector;

struct Pos
{
	unsigned int x;
	unsigned int y;
};

enum Dir
{
	UP, DOWN, LEFT, RIGHT, NONE
};

struct Fish
{
	Dir nextDir;
	string text;
};

struct Cell
{
	bool empty;
	bool update;
	Fish *fish; //most likely a fish
	char display;
};

//I think this will be a little incongruous with the overworld board
class FishingBoard
{
public:
	FishingBoard() : dirDist(0,16) , xDist(0,BOARDWIDTH - 1) , yDist(0, BOARDHEIGHT - 1)
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
			board[i][j].update		= false;
		}
		cUpdate = false;
		pause = DEFAULTPAUSE;
	}

	Fish *run()
	{
		timeout(0);
		int i = 0, count = 0;
		char c = -1;

		while (i < NUMFISH)
			i += spawnFish();

		print();

		//fish move around while waiting for user input
		while(c == NOINPUT)
		{
			c = getch();
			sleepms(pause / INPUTPRECISION);

			//user gets INPUTPRECISION chances to input a key before the next update
			if (count == INPUTPRECISION && c == NOINPUT)
			{
				update();
				count = 0;	
			}
			count++;
		}

		timeout(-1);

		print();

		return check(getCheck());
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

	Pos getCheck()
	{
		char c;
		int row = -1, col = -1; //position to be send to check
		bool bCol = false, bRow = false;
		while (!bRow || !bCol)
		{
			c = getch();
			//c is a letter (column)
			if(c >= 'a' && c <= 'z')
			{
				if (c - 'a' <= BOARDWIDTH)
				{
					bCol = true;
					col = c - 'a';
				}
			}
			else if (c >= 'A' && c <= 'Z')
			{
				if (c - 'A' <= BOARDWIDTH)
				{
					bCol = true;
					col = c - 'A';
				}
			}

			//highlight is a row (number)
			else if (c >= '0' && c <= '9')
			{
				if (c - '0' <= BOARDHEIGHT)
				{
					bRow = true;
					row = c - '0';
				}
			}
			printHighlight(c);
		}
		getch();
		return {row, col};
	}

	Fish *check(Pos pos)
	{
		return check(pos.x, pos.y);
	}

	//returns the fish you shoot so you can see what's inside
	Fish *check(unsigned int x, unsigned int y)
	{
		//if there is something in the cell
		if (board[y][x].fish != nullptr)
		{
			return board[y][x].fish;
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
		bool success = false;
		//actually update the board AFTER checking if the user is going to fish
		for (int i = 0; i < BOARDWIDTH; i++)
		{
			for (int j = 0; j < BOARDHEIGHT ; j++)
			{
				//there is a fish there, it needs to move
				if (!board[i][j].empty)
				{
					while (!success)
					{
						board[i][j].fish->nextDir = getDir();
						success = moveFish(i,j);
					}
					success = false;
				}
			}
		}
		cUpdate = !cUpdate;
		print();
	}

	Dir getDir()
	{
		int d = dirDist(rand);
		switch (d)
		{
			//UP
			case 0:
				return Dir::UP;
				break;
			case 1:
				return Dir::DOWN;
				break;
			case 2:
				return Dir::LEFT;
				break;
			case 3:
				return Dir::RIGHT;
				break;
			default:
				return Dir::NONE;
				break;
		}
	}

	//swaps the cell with the Fish's next destination cell
	bool moveFish(unsigned int x, unsigned int y)
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
		
		//the fish hasn't already updated this tick
		if (board[x][y].update == cUpdate)
		{	
			//don't move, but classify as an update	
			if (nextDir == Dir::NONE)
			{
				board[x][y].update = !board[x][y].update;
				return true;
			}
			//if nextPos is in the bounds of the board AND there isn't already a fish there
			else if (nextPos.x >= 0 && nextPos.x < BOARDWIDTH && nextPos.y >= 0 && nextPos.y < BOARDHEIGHT && board[nextPos.x][nextPos.y].empty)
			{
				//swap the two cells. a BIT sloppy
				board[x][y].update = !board[x][y].update;
				std::swap(board[x][y] , board[nextPos.x][nextPos.y]);
				//success
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
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

	//print the board with a row highlighted
	void printHighlight(char highlight) const
	{
		//determine if highlight is a row or column
		bool row = false, column = false;
		
		//highlight is a column (letter)
		if(highlight >= 'a' && highlight <= 'z')
		{
			column = true;
			highlight -= 'a';
		}
		else if (highlight >= 'A' && highlight <= 'Z')
		{
			column = true;
			highlight -= 'A';
		}

		//highlight is a row (number)
		else if (highlight >= '0' && highlight <= '9')
		{
			row = true;
			highlight -= '0';
		}

		//prints letters along top row and along the side
		for (int i = 0; i < BOARDWIDTH ; i++)
		{	
			if (column && i == highlight)
			{
				attron(A_REVERSE);
				mvaddch(0,     (i + 1) * 2, (char) i + 'A'); //Letters along the top
				attroff(A_REVERSE);
			}
			else
			{
				//mvaddch(0,     (i + 1) * 2, (char) i + 'A'); //Letters along the top
			}
		}

		for (int j = 0; j < BOARDHEIGHT; j++)
		{
			if (row && j == highlight)
			{
				attron(A_REVERSE);
				mvaddch(j + 1, 0,           (char) j + '0'); //Numbers along the right
				attroff(A_REVERSE);
			}
			else
			{
				//mvaddch(j + 1, 0,           (char) j + '0'); //Numbers along the right
			}
		}

		for (int i = 0; i < BOARDWIDTH; i++)
		{
			for (int j = 0; j < BOARDHEIGHT; j++)
			{
				if ((column && i == highlight) || (row && j == highlight))
				{
					attron(A_REVERSE);
					mvaddch(j + 1, (i + 1) * 2, board[i][j].display);
					if (row)
						mvaddch(j + 1, (i + 1) * 2 - 1, ' ');
					attroff(A_REVERSE);
				}
				else
				{
					//mvaddch(j + 1, (i + 1) * 2, board[i][j].display);
				}
			}
		}
		refresh();
	}

	//taken from my Textbox engine :)
	bool changeSpeed(unsigned int newSpeed) //actually changes pause length
	{
		pause = ((double)DEFAULTSPEED / newSpeed) * DEFAULTPAUSE; //pause becomes the ratio between speed and defaultSpeed times defaultPause
		return true;
	}

private:
	std::default_random_engine rand;
	std::uniform_int_distribution<int> dirDist, xDist, yDist;

	//upon further inspection I think it would be a better idea to use a 1D vector for this
	//OR create a matrix class... that's probably what I should do
	vector<vector<Cell>> board; //that's a lotta template arguments! it used to be more
	bool cUpdate; //toggles every update to prevent double updates
	
	unsigned int pause;
};
