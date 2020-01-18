#include "humanplayer.h"
#include "buffer.h"
#include "field.h"

HumanPlayer::HumanPlayer(std::string name, char sign, Buffer *buffer) :
	name(name), sign(sign), buffer(buffer)
{}

char HumanPlayer::GetSign() const 
{
	return sign;
}

std::string HumanPlayer::GetName() const
{ 
	return name;
}

FieldSetPosition HumanPlayer::ChooseFieldPos(const FieldSet &fSeht) const
{
	buffer->ReadFieldPos();
}
