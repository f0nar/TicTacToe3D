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
	void Restart();
	bool IsEnded() const;
	const Player *GetCurrPlayer() const ;
	const FieldSet &GetFieldSet() const; 
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
	Player *player1, *player2;
	FieldSet fSet;
};

#endif
