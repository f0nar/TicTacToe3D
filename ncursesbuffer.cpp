#include "field.h"
#include "ncursesbuffer.h"
#include <vector>
#include <ncurses.h>

NcursesBuffer::NcursesBuffer() :
	win(initscr()), cacheValid(false)	
{
	//initscr();
	curs_set(0);
	noecho();
	keypad(win, true);

}
FieldSetPosition NcursesBuffer::ReadFieldPos(const FieldSet &fSet)
{
	FieldSetPosition fPos;

	while(true){
		int input = wgetch(win);
		switch(input){
			case KEY_ENTER:
				return fPos;
			case KEY_UP:
				if(fPos.y > 0) --fPos.y;
				break;
			case KEY_DOWN:
				if(fPos.y < fSet.GetMaxXY()- 1) ++fPos.y;
				break;
			case KEY_LEFT:
				if(fPos.x > 0) --fPos.x;
				else if(fPos.field == FieldSet::Down) fPos.field = FieldSet::Mid;
				else if(fPos.field == FieldSet::Mid) fPos.field = FieldSet::Top;
				break;
			case KEY_RIGHT:
				if(fPos.x < fSet.GetMaxXY()- 1) ++fPos.x;
				else if(fPos.field == FieldSet::Top) fPos.field = FieldSet::Mid;
				else if(fPos.field == FieldSet::Mid) fPos.field = FieldSet::Down;
				break;
		}
		DrawFieldFromCache(fPos);
	}
}

void NcursesBuffer::FieldToCache(const FieldSet &fSet)
{
	decltype(auto) fTable = fSet.GetFieldSet();
	decltype(auto) totalF = fSet.GetTotalField();

	const int rowLength = fSet.GetMaxXY()* 2- 1,
	      gapLength = 1;

	outLines.push_back(std::move("Top" + std::string(7, ' ') + "Mid" + std::string(6, ' ') + "Down"));

	for(int i = 0; i < rowLength; ++i){
		std::string iRow = std::string(rowLength* 3 + gapLength* 2, '-');
		for(int j = 1; j <= 2; ++j) 
			iRow[j*(rowLength + gapLength)- 1] = ' ';
	
		if(i % 2 == 0){	
			for(int j = 0; j < rowLength; ++j){
				if(j % 2){	
					iRow[j] = iRow[j+ rowLength+ gapLength] = iRow[j+ (rowLength+ gapLength)* 2] = '|'; 
				}
				else{
					iRow[j] = fTable.at(FieldSet::Top)[i/2][j/2];
					iRow[j+ rowLength+ gapLength] = fTable.at(FieldSet::Mid)[i/2][j/2]; 
					iRow[j+ (rowLength+ gapLength)* 2] = fTable.at(FieldSet::Down)[i/2][j/2] ; 
				}
			}
		}
		outLines.push_back(std::move(iRow));
 	}	

	outLines.push_back("Total");

	for(int i = 0; i < rowLength; ++i){
		std::string iRow = std::string(rowLength, '-');
		if(i % 2 == 0)
			for(int j = 0; j < rowLength; ++j)
				iRow[j] = (j % 2 == 0) ? totalF[i/2][j/2] : '|';
	outLines.push_back(std::move(iRow));
 	}
	
	cacheValid = true;
}


void NcursesBuffer::ToCacheIfIsNotIn(const FieldSet &fSet)
{
	//if(cacheValid && std::addresof(fSet) == fSetInCacheAddres) return;
	ClearCache();
	FieldToCache(fSet);
}

void NcursesBuffer::ClearCache()
{
	outLines.resize(0);
	cacheValid = false;
}

