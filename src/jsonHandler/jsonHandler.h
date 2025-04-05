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
    private:
        jsonVisitor vis;
    public:
        void saveMedia(media*);

        void readAllLibri(list<media*>&);
        void readAllCanzoni(list<media*>&);
        void readAllAlbum(list<media*>&);

        void clearAll(); //svuota i file per poter poi ripopolare
};


#endif
