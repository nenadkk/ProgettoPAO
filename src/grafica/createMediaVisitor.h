#ifndef CREATEMEDIAVISITOR
#define CREATEMEDIAVISITOR
#include "../logica/visitor.h"
#include "../logica/media.h"
#include "mainWindow.h"
#include "widgetCreazione.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QObject>

class createMediaVisitor : public visitor
{
    private:
        mainWindow *windowEsterna;
        QGridLayout *layoutEsterno;
        mediaManager *managerEsterno;

        void creaSottoOggettoMedia(QWidget**,widgetCreazione*);

    public:
        createMediaVisitor(mainWindow*, QGridLayout*, mediaManager*);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;
    
    private slots:
        void confermaSalvataggio();
        void annullaSalvataggio();
};

#endif
