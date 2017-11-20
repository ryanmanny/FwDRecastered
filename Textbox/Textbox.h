#pragma once

#include "../ReFishing.h"

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
	Textbox();
	Textbox(const unsigned int newWidth, const unsigned int newHeight);
	Textbox(const unsigned int newWidth, const unsigned int newHeight, const unsigned int newXpos, const unsigned int newYpos);

	//border is one wide around textbox
	void drawBorder() const;
	void callBox(string s);
	bool newLine();
	//Overwrites all characters with spaces
	bool clear();
	//Will be called by the Textbox engine when [SPEED<NewSpeed>] is encountered
	bool changeSpeed(unsigned int newSpeed); //actually changes pause length
	bool changeSize(unsigned int newWidth, unsigned int newHeight);
	bool moveWindow(unsigned int newxpos, unsigned int newypos);
	bool reset();
private:
	unsigned int _xpos; //xpos of window itself
	unsigned int _ypos;	//ypos of window itself

	unsigned int _x; //xpos in window
	unsigned int _y; //ypos in window

	unsigned int _width;
	unsigned int _height;

	unsigned int _pause; //milliseconds to pause for. Used by sleep()
};