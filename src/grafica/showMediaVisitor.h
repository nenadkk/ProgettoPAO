#ifndef SHOWMEDIAVISITOR
#define SHOWMEDIAVISITOR
#include "../logica/visitor.h"
#include <QGridLayout>
class showMediaVisitor : public visitor
{
    private:
        QGridLayout* layoutDaRiempire;
        int row, col;
    public:
        showMediaVisitor(QGridLayout* );

        void visit(libro  *_libro) override;
        void visit(canzone  *_canzone) override;
        void visit(album  *_album) override;

};

#endif
