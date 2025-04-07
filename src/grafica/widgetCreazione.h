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
        mainWindow* windowEsterna;
        QListWidget* trackList;

        void copiaImmagine();
        bool isImageFile(const QString &filePath) const;
        bool validaInput();

        void creaSottoOggettoMedia(QWidget**,widgetCreazione*);

    private slots:
        void creaLibro();
        void creaCanzone();
        void creaAlbum();
        void browseImage();

    public slots:

        void buildWidget(libro*);
        void buildWidget(canzone*);
        void buildWidget(album*);

    public:
        widgetCreazione(media*, mediaManager*, QWidget* parent=nullptr);
        void insertLineEdit(QString,QLineEdit*);
        QLineEdit*& operator[](const QString& );
};
#endif
