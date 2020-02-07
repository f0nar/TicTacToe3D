#include "gamemenu.h"
#include "humanplayer.h"
#include "buffer.h"
#include "player.h"
#include "game.h"
#include <string>

GameMenu::GameMenu(Buffer *buffer) :
	buffer(buffer),
    player1(CreatePlayer('X')),
    player2(CreatePlayer('O')),
    game(new Game(player1, player2))
{
//	buffer->PrintMessage("Hello");
}

void GameMenu::PlayMatch()
{
    /*
    auto player = game->GetCurrPlayer();
    if(!player)
        buffer->ReadLine("!player");
    else {
        auto pos = player->ChooseFieldPos(game->GetFieldSet());
       // char c = player->GetSign();
        std::string name = player->GetName();
        buffer->ReadLine(name);
    }
*/
	while(!game->IsEnded())
	{
		auto currPlayer = game->GetCurrPlayer();
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

Player *GameMenu::CreatePlayer(char c)
{
	std::string nameMsg = "Write name for Player " + std::string(1,c),
		name = buffer->ReadLine(nameMsg);
	return new HumanPlayer(name, c, buffer);
}

void GameMenu::Restart()
{
	delete game;
	game = new Game(player1, player2);
}

GameMenu::~GameMenu()
{
	delete game;
	delete player1;
	delete player2;
}
