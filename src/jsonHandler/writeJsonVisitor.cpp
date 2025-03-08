#include "writeJsonVisitor.h"

void writeJsonVisitor::visit(libro *_libro)
{
             
}

void writeJsonVisitor::visit(canzone *_canzone)
{
    
}

void writeJsonVisitor::visit(album *_album)
{
    
}


QJsonObject writeJsonVisitor::libroToJson(const libro& _libro)
{
    QJsonObject json;
    json["titolo"] = toQString(_libro.getTitolo());
    json["autore"] = toQString(_libro.getAutore());
    json["anno"] = _libro.getAnno();
    json["copertina"] = toQString(_libro.getCopertina());
    json["numPagine"] = _libro.getNumPagine();
    json["isbn"] = _libro.getIsbn();
    json["editore"] = toQString(_libro.getEditore());
    
    return json;
}

QJsonObject writeJsonVisitor::canzoneToJson(const canzone& _canzone)
{
    QJsonObject json;
    json["titolo"] = toQString(_canzone.getTitolo());
    json["autore"] = toQString(_canzone.getAutore());
    json["anno"] = _canzone.getAnno();
    json["copertina"] = toQString(_canzone.getCopertina());
    json["durata"] = _canzone.getDurata();
    json["genere"] = toQString(_canzone.getGenere());
    json["id"] = _canzone.getId();
    
    return json;
}

QJsonObject writeJsonVisitor::albumToJson(const album& _album)
{
    QJsonObject json;
    json["titolo"] = toQString(_album.getTitolo());
    json["autore"] = toQString(_album.getAutore());
    json["anno"] = _album.getAnno();
    json["copertina"] = toQString(_album.getCopertina());

    QJsonArray canzoniArray;

    for(int i=0; i<_album.getNumCanzoni();i++)
    {
        canzoniArray.append(_album[i]->getId());   
    }

    json["canzoni"] = canzoniArray;
    
    return json;
}
