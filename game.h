#ifndef GAME_H
#define GAME_H

#include <utility>
#include "field.h"

class Player;

class Game
{
public:
	Game(Player *p1, Player *p2);
	void Play();
	bool IsEnded();
	Player *GetCurrPlayer() const ;
private:
	std::size_t winLength = 5;
	void CheckWinSequence(std::size_t x, std::size_t y);
	void UpdatePlayer();
	bool gameEnded;
	bool currPlayer;
	bool CheckRow(const size_t x,const  size_t y, const vvc &field);
	bool CheckCow(const size_t x, const size_t y, const vvc &field);
	bool CheckMajorDiagonal(const size_t x, const size_t y, const vvc &field);
	bool CheckMinorDiagonal(const size_t x, const size_t y, const vvc &field);
	std::pair<Player*, Player*> players;
	FieldSet fSet;
};

#endif
