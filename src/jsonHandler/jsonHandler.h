#ifndef JSONHANDLER
#define JSONHANDLER

#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "jsonVisitor.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class jsonHandler 
{
    public:
        static void saveMedia(media*);

        static void readAllLibri(list<media*>&);
        static void readAllCanzoni(list<media*>&);
        static void readAllAlbum(list<media*>&);

        static void clearAll(); //svuota i file per poter poi ripopolare
};


#endif
