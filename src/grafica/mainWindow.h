#ifndef MAINWINDOW
#define MAINWINDOW
#include "../logica/media.h"
#include "../mediaManager/mediaManager.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>

class mainWindow : public QMainWindow 
{
    Q_OBJECT

    private:
        mediaManager mediaMan;
        QGridLayout *mediaVisibili;
        QLineEdit *searchBar;
        QLineEdit *copertinaTemp;

        int rowGrid;
        int colGrid;

        void ricerca();
        void addToMediaVisibili(media*);
        
    private slots:
        void sceltaCreazione();
        void creaLibro();
        void creaCanzone();
        void creaAlbum();

        void filtraLibri();
        void filtraCanzoni();
        void filtraAlbum();

    public:
        mainWindow(QWidget* parent = nullptr);
        void svuotaMediaVisibili();

    public slots:
        void reloadMediaVisibili();
};
#endif
