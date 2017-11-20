#include "Textbox.h"

Textbox::Textbox()
{
	_xpos = 0;
	_ypos = 0;

	_x = 0;
	_y = 0;

	_width = DEFAULTWIDTH;
	_height = DEFAULTHEIGHT;

	_pause = DEFAULTPAUSE;
}

Textbox::Textbox(const unsigned int newWidth, const unsigned int newHeight)
{
	*this = Textbox();

	_width = newWidth;
	_height = newHeight;
}

Textbox::Textbox(const unsigned int newWidth, const unsigned int newHeight, const unsigned int newXpos, const unsigned int newYpos)
{
	//we need to go deeper
	*this = Textbox(newWidth, newHeight);

	moveWindow(newXpos, newYpos);
}

//border is one wide around textbox
void Textbox::drawBorder() const //maybe accept a border enum type?
{
	//for now here's the default border

	//the corners
	mvaddch(0 + _ypos,			 0 + _xpos,           ACS_ULCORNER); 	//topleft corner
	mvaddch(0 + _ypos,			 _width + _xpos + 1,  ACS_URCORNER); 	//topright corner
	mvaddch(_height + _ypos + 1, 0 + _xpos,           ACS_LLCORNER);	//bottomleft corner
	mvaddch(_height + _ypos + 1, _width + _xpos + 1,  ACS_LRCORNER);	//bottomright corner

	//horizontal lines
	for (unsigned int i = 1; i < _width + 1; i++)
	{
		//the top
		mvaddch(0 + _ypos,			 i + _xpos,       		ACS_HLINE);
		//the bottom
		mvaddch(_height + _ypos + 1, i + _xpos,       		ACS_HLINE);
	}

	//vertical lines
	for (unsigned int j = 1; j < _height + 1; j++)
	{
		//the left
		mvaddch(j + _ypos,			 0 + _xpos,			  	ACS_VLINE);
		//the right
		mvaddch(j + _ypos,			 _width + _xpos + 1,   	ACS_VLINE);
	}
	refresh();
}

void Textbox::callBox(string s)
{
	unsigned int i = 0, j = 0;
	char opcode = 'N'; //noop
	
	string word;
	string command;

	drawBorder();
	clear();

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
				else if (opcode == 'R') //reset
				{
					reset();
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
		if (_x + word.length() > _width + 1)
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
			if (word.at(j) != ' ')
			{
				mvaddch(_y + _ypos + 1, _x + _xpos + 1, word.at(j)); //place character, move position
				refresh();
			}
			sleepms(_pause);
			_x++;
			j++;
		}

		word = "";
	}
	move(_width - 1, _height - 1); //should move the cursor to the bottom right but it doesn't work. I think it has to do with one of my flags I set in main
	getch();
}

bool Textbox::newLine()
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
//Overwrites all characters with spaces
bool Textbox::clear()
{
	//resets cursor to top right
	_x = 0;
	_y = 0;
	//since we have no idea what is in the box beforehand we have to call this every time
	for (unsigned int i = 1; i < _width + 1; i++)
	{
		for (unsigned int j = 1; j < _height + 1; j++)
		{
			mvaddch(j + _ypos, i + _xpos, ' '); //overwrites with space
		}
	}
	refresh();
	return true;
}

//Will be called by the Textbox engine when [SPEED<NewSpeed>] is encountered
bool Textbox::changeSpeed(unsigned int newSpeed) //actually changes pause length
{
	_pause = ((double)DEFAULTSPEED / newSpeed) * DEFAULTPAUSE; //pause becomes the ratio between speed and defaultSpeed times defaultPause
	return true; //I'm not quite sure what the fail condition is for this one yet
}

bool Textbox::changeSize(unsigned int newWidth, unsigned int newHeight)
{
	_width = newWidth;
	_height = newHeight;
	return true;
}

bool Textbox::moveWindow(unsigned int newxpos, unsigned int newypos)
{
	_xpos = newxpos;
	_ypos = newypos;
	return true;
}
bool Textbox::reset()
{
	return changeSpeed(DEFAULTSPEED);
}