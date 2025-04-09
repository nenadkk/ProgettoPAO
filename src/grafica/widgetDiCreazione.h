#ifndef WIDGETDICREAZIONE
#define WIDGETDICREAZIONE
#include <QPushButton>
#include <QMap>
#include <QListWidget>
#include <array>

#include "mainWindow.h"
#include "../mediaManager/mediaManager.h"
#include "../logica/media.h"

class widgetDiCreazione : public QWidget
{
    Q_OBJECT

    protected:
        mediaManager *manager;
        QMap<QString, QLineEdit*> attributi;
        mainWindow* windowEsterna;
        std::array<QWidget*, 4> widgetBase;

        widgetDiCreazione(mediaManager*, QWidget* parent=nullptr);

        void copiaImmagine();
        bool isImageFile(const QString &filePath) const;
        bool validaInput();

    protected slots:
        virtual void crea() = 0;
        void browseImage();

    public:
        void insertLineEdit(QString,QLineEdit*);
        QLineEdit*& operator[](const QString& );
};
#endif
