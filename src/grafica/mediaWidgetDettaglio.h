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

class sceltaDettaglioVisitor;

class mediaWidgetDettaglio : public QWidget
{    
    private:
        void aggiungiPulsanti(QHBoxLayout*);

    public:
        mediaWidgetDettaglio(media*);

        void creaDettaglio(libro*);
        void creaDettaglio(canzone*);
        void creaDettaglio(album*);

};

#endif
