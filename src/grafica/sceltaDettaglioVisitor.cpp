#include "sceltaDettaglioVisitor.h"

sceltaDettaglioVisitor::sceltaDettaglioVisitor(mediaWidgetDettaglio* m) : widget(m) {}


void sceltaDettaglioVisitor::visit(libro* _libro)
{
    widget->buildDettaglio(_libro);
}
void sceltaDettaglioVisitor::visit(canzone* _canzone)
{
    widget->buildDettaglio(_canzone);
}
void sceltaDettaglioVisitor::visit(album* _album)
{
    widget->buildDettaglio(_album);
}
