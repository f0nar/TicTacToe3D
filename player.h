#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class FieldSet;
struct FieldSetPosition;

class Player
{
public:
    virtual FieldSetPosition ChooseFieldPos(const FieldSet &fSet) const = 0 ;
    virtual char GetSign() const = 0;
    virtual std::string GetName() const = 0;
};

#endif
