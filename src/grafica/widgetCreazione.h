#ifndef WIDGETCREAZIONE
#define WIDGETCREAZIONE
#include <QPushButton>
#include <QMap>
#include <QListWidget>

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
        QListWidget* trackList;

        void copiaImmagine();
        bool isImageFile(const QString &filePath) const;
        bool validaInput();

        void creaSottoOggettoMedia(QWidget**,widgetCreazione*);

    public slots:
        void crea();
        void browseImage();

        void buildWidget(libro*);
        void buildWidget(canzone*);
        void buildWidget(album*);

    public:
        widgetCreazione(media*, mediaManager*, QWidget* parent=nullptr, QListWidget* tracks = nullptr);
        void insertLineEdit(QString,QLineEdit*);
        QLineEdit*& operator[](const QString& );
};
#endif
