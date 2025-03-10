#include "writeJsonVisitor.h"
#include "qjsonobject.h"
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>

void writeJsonVisitor::clearAll()
{
    string paths[3] = {"./src/jsonHandler/data/libro.json",
                       "./src/jsonHandler/data/canzone.json",
                       "./src/jsonHandler/data/album.json"};
    for(string p : paths)
    {
        QFile file(toQString(p));

        QJsonArray emptyArray;
        QJsonDocument doc(emptyArray);

        if (file.open(QIODevice::WriteOnly)) 
        {
            file.write(doc.toJson());
            file.close();
        }
    }
}

void writeJsonVisitor::visit(libro *_libro)
{
  //  QJsonDocument doc(writeJsonVisitor::libroToJson(*(_libro)));
    QFile file("./src/jsonHandler/data/libro.json");

    QJsonDocument doc;
    QJsonArray jsonArray;

    // Legge il contenuto del file 
    if (file.open(QIODevice::ReadOnly)) 
    {
        QByteArray data = file.readAll();
        file.close();

        doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) 
            jsonArray = doc.array();
        
    }

    jsonArray.append(writeJsonVisitor::libroToJson(*(_libro)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }
}

void writeJsonVisitor::visit(canzone *_canzone)
{
    QFile file("./src/jsonHandler/data/canzone.json");

    QJsonDocument doc;
    QJsonArray jsonArray;

    // Legge il contenuto del file 
    if (file.open(QIODevice::ReadOnly)) 
    {
        QByteArray data = file.readAll();
        file.close();

        doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) 
            jsonArray = doc.array();
        
    }

    jsonArray.append(writeJsonVisitor::canzoneToJson(*(_canzone)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }   
}

void writeJsonVisitor::visit(album *_album)
{
    QFile file("./src/jsonHandler/data/album.json");

    QJsonDocument doc;
    QJsonArray jsonArray;

    // Legge il contenuto del file 
    if (file.open(QIODevice::ReadOnly)) 
    {
        QByteArray data = file.readAll();
        file.close();

        doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) 
            jsonArray = doc.array();
        
    }

    jsonArray.append(writeJsonVisitor::albumToJson(*(_album)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }
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
