#ifndef SCELTADETTAGLIOVISITOR
#define SCELTADETTAGLIOVISITOR
#include "../logica/visitor.h"
#include "mediaWidgetDettaglio.h"

class sceltaDettaglioVisitor : public visitor
{
    private:
        mediaWidgetDettaglio *widget;

    public:
        sceltaDettaglioVisitor(mediaWidgetDettaglio*);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;

};
#endif
