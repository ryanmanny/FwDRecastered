#include <string>
#include <vector>

#define BOARDWIDTH 20
#define BOARDHEIGHT 10

using std::string;
using std::vector;

struct Pos
{
	int x;
	int y;
};

struct Fish
{
	string text;
};

template <typename Hittable>
struct Cell
{
	Pos pos;
	bool empty;
	Hittable *hit; //most likely a fish
	char display;
};

//I think this will be a little incongruous with the overworld board
template <typename Hittable>
class Board
{
public:
	Board()
	{
		//resize row vector to BOARDHEIGHT
		board.resize(BOARDHEIGHT);
		for (unsigned int i = 0; i < BOARDHEIGHT; i++)
		{
			//resize column vectors to BOARDWIDTH
			board.at(i).resize(BOARDWIDTH);
		}

		for (unsigned int i = 0; i < BOARDHEIGHT; i++)
		for (unsigned int j = 0; j < BOARDWIDTH ; j++)
		{
			board.at(i).at(j).pos.y = i;
			board.at(i).at(j).pos.x	= j;
			board[i][j].empty 		= true;
			board[i][j].hit 		= nullptr;
			board[i][j].display		= '~';
		}
	}

	//returns the fish you shoot so you can see what's inside
	Hittable * shootBoard(unsigned)
	{

	}

	//Precondition: screen is open
	void print() const
	{
		//prints letters along top row and along the side
		for (int i = 0; i < BOARDWIDTH ; i++)
			mvaddch(0,     (i + 1) * 2, (char) i + 'A'); //Letters along the top

		for (int j = 0; j < BOARDHEIGHT; j++)
			mvaddch(j + 1, 0,           (char) j + '0'); //Numbers along the right

		for (int i = 0; i < BOARDHEIGHT; i++)
		{
			for (int j = 0; j < BOARDWIDTH ; j++)
			{
				mvaddch(board[i][j].pos.y + 1, (board[i][j].pos.x + 1) * 2, board[i][j].display);
			}
		}
		refresh();
	}

private:
	vector<vector<Cell<Hittable>>> board; //that's a lotta template arguments!
};
