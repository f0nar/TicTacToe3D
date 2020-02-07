#ifndef FIELDSET_H
#define FIELDSET_H

#include <vector>
#include <map>

typedef std::vector<std::vector<char>> vvc;

struct FieldSetPosition;

class FieldSet
{
public:
	enum Field {Top, Mid, Down};
	FieldSet(char x = 'X', char o = 'O', char n = ' ');
	std::size_t GetMaxXY() const;
	void Set(FieldSetPosition fpos);
	const vvc &GetTotalField() const;
	const std::map<Field, vvc> &GetFieldSet() const;
private:
	std::size_t maxXY;
	std::map<Field, vvc> fieldSet;
	vvc totalField;
	std::vector<FieldSetPosition> moveHistory;
	char GetCurrentChar() const;
	void UpdateCurrentChar();
	void UpdateTotalField(std::size_t x, std::size_t y);
        const char &Intercept(const char &top, const char &down);	
	char X, O, NONE, currChar;
};

struct FieldSetPosition
{
	FieldSetPosition();
	FieldSet::Field field;
	int x, y;
};

#endif
