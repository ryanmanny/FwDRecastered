#include <string>
#include <vector>

#define BOARDWIDTH 10
#define BOARDHEIGHT 15

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

template <typename Hittable>
class Board
{
public:
	Board()
	{
		//resize row vector to BOARDHEIGHT
		board.resize(BOARDHEIGHT);
		for (int i = 0; i < BOARDHEIGHT; i++)
		{
			//resize column vectors to BOARDWIDTH
			board.at(i).resize(BOARDWIDTH);
		}

		for (int i = 0; i < BOARDHEIGHT; i++)
		for (int j = 0; j < BOARDWIDTH ; j++)
		{
			board.at(i).at(j).pos.y = i;
			board.at(i).at(j).pos.x	= j;
			board[i][j].empty 		= true;
			board[i][j].hit 		= nullptr;
			board[i][j].display		= '~';
		}
	}

	//Precondition: screen is open
	void print() const
	{
		for (int i = 0; i < BOARDHEIGHT; i++)
		for (int j = 0; j < BOARDWIDTH ; j++)
		{
			mvaddch(board[i][j].pos.y, board[i][j].pos.x * 2, board[i][j].display);
			refresh();
		}
	}

private:
	vector<vector<Cell<Hittable>>> board; //that's a lotta template arguments!
};
