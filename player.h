#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct FieldSetPosition;

class Player
{
public:
    virtual FieldSetPosition ChooseFieldPos() const = 0 ;
    virtual char GetSign() const = 0;
    virtual std::string GetName() const = 0;
};

#endif
