#ifndef SHOWMEDIAVISITOR
#define SHOWMEDIAVISITOR
#include "../logica/visitor.h"
#include "mainWindow.h"
#include <QGridLayout>
class showMediaVisitor : public visitor
{
    private:
        mainWindow* windowEsterna;
        QGridLayout* layoutDaRiempire;
        int row, col, maxCol;
    public:
        showMediaVisitor(mainWindow*,QGridLayout*, int );

        void visit(libro  *_libro) override;
        void visit(canzone  *_canzone) override;
        void visit(album  *_album) override;

};

#endif
