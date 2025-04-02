#ifndef CREAMEDIAVISITOR
#define CREAMEDIAVISITOR
#include "../logica/visitor.h"
#include "../mediaManager/mediaManager.h"

#include <QLineEdit>
#include <QListWidget>

class creaMediaVisitor : public visitor
{
    private:
        mediaManager *manager;
        QMap<QString, QLineEdit*> attributi;
        QListWidget* trackList;

    public:
        creaMediaVisitor(mediaManager*,QMap<QString, QLineEdit*>, QListWidget*tracks=nullptr);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;
 
};

#endif
