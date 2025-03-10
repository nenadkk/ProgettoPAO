#ifndef WRITEJSONVISITOR
#define WRITEJSONVISITOR

#include "../logica/visitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class writeJsonVisitor : public visitor
{
    private:
        QJsonObject libroToJson(const libro&);
        QJsonObject canzoneToJson(const canzone&);
        QJsonObject albumToJson(const album&);

    public:
        void visit(libro  *_libro) override;
        void visit(canzone  *_canzone) override;
        void visit(album  *_album) override;

        void clearAll(); //svuota i file per poter poi ripopolare

};


#endif
