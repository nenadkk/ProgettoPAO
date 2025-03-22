#ifndef CREATEMEDIAVISITOR
#define CREATEMEDIAVISITOR
#include "../logica/visitor.h"
#include "../logica/media.h"
#include "mainWindow.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QObject>

class createMediaVisitor : public visitor
{
    private:
        mainWindow *windowEsterna;
        QGridLayout *layoutEsterno;

        void creaSottoOggettoMedia(QWidget**, QLineEdit**);

    public:
        createMediaVisitor(mainWindow*, QGridLayout*);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;
    
    private slots:
        void confermaSalvataggio();
        void annullaSalvataggio();
};

#endif
