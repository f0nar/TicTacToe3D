#ifndef MENU_H
#define MENU_H

#include "gamefactory.h"

class Buffer;

class Menu
{
public:
	Menu(Buffer *buffer);
	void Serve();
private:
	void PrintHelp() const;
	void Play();
	GameFactory gameFactory;
	Buffer *buffer;
};

#endif
