#ifndef WIDGETEDITORMEDIA
#define WIDGETEDITORMEDIA
#include <QPushButton>
#include <QMap>
#include <QListWidget>
#include <array>

#include "mainWindow.h"
#include "../mediaManager/mediaManager.h"
#include "../logica/media.h"

class widgetEditorMedia : public QWidget
{
    Q_OBJECT

    protected:
        mediaManager *manager;
        QMap<QString, QLineEdit*> attributi;//i QLineEdit in questa mappa avranno come parent il layout principale
                                            //quindi verranno distrutti alla distruzione di quest ultimo
        mainWindow* windowEsterna;
        std::array<QWidget*, 4> widgetBase;//stesso discorso che con 'attributi'
        media* object;

        widgetEditorMedia(mediaManager*, QWidget* parent=nullptr, media* object=nullptr); //se object non viene passato allora 
                                                                                          //viene creato il widget in modalità 
                                                                                          //creazione, altrimenti in modalità di 
                                                                                          //modifica

        void copiaImmagine();
        bool isImageFile(const QString &filePath) const;
        bool validaInput();

    protected slots:
        virtual void crea() = 0;
        virtual void modifica() = 0;
        void browseImage();

    public:
        void insertLineEdit(QString,QLineEdit*);
        QLineEdit*& operator[](const QString& );
};
#endif
