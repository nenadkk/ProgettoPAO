#ifndef SCELTADETTAGLIOVISITOR
#define SCELTADETTAGLIOVISITOR
#include "../logica/visitor.h"
#include "widgetDettaglio.h"

class sceltaDettaglioVisitor : public visitor
{
    private:
        widgetDettaglio *widget;

    public:
        sceltaDettaglioVisitor(widgetDettaglio*);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;

};
#endif
