#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

class Buffer;
class Game;
class Player;

class GameFactory
{
public:
	GameFactory(Buffer *buffer);
	Game *CreateGame();
private:
	Player *CreatePlayer(char sign);
	Buffer *buffer;
		
};
	

#endif
