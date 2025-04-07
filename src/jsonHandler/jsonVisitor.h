#ifndef JSONVISITOR
#define JSONVISITOR

#include "../logica/visitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class jsonVisitor : public visitor
{
    private:
        QJsonObject libroToJson(const libro&);
        QJsonObject canzoneToJson(const canzone&);
        QJsonObject albumToJson(const album&);

    public:
        void visit(libro  *_libro) override;
        void visit(canzone  *_canzone) override;
        void visit(album  *_album) override;

};


#endif
