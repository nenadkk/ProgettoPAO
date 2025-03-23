#ifndef BOTTONESALVA
#define BOTTONESALVA
#include <QPushButton>
#include <QMap>
#include "../mediaManager/mediaManager.h"
#include "mainWindow.h"
#include "../logica/media.h"

class bottoneSalva : public QPushButton
{
    Q_OBJECT

    private:
        mediaManager *manager;
        QMap<QString, QLineEdit*> attributi;
        media *tipo;
        mainWindow* windowEsterna;

        void copiaImmagine(QString&);

    private slots:
        void crea();

    public:
        bottoneSalva(mediaManager*, QMap<QString,QLineEdit*>, media*, mainWindow*, QPushButton* parent=nullptr);
};
#endif
