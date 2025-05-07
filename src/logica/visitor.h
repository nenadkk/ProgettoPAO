#ifndef VISITOR
#define VISITOR

#include <string>
#include <QString>

//forward declaration
class libro;
class canzone;
class album;

class visitor
{
    public:
        virtual void visit(libro *_libro)=0; 
        virtual void visit(canzone *_canzone)=0; 
        virtual void visit(album *_album)=0; 
};

#endif
