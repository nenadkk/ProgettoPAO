#ifndef MAINWINDOW
#define MAINWINDOW
#include "../logica/media.h"
#include "../listaMedia/listaMedia.h"
#include "qwidget.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>

class mainWindow : public QMainWindow 
{
    Q_OBJECT

    private:
        listamedia LM;
        QGridLayout *mediaVisibili;
        QLineEdit *searchBar;
        QLineEdit *copertinaTemp;

        void resizeEvent(QResizeEvent* event) override;
        void updateLayoutAtResize();
        void svuotaMediaVisibili();

        void creaSottoOggettoMedia(QWidget**, QLineEdit**);
        bool isImageFile(const QString &filePath) const;

    public:
        mainWindow(QWidget* parent = nullptr);

    private slots:
        void browseImage();
        void confermaSalvataggio();
        void annullaSalvataggio();

    public slots:
        void ricerca();
        void reloadMediaVisibili();
        void sceltaCreazione();

        void creaLibro();
        void creaCanzone();
        void creaAlbum();
};
#endif
