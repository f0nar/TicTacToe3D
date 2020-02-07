#ifndef MENU_H
#define MENU_H

class Buffer;

class Menu
{
public:
	Menu(Buffer *buffer);
	void Serve();
private:
	void PrintHelp() const;
	void Play();
	Buffer *buffer;
};

#endif
