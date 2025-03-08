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
    public:
        void visit(libro  *_libro) override;
        void visit(canzone  *_canzone) override;
        void visit(album  *_album) override;

        QJsonObject libroToJson(const libro&);
        QJsonObject canzoneToJson(const canzone&);
        QJsonObject albumToJson(const album&);

        void salvaLibri(const list<media>& _libri);
        void salvaCanzoni(const list<canzone>& _canzoni);
        void salvaAlbum(const list<media>& _album);
};


#endif
