#include "ReFishing.h"

#include "FishingBoard/FishingBoard.h"
#include "Textbox/Textbox.h" //uninclude these eventually, they should ideally be only in Scene

#include "Scenes/Scene.h"

int main(void)
{
	initscr();
	keypad(stdscr, true);
	nonl();
	cbreak();
	noecho();
	leaveok(stdscr, false);

	//New scene test code

	//testScene();

	//Original scene test code

	// Scene s("Scenes/testScene.txt");
	// s.run(); //after debugging, build run into the constructor

	//Textbox test code

	// //Textbox should be constructed at the beginning of a scene. It will not appear until it is called with a string
	Textbox t(20,10);
	// //Example command with syntax and all of the commands. Maybe consider putting a / between words or something...
	// t.callBox("Here's an awesome string [P1000]that if it [S200]doesn't work you go[R]nna die a horrible death [L]Watch out for danger it could be anywhere");
	// //Words that are too long will newline but spill out of the side. That is fine
	// t.changeSize(10, 5);
	// t.moveWindow(5,5);
	// t.callBox("Here's a word that'stoolong");

	//FishingBoard test code
	//TODO: Make FishingBoard constructor clear the boardspace

	FishingBoard board;
	Fish *fish = board.run();
	if (fish != nullptr)
		t.callBox(fish->text);
	else
		t.callBox("Ain't no fish found");

	endwin();
}
