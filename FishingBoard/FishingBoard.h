#include <string>
#include <vector>
#include <random>
#include <chrono>

#include "../ReFishing.h"

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
	FishingBoard();

	//Runs the game
	Fish *run();

	//Spawns Fish in random location
	bool spawnFish();
	//Spawns Fish at location passed in
	bool spawnFish(const unsigned int x, const unsigned int y);

	//randomly generates the fish
	Fish *genFish();

	//Gets a position to check from the user and highlights board based on input
	Pos getCheck();

	//Checks the board at the current position
	Fish *check(Pos pos);
	//returns the fish you shoot so you can see what's inside
	Fish *check(unsigned int x, unsigned int y);

	//moves all of the Fish on the board by calling moveFish
	void update();

	//Randomly returns direction
	Dir getDir();

	//swaps the cell with the Fish's next destination cell
	bool moveFish(unsigned int x, unsigned int y);
	//Precondition: screen is open
	void print() const;
	//print the board with a row highlighted
	void printHighlight(char highlight) const;
	//taken from my Textbox engine :)
	bool changeSpeed(unsigned int newSpeed); //actually changes pause length

private:
	std::default_random_engine rand;
	std::uniform_int_distribution<int> dirDist, xDist, yDist;

	//upon further inspection I think it would be a better idea to use a 1D vector for this
	//OR create a matrix class... that's probably what I should do
	vector<vector<Cell>> board; //that's a lotta template arguments! it used to be more
	bool cUpdate; //toggles every update to prevent double updates
	
	unsigned int pause;
};
