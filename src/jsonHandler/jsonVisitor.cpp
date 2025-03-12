#include "jsonVisitor.h"
#include "qjsonobject.h"
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "../logica/libro.h"

void jsonVisitor::clearAll()
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

void jsonVisitor::visit(libro *_libro)
{
  //  QJsonDocument doc(jsonVisitor::libroToJson(*(_libro)));
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

    jsonArray.append(jsonVisitor::albumToJson(*(_album)));

    // Scrive i dati aggiornati nel file
    if (file.open(QIODevice::WriteOnly)) 
    {
        doc.setArray(jsonArray);
        file.write(doc.toJson());
        file.close();
    }
}

void jsonVisitor::readAllLibri(list<media*>& listaMedia)
{
    QFile file("./src/jsonHandler/data/libro.json");
    
    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning() << "Non è possibile aprire il file:" << file.errorString();
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) 
    {
        qWarning() << "Il file JSON non contiene un array valido.";
        return;
    }
    QJsonArray jsonArray = doc.array();
    
    for (const QJsonValue& value : jsonArray) 
    {
        if (value.isObject()) 
        {
            listaMedia.push_back(new libro(value["titolo"].toString().toStdString(), 
                                           value["autore"].toString().toStdString(), 
                                           value["anno"].toInt(), 
                                           value["copertina"].toString().toStdString(), 
                                           value["id"].toInt(),
                                           value["numPagine"].toInt(), 
                                           value["isbn"].toInt(), 
                                           value["editore"].toString().toStdString()));
        }
    }
}

void jsonVisitor::readAllCanzoni(list<media*>& listaMedia)
{
    QFile file("./src/jsonHandler/data/canzone.json");
    
    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning() << "Non è possibile aprire il file:" << file.errorString();
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) 
    {
        qWarning() << "Il file JSON non contiene un array valido.";
        return;
    }
    QJsonArray jsonArray = doc.array();
    
    for (const QJsonValue& value : jsonArray) 
    {

        if (value.isObject()) 
        {
            listaMedia.push_back(new canzone(value["titolo"].toString().toStdString(), 
                                           value["autore"].toString().toStdString(), 
                                           value["anno"].toInt(), 
                                           value["copertina"].toString().toStdString(), 
                                           value["id"].toInt(),
                                           value["durata"].toInt(), 
                                           value["genere"].toString().toStdString()));
        }
    }
}

void jsonVisitor::readAllAlbum(list<media*>& listaMedia)
{
    QFile file("./src/jsonHandler/data/album.json");
    
    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning() << "Non è possibile aprire il file:" << file.errorString();
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) 
    {
        qWarning() << "Il file JSON non contiene un array valido.";
        return;
    }
    QJsonArray jsonArray = doc.array();
    
    for (const QJsonValue& value : jsonArray) 
    {
        if (value.isObject()) 
        {
            album* a =new album(value["titolo"].toString().toStdString(), 
                    value["autore"].toString().toStdString(), 
                    value["anno"].toInt(), 
                    value["copertina"].toString().toStdString(), 
                    value["id"].toInt());
            
            //aggiunta dei riferimenti alle canzoni
            QJsonArray canzoniJson = value["canzoni"].toArray();
            
            for(auto temp : canzoniJson)
            {
                for(auto m : listaMedia)
                {
                    if(dynamic_cast<canzone*>(m) && m->getId()==temp.toInt()) //se è una canzone e l'id combacia
                    {
                        a->addCanzone(dynamic_cast<canzone*>(m)); 
                    }
                }
            }

            listaMedia.push_back(a);
        }
    }
}

QJsonObject jsonVisitor::libroToJson(const libro& _libro)
{
    QJsonObject json;
    json["titolo"] = toQString(_libro.getTitolo());
    json["autore"] = toQString(_libro.getAutore());
    json["anno"] = _libro.getAnno();
    json["copertina"] = toQString(_libro.getCopertina());
    json["id"] = _libro.getId();
    json["numPagine"] = _libro.getNumPagine();
    json["isbn"] = _libro.getIsbn();
    json["editore"] = toQString(_libro.getEditore());
    
    return json;
}

QJsonObject jsonVisitor::canzoneToJson(const canzone& _canzone)
{
    QJsonObject json;
    json["titolo"] = toQString(_canzone.getTitolo());
    json["autore"] = toQString(_canzone.getAutore());
    json["anno"] = _canzone.getAnno();
    json["copertina"] = toQString(_canzone.getCopertina());
    json["id"] = _canzone.getId();
    json["durata"] = _canzone.getDurata();
    json["genere"] = toQString(_canzone.getGenere());
    
    return json;
}

QJsonObject jsonVisitor::albumToJson(const album& _album)
{
    QJsonObject json;
    json["titolo"] = toQString(_album.getTitolo());
    json["autore"] = toQString(_album.getAutore());
    json["anno"] = _album.getAnno();
    json["copertina"] = toQString(_album.getCopertina());
    json["id"] = _album.getId();

    QJsonArray canzoniArray;

    for(int i=0; i<_album.getNumCanzoni();i++)
    {
        canzoniArray.append(_album[i]->getId());   
    }

    json["canzoni"] = canzoniArray;
    
    return json;
}
