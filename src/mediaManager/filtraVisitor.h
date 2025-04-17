#ifndef FILTRAVISITOR
#define FILTRAVISITOR
#include <list>
#include "../logica/visitor.h"
#include "../logica/media.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"

//nel distruttore di questa classe gli oggetti puntati dalle liste soloLibri,soloCanzoni,soloAlbum
//non vengono eliminati perché questi oggetti sono condivisi con mediaManager, eliminarli significherebbe
//renderli rimuoverli anche da mediaManager
//
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

        list<media*> getSoloLibri() const;
        list<media*> getSoloCanzoni() const;
        list<media*> getSoloAlbum() const;

};
#endif
