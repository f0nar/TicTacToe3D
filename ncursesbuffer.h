#ifndef NCURSESBUFFER_H
#define NCURSESBUFFER_H

#include "buffer.h"
#include <vector>

struct _win_st;
typedef _win_st WINDOW;

class NcursesBuffer : public Buffer
{
public:
	NcursesBuffer();
	FieldSetPosition ReadFieldPos(const FieldSet &fSet) ;
	void DrawField(const FieldSet &fSet);
	void DrawField(const FieldSet &fSet, const std::string &msg) ;
	void PrintMessage(const std::string &msg);
    std::size_t ChooseOneFromList(const std::vector<std::string> &optList, std::size_t count);
    std::size_t ChooseOneFromList(const std::vector<std::string> &optList, std::size_t count, const std::string &msg);
    std::string ReadLine();
    std::string ReadLine(const std::string &msg);
	~NcursesBuffer();
private:
	WINDOW* win;
	std::vector<std::string> outLines;
	bool cacheValid;
//	const FieldSet *fSetInCacheAddres;
	void ToCacheIfIsNotIn(const FieldSet &fSet);
	void FieldToCache(const FieldSet &fSet);
	void ClearCache();
	void DrawFieldFromCache(FieldSetPosition fPos);
};

#endif
