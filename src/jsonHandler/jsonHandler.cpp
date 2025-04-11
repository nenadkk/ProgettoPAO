#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "jsonVisitor.h"
#include "jsonHandler.h"
#include "../logica/libro.h"

void jsonHandler::saveMedia(media* obj)
{
    jsonVisitor vis;
    obj->accept(&vis);
}

void jsonHandler::clearAll()
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

void jsonHandler::readAllLibri(list<media*>& listaMedia)
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

void jsonHandler::readAllCanzoni(list<media*>& listaMedia)
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

void jsonHandler::readAllAlbum(list<media*>& listaMedia)
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
                    if(m->getId()==temp.toInt()) //se l'id combacia (l'id è univoco per ogni media, quindi se combacia
                                                 //per forza è un media di tipo canzone)
                    {
                        a->addCanzone(dynamic_cast<canzone*>(m)); 
                    }
                }
            }

            listaMedia.push_back(a);
        }
    }
}

