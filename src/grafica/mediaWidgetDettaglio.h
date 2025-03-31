#ifndef MEDIAWIDGETDETTAGLIO
#define MEDIAWIDGETDETTAGLIO

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

class mediaWidgetDettaglio : public QWidget
{    
    private:
        media* object;

        mediaWidgetDettaglio(media*);
        void aggiungiPulsanti(QHBoxLayout*);

        void creaDettaglioLibro();
        void creaDettaglioCanzone();
        void creaDettaglioAlbum();

    public:
        static mediaWidgetDettaglio* creaDettaglio(media*);

};

#endif
