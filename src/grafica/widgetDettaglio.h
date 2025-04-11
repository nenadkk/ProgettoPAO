#ifndef WIDGETDETTAGLIO
#define WIDGETDETTAGLIO

#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "mainWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <QListWidget>

class widgetDettaglio : public QWidget
{    
    private:
        media* object;
        mediaManager* manager;
        mainWindow* windowEsterna;

    public:
        widgetDettaglio(media*,mediaManager*,QWidget *parent = nullptr);

        void buildDettaglio(libro*);
        void buildDettaglio(canzone*);
        void buildDettaglio(album*);

    private slots:
        void removeMedia();
        void modificaLibro();
        void modificaCanzone();
        void modificaAlbum();

};

#endif
