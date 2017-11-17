#include "ReFishing.h"
#include "Sleep.h"

#include <string>

using std::string;

#define DEFAULTPAUSE 50 //50 Milliseconds, about 20 characters/sec
#define DEFAULTSPEED 100 //Just an arbitrary number. Basically 100% speed, defined by a PAUSE of 50

#define DEFAULTWIDTH 60 //60 Characters wide
#define DEFAULTHEIGHT 8 //8 Characters tall

//Textbox uses its own minilanguage to process pauses and speed changes, marked by brackets
//Inspired by Iwata's crazy turing-complete Earthbound text engine
//Bad commands will not throw errors yet, they will just not do anything. I guess I'm writing the game so hopefully I know my own engine
//Default SPEED is 100

//COMMANDS
//[L]					//adds newline. There's also an automatic way to do this
//[S<NewSpeed>]
//[P<LengthInMilliseconds>]
//[N]					//Noop, just stupid

//TODO COMMANDS:
//Take a

class Textbox
{
public:
	Textbox()
	{
		_x = 0;
		_y = 0;

		_width = DEFAULTWIDTH;
		_height = DEFAULTHEIGHT;

		_pause = DEFAULTPAUSE;
	}

	Textbox(unsigned int newWidth, unsigned int newHeight)
	{
		*this = Textbox();

		_width = newWidth;
		_height = newHeight;
	}

	//border is one wide around textbox
	void drawBorder() //maybe accept a border enum type?
	{
		//for now here's the default border

		//the corners
		mvaddch(0,           0,           ACS_ULCORNER); 	//topleft corner
		mvaddch(0,           _width + 1,  ACS_URCORNER); 	//topright corner
		mvaddch(_height + 1, 0,           ACS_LLCORNER);	//bottomleft corner
		mvaddch(_height + 1, _width + 1,  ACS_LRCORNER);	//bottomright corner

		//horizontal lines
		for (unsigned int i = 1; i < _width + 1; i++)
		{
			//the top
			mvaddch(0,           i,       ACS_HLINE);
			//the bottom
			mvaddch(_height + 1, i,       ACS_HLINE);
		}
		//vertical lines
		for (unsigned int j = 1; j < _height + 1; j++)
		{
			//the left
			mvaddch(j,		0,			  ACS_VLINE);
			//the right
			mvaddch(j,		_width + 1,   ACS_VLINE);
		}
		refresh();
	}

	void callBox(string s)
	{
		unsigned int i = 0, j = 0;
		char opcode; //noop
		string word;
		string command;

		drawBorder();

		while (i < s.length())
		{
			//get next word
			while (i < s.length() && s.at(i) != ' ')
			{
				//command flag reached
				if (s.at(i) == '[')
				{
					i++;
					//first character is opcode
					opcode = s.at(i++);
					//until end of flag, read the command
					while (s.at(i) != ']')
					{
						command += s.at(i);
						i++;
					}
					//pause command
					if (opcode == 'P')
					{
						sleepms((unsigned int)stoi(command));
					}
					//changeSpeed command
					else if (opcode == 'S')
					{
						changeSpeed((unsigned int)stoi(command));
					}
					else if (opcode == 'L') //newline
					{
						newLine();
					}
					command = "";
				}
				else if (s.at(i) == ']')
				{
					i++;
				}
				else
				{
					word += s.at(i);
					i++;
				}
			}
			word += ' '; //every word has a space I guess
			i++;

			//go to next line if we run out of room on this one
			if (_x + word.length() > _width)
			{
				//if we ran out of room, just stop trying to print
				if(!newLine())
				{
					break;
				}
			}

			//prints the word to the terminal
			j = 0;
			while (j < word.length())
			{
				mvaddch(_y + 1, _x++ + 1, word.at(j)); //place character, move position
				refresh();
				sleepms(_pause);
				j++;
			}

			word = "";
		}
		move(_width - 1, _height - 1); //should move the cursor to the bottom right but it doesn't work. I think it has to do with one of my flags I set in main
	}

	bool newLine()
	{
		if (_y < _height - 1)
		{
			_x = 0;
			_y++;
			return true;
		}
		else
		{
			return false; //We ran out of room on the screen
		}
	}

	//Will be called by the Textbox engine when [SPEED<NewSpeed>] is encountered
	bool changeSpeed(unsigned int newSpeed) //actually changes pause length
	{
		_pause = ((double)DEFAULTSPEED / newSpeed) * DEFAULTPAUSE; //pause becomes the ratio between speed and defaultSpeed times defaultPause
	}
private:
	unsigned int _x; //xpos in window
	unsigned int _y; //ypos in window

	unsigned int _width;
	unsigned int _height;

	unsigned int _pause; //milliseconds to pause for. Used by sleep()
};