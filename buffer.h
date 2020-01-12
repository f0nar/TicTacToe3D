#ifndef BUFFER_H
#define BUFFER_H

class FieldSet;
struct FieldSetPosition;

class Buffer
{
public:
    virtual FieldSetPosition ReadFieldPos() = 0;
    virtual void DrawField(const FieldSet &fSet) = 0;
};

#endif
