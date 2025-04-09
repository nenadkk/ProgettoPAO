#ifndef FILTRAVISITOR
#define FILTRAVISITOR
#include <list>
#include "../logica/visitor.h"
#include "../logica/media.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"

class filtraVisitor : visitor
{
    private:
        list<media*> soloLibri;
        list<media*> soloCanzoni;
        list<media*> soloAlbum;

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override; 

    public:
        filtraVisitor(list<media*>);

        list<media*> getSoloLibri();
        list<media*> getSoloCanzoni();
        list<media*> getSoloAlbum();

};
#endif
