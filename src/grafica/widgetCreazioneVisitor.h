#ifndef WIDGETCREAZIONEVISITOR
#define WIDGETCREAZIONEVISITOR
#include "../logica/visitor.h"
#include "../logica/media.h"
#include "mainWindow.h"
#include "widgetCreazione.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QObject>

class widgetCreazioneVisitor : public visitor
{
    private:
        widgetCreazione* widget;

    public:
        widgetCreazioneVisitor(widgetCreazione*);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;
    
};

#endif
