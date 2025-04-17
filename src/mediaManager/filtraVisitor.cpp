#include "filtraVisitor.h"

filtraVisitor::filtraVisitor(list<media*> l) 
{
    for(auto m : l)
    {
        m->accept(this);
    }
}

list<media*> filtraVisitor::getSoloLibri() const { return soloLibri; }
list<media*> filtraVisitor::getSoloCanzoni() const { return soloCanzoni; }
list<media*> filtraVisitor::getSoloAlbum() const { return soloAlbum; }

void filtraVisitor::visit(libro* _libro)
{
    soloLibri.push_back(_libro);
}

void filtraVisitor::visit(canzone* _canzone)
{
    soloCanzoni.push_back(_canzone);
}

void filtraVisitor::visit(album* _album)
{
    soloAlbum.push_back(_album);
}
