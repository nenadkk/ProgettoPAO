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
        mediaManager* manager;
        mainWindow* windowEsterna;
        void aggiungiPulsanti(QHBoxLayout*);

    public:
        mediaWidgetDettaglio(media*,mediaManager*,QWidget *parent = nullptr);

        void buildDettaglio(libro*);
        void buildDettaglio(canzone*);
        void buildDettaglio(album*);

    private slots:
        void removeMedia();

};

#endif
