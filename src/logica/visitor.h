#ifndef VISITOR
#define VISITOR

#include <string>
#include <QString>

class libro;
class canzone;
class album;

inline QString toQString(const std::string& str) 
{
    return QString::fromStdString(str);
}

class visitor
{
    public:
        virtual void visit(libro *_libro)=0; 
        virtual void visit(canzone *_canzone)=0; 
        virtual void visit(album *_album)=0; 
};

#endif
