#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>

class FieldSet;
struct FieldSetPosition;

class Buffer
{
public:
    virtual FieldSetPosition ReadFieldPos(const FieldSet &fSet) = 0;
    virtual void DrawField(const FieldSet &fSet) = 0;
    virtual void DrawField(const FieldSet &fSet,const std::string &msg) = 0;
    virtual void PrintMessage(const std::string &msg) = 0;
    virtual std::size_t ChooseOneFromList(const std::vector<std::string> &optList, std::size_t count) = 0;
     virtual std::size_t ChooseOneFromList(const std::vector<std::string> &optList, std::size_t count,const std::string &msg) = 0;
    virtual std::string ReadLine() = 0;
    virtual std::string ReadLine(const std::string &msg) = 0;
};

#endif
