#include "sceltaDettaglioVisitor.h"

sceltaDettaglioVisitor::sceltaDettaglioVisitor(mediaWidgetDettaglio* m) : widget(m) {}


void sceltaDettaglioVisitor::visit(libro* _libro)
{
    widget->creaDettaglio(_libro);
}
void sceltaDettaglioVisitor::visit(canzone* _canzone)
{
    widget->creaDettaglio(_canzone);
}
void sceltaDettaglioVisitor::visit(album* _album)
{
    widget->creaDettaglio(_album);
}
