#ifndef HUMENPLAYER_H
#define HUMENPLAYER_H

#include "player.h"

class Buffer;

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name, char sign, Buffer *buffer);
	FieldSetPosition ChooseFieldPos(const FieldSet &fSet) const;
	char GetSign() const;
	std::string GetName() const;
private:
	std::string name;
	char sign;
	Buffer *buffer;
};

#endif
