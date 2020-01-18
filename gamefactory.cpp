#include "gamefactory.h"
#include "buffer.h"
#include "game.h"
#include "player.h"
#include "humanplayer.h"

GameFactory::GameFactory(Buffer *buffer) :
	buffer(buffer)
{}

Game *GameFactory::CreateGame()
{
	return (new Game(CreatePlayer('X'), CreatePlayer('O')));
}

Player *GameFactory::CreatePlayer(char sign)
{
	std::string nameMsg = "Enter your name (" + std::string(1, sign) + ")";
	std::string name = buffer->ReadLine(nameMsg);
	HumanPlayer *humanPlayer = new HumanPlayer(name, sign, buffer);
	return static_cast<Player *> (humanPlayer);
}

