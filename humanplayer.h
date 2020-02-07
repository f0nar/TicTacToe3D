#ifndef HUMENPLAYER_H
#define HUMENPLAYER_H

#include "player.h"

class Buffer;

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name, char sign, Buffer *buffer) ;
	FieldSetPosition ChooseFieldPos(const FieldSet &fSet) const override;
	char GetSign() const override ;
	std::string GetName() const override;
private:
	std::string name;
	char sign;
	Buffer *buffer;
};

#endif
