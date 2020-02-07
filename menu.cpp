#include "menu.h"
#include "gamemenu.h"
#include "buffer.h"
#include "game.h"

Menu::Menu(Buffer *buffer) : 
	buffer(buffer)
{}

void Menu::Serve()
{
	std::vector<std::string> menuList = { "1.Play" , "2.Help", "3.Exit" };
	std::string menuMsg = "TicTacToe3D";
	bool isSessionEnded = false;
	while(!isSessionEnded){
		std::size_t input = buffer->ChooseOneFromList(menuList, menuList.size(), menuMsg);
		switch(input+ 1){
			case 1: 
				Play();
				break;
			case 2: 
				PrintHelp();
				break;
			case 3:
				isSessionEnded = true;
				break;
		}
	}
}


void Menu::PrintHelp() const
{
	std::string helpMsg = "****Rules****";
	buffer->PrintMessage(helpMsg);
}


void Menu::Play()
{
	std::vector<std::string> continueList = { "1.Yes", "2.No" };
	std::string continueMsg = "Continue";
	
	GameMenu game(buffer);
	while(true){
		game.PlayMatch();
		std::size_t input = buffer->ChooseOneFromList(continueList, continueList.size(), continueMsg);
		if(!input)
		       	game.Restart();
		else 
			return;
	}	
}


