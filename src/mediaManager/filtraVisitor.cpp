#include "filtraVisitor.h"

filtraVisitor::filtraVisitor(list<media*> l) 
{
    for(auto m : l)
    {
        m->accept(this);
    }
}

list<media*> filtraVisitor::getSoloLibri() { return soloLibri; }
list<media*> filtraVisitor::getSoloCanzoni() { return soloCanzoni; }
list<media*> filtraVisitor::getSoloAlbum() { return soloAlbum; }

void filtraVisitor::visit(libro* _libro)
{
    soloLibri.push_back(_libro);
}

void filtraVisitor::visit(canzone* _canzone)
{
    soloLibri.push_back(_canzone);
}

void filtraVisitor::visit(album* _album)
{
    soloLibri.push_back(_album);
}
