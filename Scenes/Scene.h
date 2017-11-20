#pragma once

#include "../ReFishing.h"
#include "../Textbox/Textbox.h"

#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;

//Scenes will now be cpp files that construct a scene object
//The important task of the scene class is now...?

void testScene(void);

//This is the scene manager. Scenes will be constructed by a series of instructions in a textfile

class Scene
{
public:
	//don't call this one
	Scene ()
	{

	}
	//loads the scene file
	// Scene (string s) : file(s)
	// {
	// 	if (file.is_open())
	// 	{

	// 	}
	// 	else
	// 	{
	// 		t.callBox("File ain't open dingo");
	// 		getch();
	// 	}
	// }
	//executes the instructions in the file
	// void run()
	// {
	// 	// string s;
	// 	// while (!file.eof())
	// 	// {
	// 	// 	//runs every command in the file
	// 	// 	std::getline(file,s);

	// 	// 	if (s.length() > 2)
	// 	// 		runCommand(s);
	// 	// }
	// }

	//This was getting out of hand. I suspect its probably the best way
	//to handle these sorts of things but for now I'm going to directly
	//process the scenes

	//Also if scenes are done in cpp files they get compiled and the
	//players can't find all the secrets by looking at them

	// //runs similarly to the Textbox engine
	// //sort of like an interpreter I guess
	// void runCommand(const string s)
	// {
	// 	//first character is the opcode
	// 	char opcode = s.at(0);
	// 	string command(s.begin() + 2, s.end());
	// 	string c1, c2;

	// 	switch(opcode)
	// 	{
	// 	//this is like a comment, although any invalid character will work
	// 	case '#':
	// 		//noop
	// 		break;
	// 	//display text
	// 	case 'T':
	// 		t.callBox(command);
	// 		break;
	// 	//change Textbox size
	// 	//format: <000,000>
	// 	case 'S':
	// 		t.changeSize(std::stoi(string(command.begin(), command.begin() + 3)),std::stoi(string(command.begin() + 4, command.end())));
	// 		break;
	// 	//move Textbox
	// 	//format: <000,000>
	// 	case 'M':
	// 		t.moveWindow(std::stoi(string(command.begin(), command.begin() + 3)),std::stoi(string(command.begin() + 4, command.end())));
	// 		break;
	// 	case 'F':
	// 		//run fishing minigame
	// 		break;
	// 	case 'C':
	// 		//generate choice and store answer
	// 		//
	// 		break;
	// 	default:
	// 		t.callBox("Invalid command entered, learn the source code better!");
	// 		break;
	// 	}
	// }
private:
	// ifstream file;
	Textbox t;
	// vector<string> responses;
};