#include "gamemenu.h"
#include "player.h"
#include "buffer.h"
#include "game.h"
#include <string>

GameMenu::GameMenu(Game *game, Buffer *buffer) :
	buffer(buffer), game(game)
{}

void GameMenu::PlayMatch()
{
	while(!game->IsEnded())
	{
		decltype(auto) currPlayer = game->GetCurrPlayer();
		std::string msg = 
			"Current Player: " + currPlayer->GetName() + 
			" (" + std::string(1, currPlayer->GetSign()) + ")\n";
		
		buffer->DrawField(game->GetFieldSet(), msg);	

		game->Play();
	}
	DrawWinner(game->GetCurrPlayer());
}

void GameMenu::DrawWinner(const Player *winner)
{
	std::string msg =
	       	"Congratulations " + winner->GetName() +
		" (" + std::string(1, winner->GetSign()) + ")! You won!";	
}
