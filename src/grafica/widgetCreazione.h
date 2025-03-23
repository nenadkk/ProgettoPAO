#ifndef WIDGETCREAZIONE
#define WIDGETCREAZIONE
#include <QPushButton>
#include <QMap>
#include "mainWindow.h"
#include "../mediaManager/mediaManager.h"
#include "../logica/media.h"

class widgetCreazione : public QWidget
{
    Q_OBJECT

    private:
        mediaManager *manager;
        QMap<QString, QLineEdit*> attributi;
        media *tipo;
        mainWindow* windowEsterna;

        void copiaImmagine(QString&);
        bool isImageFile(const QString &filePath) const;

    public slots:
        void crea();
        void browseImage();

    public:
        widgetCreazione(mediaManager*, media*, mainWindow*, QPushButton* parent=nullptr);
        void insertLineEdit(QString,QLineEdit*);
        QLineEdit*& operator[](const QString& );
};
#endif
