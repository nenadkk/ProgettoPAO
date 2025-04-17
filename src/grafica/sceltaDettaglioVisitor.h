#ifndef SCELTADETTAGLIOVISITOR
#define SCELTADETTAGLIOVISITOR
#include "../logica/visitor.h"
#include "widgetDettaglio.h"

//l'oggetto puntato da widget non deve essere distrutto perché poi va visulizzato a schermo anche
//dopo la distruttore di questa classe

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
