#include "jsonVisitor.h"
#include "qjsonobject.h"
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "../logica/libro.h"
#include "jsonHandler.h"//per poter accede a save_file

void jsonVisitor::visit(libro *_libro)
{
  //  QJsonDocument doc(jsonVisitor::libroToJson(*(_libro)));
    QFile file(QString::fromStdString(save_file.find("libro")->second));

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

    jsonArray.append(jsonVisitor::libroToJson(*(_libro)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }
}

void jsonVisitor::visit(canzone *_canzone)
{
    QFile file(QString::fromStdString(save_file.find("canzone")->second));

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

    jsonArray.append(jsonVisitor::canzoneToJson(*(_canzone)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }   
}

void jsonVisitor::visit(album *_album)
{
    QFile file(QString::fromStdString(save_file.find("album")->second));

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

    jsonArray.append(jsonVisitor::albumToJson(*(_album)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) 
    {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }
}

QJsonObject jsonVisitor::libroToJson(const libro& _libro)
{
    QJsonObject json;
    json["titolo"] = QString::fromStdString(_libro.getTitolo());
    json["autore"] = QString::fromStdString(_libro.getAutore());
    json["anno"] = _libro.getAnno();
    json["copertina"] = QString::fromStdString(_libro.getCopertina());
    json["id"] = _libro.getId();
    json["numPagine"] = _libro.getNumPagine();
    json["isbn"] = _libro.getIsbn();
    json["editore"] = QString::fromStdString(_libro.getEditore());
    
    return json;
}

QJsonObject jsonVisitor::canzoneToJson(const canzone& _canzone)
{
    QJsonObject json;
    json["titolo"] = QString::fromStdString(_canzone.getTitolo());
    json["autore"] = QString::fromStdString(_canzone.getAutore());
    json["anno"] = _canzone.getAnno();
    json["copertina"] = QString::fromStdString(_canzone.getCopertina());
    json["id"] = _canzone.getId();
    json["durata"] = _canzone.getDurata();
    json["genere"] = QString::fromStdString(_canzone.getGenere());
    
    return json;
}

QJsonObject jsonVisitor::albumToJson(const album& _album)
{
    QJsonObject json;
    json["titolo"] = QString::fromStdString(_album.getTitolo());
    json["autore"] = QString::fromStdString(_album.getAutore());
    json["anno"] = _album.getAnno();
    json["copertina"] = QString::fromStdString(_album.getCopertina());
    json["id"] = _album.getId();

    QJsonArray canzoniArray;

    for(int i=0; i<_album.getNumCanzoni();i++)
    {
        canzoniArray.append(_album[i]->getId());   
    }

    json["canzoni"] = canzoniArray;
    
    return json;
}
