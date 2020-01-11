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
	FieldSet(char x = 'X', char o = 'O');
	std::size_t GetMaxXY() const;
	void Set(FieldSetPosition fpos);
	const vvc &GetTotalField() const;
	const std::map<Field, vvc> &GetFieldSet() const;
private:
	std::size_t maxXY;
	std::map<Field, vvc> fieldSet;
	vvc totalField;
	void UpdateTotalField(std::size_t x, std::size_t y);
        const char &Intercept(const char &top, const char &down);	
}

struct FieldSetPosition
{
	FieldSetPosition();
	FieldSet::Field field;
	int x, y;
}

#endif
