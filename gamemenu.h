#ifndef GAMEMENU_H
#define MENU_H

class Game;
class Buffer;
class Player;
class HumanPlayer;

class GameMenu
{
public:
	GameMenu(Buffer *buffer);
	void PlayMatch();
	void Restart();
	~GameMenu();
private:
	void DrawWinner(const Player *winner);
	Player *CreatePlayer(char c);
	Game *game;
	Buffer *buffer;
	Player *player1, *player2;
};

#endif
