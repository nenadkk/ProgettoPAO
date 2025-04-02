#include "creaMediaVisitor.h"

creaMediaVisitor::creaMediaVisitor(mediaManager* m, QMap<QString, QLineEdit*> a, QListWidget*t) : 
    manager(m), attributi(a), trackList(t) {}

void creaMediaVisitor::visit(libro* newLibro)
{

}

void creaMediaVisitor::visit(canzone* newCanzone)
{

}

void creaMediaVisitor::visit(album* newAlbum)
{

}
