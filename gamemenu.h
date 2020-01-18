#ifndef GAMEMENU_H
#define MENU_H

class Game;
class Buffer;
class Player;

class GameMenu
{
public:
	GameMenu(Game *game, Buffer *buffer);
	void PlayMatch();
	void DrawWinner(const Player *winner);
private:
	Game *game;
	Buffer *buffer;
};

#endif
