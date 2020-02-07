#include "buffer.h"
#include "menu.h"
#include "ncursesbuffer.h"

int main(){
	NcursesBuffer *buffer = new NcursesBuffer();
	Menu menu(static_cast<Buffer *> (buffer));
	menu.Serve();
		
	return 0;
}