void NcursesBuffer::DrawFieldFromCache(FieldSetPosition fSetPos)
{
	wclear(win);
	const int fieldOffset  = 9,
	      gapOffset = 1,
	      outLinesCount = outLines.size();

	int fieldOffsetCount = 0, gapOffsetCount;
	if(fSetPos.field == FieldSet::Mid) fieldOffsetCount= 1;
	else if(fSetPos.field == FieldSet::Down) fieldOffsetCount= 2;
	gapOffsetCount = fieldOffsetCount > 0 ? fieldOffsetCount - 1 : fieldOffsetCount; 

	const int currX = fSetPos.x* 2 + fieldOffsetCount* fieldOffset + gapOffsetCount* gapOffset,
	      currY = fSetPos.y*2 + gapOffset ;	

	int winMaxX, winMaxY;
	getmaxyx(win, winMaxY, winMaxY);

	int i = 0;

	for(; i < currY; ++i)
		mvwaddstr(win, (winMaxY - outLines.size())/2 + i, (winMaxX - outLines[i].size())/2, outLines[i].c_str());

	mvwaddstr(win, (winMaxY - outLines.size())/2 + i, (winMaxX - outLines[i].size())/2, outLines[i].substr(0, currX).c_str());

	wattron(win, A_STANDOUT);
	mvwaddstr(win, (winMaxY - outLines.size())/ 2+ i, (winMaxX- outLines[i].size())/ 2+ currX, &outLines[i][currX]);
	wattroff(win, A_STANDOUT);

	mvwaddstr(win, (winMaxY - outLines.size())/ 2+ i, (winMaxX- outLines[i].size())/ 2+ currX+ 1, outLines[i].substr(currX + 1, outLines[i].size()).c_str());
	++i;
	
	for(; i < outLinesCount; ++i)
		mvwaddstr(win, (winMaxY - outLines.size())/2 + i, (winMaxX - outLines[i].size())/2, outLines[i].c_str());

	wrefresh(win);
}

void NcursesBuffer::DrawField(const FieldSet &fSet)
{
	ToCacheIfIsNotIn(fSet);
	FieldSetPosition fPos;
	DrawFieldFromCache(fPos);
	ClearCache();
}

void NcursesBuffer::DrawField(const FieldSet &fSet, const std::string &msg) 
{
	ToCacheIfIsNotIn(fSet);
	outLines.push_back(std::move(msg));
	FieldSetPosition fPos;
	DrawFieldFromCache(fPos);
	ClearCache();
}

void NcursesBuffer::PrintMessage(const std::string &msg)
{
	int maxX, maxY;
	getmaxyx(win, maxY, maxX);

	mvwaddstr(win, maxY/ 2, (maxX - msg.size())/ 2, msg.c_str());

	wrefresh(win);
	wgetch(win);
}

std::size_t NcursesBuffer::ChooseOneFromList(const std::vector<std::string> &optList, std::size_t count)
{
	return 0;
}

std::size_t NcursesBuffer::ChooseOneFromList(const std::vector<std::string> &optList, std::size_t count, const std::string &msg)
{
	
	std::size_t currOpt = 0;
	const std::size_t optCount = optList.size() < count ? optList.size() : count;

	int maxX, maxY;

	while(true){
		std::size_t i = 0;
		getmaxyx(win, maxY, maxX); 

		mvwaddstr(win, (maxY - optCount)/ 2- 1, (maxX - msg.size())/ 2, msg.c_str());

		for(; i < currOpt; ++i)
			mvwaddstr(win, (maxY - optCount)/ 2+ i, (maxX - optList[i].size())/ 2, optList[i].c_str());

		wattron(win, A_STANDOUT);
		mvwaddstr(win, (maxY - optCount)/ 2+ i, (maxX - optList[i].size())/ 2, optList[i].c_str());
		wattroff(win, A_STANDOUT);
		++i;

		for(; i < optCount; ++i) 
			mvwaddstr(win, (maxY - optCount)/ 2+ i, (maxX - optList[i].size())/ 2, optList[i].c_str());
		refresh();
		wrefresh(win);

		int input = wgetch(win);
		switch(input){
			case 10: 
				return currOpt;
			case KEY_DOWN: 
				if( currOpt < optCount - 1) ++currOpt;
				break;
			case KEY_UP:
				if( currOpt ) --currOpt;
				break;
		}

	}
}

std::string NcursesBuffer::ReadLine()
{
	return "";
}

std::string NcursesBuffer::ReadLine(const std::string &msg)
{
	wclear(win);

	char line[25];
	int maxY, maxX;
	
	getmaxyx(win, maxY, maxX);
	mvwaddstr(win, maxY/ 2, (maxX - msg.size())/ 2, msg.c_str());
	wrefresh(win);	
	echo();
//	keypad(win, false);
	mvwgetnstr(win, maxY/ 2+ 1, (maxX - msg.size())/ 2, line, 25);
	noecho();
//	keypad(win, true);

//	wgetch(win);
	return std::string(line); 
}

NcursesBuffer::~NcursesBuffer()
{
	delwin(win);
	endwin();
}
