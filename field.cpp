#include <field.h>

FieldSet::FieldSet(char x, char o, char n)
	:maxXY(5), X(x), O(o), NONE(n), totalField(maxXY, std::vector<char>(maxXY, NONE))
{
	fieldSet[Field::Top] = vvc(totalField);
	fieldSet[Field::Mid] = vvc(totalField);
	fieldSet[Field::Down] = vvc(totalField);
}

void FieldSet::Set(FieldSetPosition fpos)
{
	fieldSet[fpos.field][fpos.x][fpos.y] = GetCurrentChar();
	UpdateTotalField(fpos.x, fpos.y);
}

const vvc &FieldSet::GetTotalField() const
{
	return totalField;
}

const std::map<FieldSet::Field, vvc> &FieldSet::GetFieldSet() const 
{
	return fieldSet;
}

void FieldSet::UpdateCurrentChar()
{
	currChar = currChar == X ? O : X;
}

char FieldSet::GetCurrentChar() const 
{
	return currChar;
}

void FieldSet::UpdateTotalField(std::size_t x, std::size_t y)
{
	char midXYval = fieldSet[Field::Mid][x][y], 
	     downXYval = fieldSet[Field::Down][x][y], 
	     topXYval = fieldSet[Field::Top][x][y],  
	     &totalXYval = totalField[x][y];

	if(midXYval != NONE && downXYval == midXYval)
        	totalXYval = midXYval;
    	else if(midXYval == NONE && downXYval == midXYval)
        	totalXYval = topXYval;
   	else
        	totalXYval = Intercept(topXYval, Intercept(midXYval, downXYval));
}

std:: size_t FieldSet::GetMaxXY() const 
{
	return maxXY;
}

const char &FieldSet::Intercept(const char &top, const char &down)
{
	return top == NONE ? down : top;
}

FieldSetPosition::FieldSetPosition() :
       field(FieldSet::Mid), x(5/2), y(x)
{}	
